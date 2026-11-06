# ZPD State: broken_gnl

## Section 1: Active Session Resume Snapshot
- Current Micro-Step: `ZPD_CONSOLIDATION` (Post-Pass Debrief & Core Takeaways)
- Current Mode: Debrief & Blank-Slate Principle Clarification
- Status: PASSED 🎉 & Consolidated

## Section 2: Concept DAG & Trajectory
- [x] `ZPD_0`: GNL의 핵심 데이터 생명주기 모델 정립 [Consolidated]
- [x] `ZPD_1`: `broken_gnl` 코드 구조 및 4단계-함수 1:1 매핑 [Consolidated]
- [x] `ZPD_2`: 보조 도구들 5개 전체 완벽 수리 완료 [Consolidated]
- [x] `ZPD_3`: `get_next_line` 본체 구현 [Consolidated]
- [x] `ZPD_4`: 테스터 전체 통과 (PASSED 🎉) [Consolidated]

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
