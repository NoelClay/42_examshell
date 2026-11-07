# ZPD State: broken_gnl

## Section 1: Active Session Resume Snapshot
- Current Micro-Step: `ZPD_COMPLETED`
- Current Mode: Post-Mortem Consolidated
- Status: All 3 Recall Gate questions answered accurately and consolidated. 🎉

## Section 2: Concept DAG & Trajectory
- [x] `ZPD_0`: GNL의 핵심 데이터 생명주기 모델 정립 [Consolidated]
- [x] `ZPD_1`: `broken_gnl` 코드 구조 및 4단계-함수 1:1 매핑 [Consolidated]
- [x] `ZPD_2`: 보조 도구들 5개 전체 완벽 수리 완료 [Consolidated]
- [x] `ZPD_3`: `get_next_line` 본체 구현 [Consolidated]
- [x] `ZPD_4`: 테스터 전체 통과 (PASSED 🎉) [Consolidated]
- [x] `ZPD_5`: 메모리 오버랩의 읽기/쓰기 선후관계(RAW) 메커니즘 정립 [Consolidated]
- [x] `ZPD_6`: 동적 메모리 반환 전 free 불변식 및 Valgrind 검사 대상 원리 [Consolidated]

## Section 3: Bottleneck Trade-Off Log
- [B-10] `final_check`에서 동적 할당 포인터 미해제(`free`)로 인한 1바이트 릭
  - 현상: Valgrind 검사 시 `definitely lost: 1 bytes in 1 blocks` 발생 (`str_append_str` at line 197).
  - 원인: `final_check(res)`에서 `s && s[0]`가 거짓(빈 문자열)일 때 `return NULL;`을 수행하지만, `res`는 `str_append_str`에 의해 이미 1바이트(널문자)가 malloc된 힙 블록임. `free(s)`를 호출하지 않고 주소를 버렸기 때문에 릭 발생.
- [B-11] `valgrind`의 구동 메커니즘 오해 (바이너리 실행기 vs 소스 코드)
  - 현상: `valgrind ./get_next_line.c` 실행 후 에러가 0개라고 오판.
  - 진실: Valgrind는 컴파일된 실행 파일(ELF 바이너리)의 기계어 실행을 감시하는 동적 분석 도구임. `.c` 소스 파일을 넣으면 쉘이 스크립트로 오인해 구문 오류로 즉시 죽어버리므로 C 코드가 아예 실행되지 않음.
- [B-9] EOF 도달 시 빈 문자열("") 반환과 외부 루프 무한 루프
  - 현상: 세그폴트 해결 후 테스터가 무한 루프 타임아웃으로 실패.
  - 원인: 호출자(`main`)는 `while ((line = get_next_line(fd)) != NULL)`로 파일 끝을 감지함. 파일의 모든 내용을 읽어 더 이상 읽을 데이터가 없을 때, 함수 마지막에서 `str_append_str(&res, b)`(`b`는 `""`)를 실행하여 길이 0짜리 힙 블록(`""`)을 반환함. 포인터 주소가 0이 아니므로 호출자가 `NULL`로 인식하지 못해 무한 호출 발생.
- [B-8] 스택 지역 변수(포인터)의 초기화 누락과 쓰레기 주소(garbage pointer) 역참조
  - 현상: 첫 줄을 읽고 `str_append_mem(&res, b, ...)`을 호출할 때 `ft_strlen` 내부에서 `s[res]` 참조 시 세그멘테이션 폴트 발생.
  - 가설/원인: `get_next_line` 내부의 지역 변수 `res`가 초기화되지 않아 스택에 남아있던 임의의 쓰레기 주소를 들고 있고, `str_append_mem`이 `*s1`을 `ft_strlen`에 전달할 때 `!s` 검사를 통과해버린 채 유효하지 않은 주소(`0xe30` 등)를 읽으려 시도함.
- [B-7] 메모리 오버랩에서 '오염'의 본질 (src 사후 변경 vs 미읽기 원본 훼손)
  - 학습자 의문 ($H_{\text{user}}$): `ft_memmove(dest, dest+1, 10)`에서 src가 결국 다 덮어씌워져 오염되는 것 아닌가? 핵심 오염이 dest인지 src인지 혼란.
  - 핵심 구분:
    1. `memmove`의 계약: "복사가 끝났을 때 dest에 원래 src 내용이 온전히 도달하는가?" (복사 완료 후 src 자리의 값 보존은 애초에 요구사항이 아님)
    2. 오염의 실체: **"아직 읽지 않은 src의 원본 데이터가 dest에 쓰는 동작 때문에 미리 지워져버리는 현상"** (이로 인해 dest에 엉뚱한 복사본이 들어감)

## Section 3: Bottleneck Trade-Off Log
- [B-6] 백지 코딩에 대한 막막함과 두려움
  - 학습자 체감: "broken gnl을 다시 백지 코딩하라고 하면 절대 못할 것 같다."
  - 진실: 이 6개 보조 함수 구조는 출제자가 억지로 꼬아놓은 시험용 기형 구조임. 백지 상태에서는 이렇게 복잡하게 짤 필요가 없음.
  - 진정한 학습 자산:
    1. 포인터 뺄셈(`tmp - b + 1`)의 길이 계산 원리
    2. 동일 버퍼 내 잔여 데이터 당기기(`ft_memmove`)
    3. `size_t` 음수 검사 시 언더플로우 함정
    4. 동적 메모리 확장 시 이전 포인터 `free`와 교체 매커니즘

## Section 4: Blank-Slate Recall Log
- [ZPD_6 Recall Pass]:
  1. 포인터 초기화: 지역 변수를 NULL로 초기화해야 `!s` 방어선이 작동하여 쓰레기 주소 역참조(SIGSEGV)를 방지함.
  2. EOF 반환 규약: 빈 문자열(`""`)은 유효한 주소이므로 호출자의 `line != NULL` 루프를 종료시키지 못함. 더 읽을 내용이 없으면 반드시 `NULL`을 반환해야 함.
  3. 동적 메모리 해제: 빈 문자열이라도 append 로직을 거쳐 `malloc(1)`로 힙에 할당된 블록이므로, `NULL`을 반환하기 전에 반드시 `free(s)`로 해제해야 누수가 발생하지 않음.
- [Final Consolidation]: broken_gnl 전체 수리 완료 및 테스터 통과 (PASSED 🎉)

## Section 3: Bottleneck Trade-Off Log
- [B-4] 학습자가 `ft_memcpy`에 `memmove` 로직을 구현함
  - 상황: 학습자가 `ft_memcpy`에 `dest < src` 분기를 직접 넣어 `memmove`의 동작을 구현함.
  - 의문: "내가 고친 ft_memcpy랑 ft_memmove랑 뭐가 달라?"
  - 해답: 완전히 동일함. 원래 C 표준에서 memcpy는 단순 복사(분기 없음), memmove가 그 분기를 가진 안전한 복사인데, 출제자가 둘 다 망쳐놔서 학습자가 memcpy에 memmove를 넣어버린 상황.

## Section 3: Bottleneck Trade-Off Log
- [B-1] 버퍼 잔여 데이터 이동 시 `ft_memcpy` 선택
  - 학습자 가설 ($H_{\text{user}}$): 메모리에 있는 데이터를 복사하는 것이므로 `ft_memcpy`를 사용할 수 있다.
  - 실제 메커니즘: `ft_memcpy`는 서로 겹치지 않는(non-overlapping) 별개의 메모리 영역 복사용이며, `str_append_mem` 내부에서 `tmp`로 복사할 때 쓰임. 동일한 버퍼 내부에서 영역이 겹칠 수 있는 이동은 `ft_memmove`의 본래 목적임.
- [B-2] `ft_strchr`에서 인덱스(숫자) 대신 포인터(주소)를 반환하는 이유
  - 학습자 가설 ($H_{\text{user}}$): 그냥 몇 번째인지 숫자 5를 반환하는 편이 직관적이다.
  - 실제 트레이드오프: 숫자를 반환하면 '못 찾음(-1)'과 '찾음(0 이상)'의 자료형 분리가 생기고, 뒷부분 주소를 구할 때 다시 덧셈(`s + idx`)을 거쳐야 함. 포인터를 반환하면 '못 찾음(NULL)'이 자연스럽고, 뒷부분 주소(`tmp + 1`)로 즉시 이동 가능함.

## Section 3: Bottleneck Trade-Off Log
- [B-1] 버퍼 잔여 데이터 이동 시 `ft_memcpy` 선택
  - 학습자 가설 ($H_{\text{user}}$): 메모리에 있는 데이터를 복사하는 것이므로 `ft_memcpy`를 사용할 수 있다.
  - 실제 메커니즘: `ft_memcpy`는 서로 겹치지 않는(non-overlapping) 별개의 메모리 영역 복사용이며, `str_append_mem` 내부에서 `tmp`로 복사할 때 쓰임. 동일한 버퍼 내부에서 영역이 겹칠 수 있는 이동은 `ft_memmove`의 본래 목적임.

## Section 4: Blank-Slate Recall Log
- [ZPD_0 Recall Pass]:
  1. 버퍼 확인
  2. 파일 읽기/누적 -> 한 줄이 생길 때까지
  3. 한 줄 반환
  4. 버퍼를 정리 (남은 부분 앞으로 당기고 널 종단)
