# ZPD State: scanf

## Section 1: Active Session Resume Snapshot
- Current Micro-Step: `ZPD_COMPLETED`
- Current Mode: Post-Implementation Complete
- Status: All tests passed (PASSED 🎉), edge cases (trailing EOF, string null-termination, ungetc character preservation) fully resolved.

## Section 2: Concept DAG & Trajectory
- [x] `ZPD_0`: scanf 표준 서식 지시자(공백, 일반 문자, % 변환) 및 반환값 규약 정립 [Consolidated]
- [x] `ZPD_1`: 헬퍼 함수 분할 및 match_space, match_char 동작 원리 [Consolidated]
- [x] `ZPD_2`: scan_int (부호 및 cnt 카운터 도입, ungetc 복원) 완료 [Consolidated]
- [x] `ZPD_3`: scan_string (단어 누적, 널 종단 '\0', trailing EOF 처리) [Consolidated]
- [x] `ZPD_4`: scan_char (단일 문자 읽기) 구현 [Consolidated]
- [x] `ZPD_5`: 테스터 통과 및 Blank-Slate Recall [Consolidated]

## Section 3: Bottleneck Trade-Off Log
- [B-7] ferror(f) vs (fc == EOF)의 개념적 차이
  - 의문: `if (ferror(f))`와 `if (fc == EOF)`는 무엇이 다른가?
  - 본질:
    1. `fc == EOF`: `fgetc`의 단일 호출 반환값. 파일이 정상적으로 끝난 것(EOF)과 에러 모두 `-1`로 반환됨.
    2. `ferror(f)`: 스트림(`FILE *`) 구조체 내부의 에러 플래그 확인 함수. 정상적인 파일 끝이 아니라 실제 입출력 하드웨어/OS 실패(Read Error)가 있었는지를 판별함.
- [B-6] EOF 직전 유효 데이터 획득 시 실패 처리 가설 ($H_{\text{user}}$)
  - 가설: "끝난 것이므로 할당은 하더라도 변환 자체는 실패로 보아야 한다."
  - 실체: 파일의 마지막 줄에 공백이나 개행이 없더라도 읽어낸 "123"은 온전한 정수임. 만약 이를 실패(0) 처리하면 파일 마지막 데이터가 버려짐. 실제 glibc scanf도 r=1로 성공 처리함.
- [B-5] 파일 끝(EOF)으로 끝나는 데이터(`echo -n "123"`)에서 유효 데이터 읽음에도 실패 처리
  - 현상: `echo -n "123"` 입력 시 `cnt == 3`임에도 루프 종료 조건 `fc == EOF` 때문에 `return EOF`를 수행하여 `r = 0`이 됨.
  - 불변식: 루프를 끝낸 원인이 EOF더라도 이미 유효한 데이터(`cnt > 0` 또는 `i > 0`)를 확보했다면 변환 성공(`1`)임.
- [B-4] scan_string에서 문자열 널 종단(`\0`) 누락
  - 현상: 버퍼에 기존 데이터가 남아있을 경우 `s=[helloXXX]`처럼 널 문자가 붙지 않아 버퍼 오염/유출 발생.
- [B-3] scan_int에서 유효 숫자 0개일 때의 성공 반환 및 읽은 문자 유실
  - 현상: `"abc hello world"` 입력 시 `%d`가 실패하지 않고 `0`을 넣은 뒤 성공(`1`)을 반환하여 뒤의 `%s`, `%c`까지 진행되어 `3`을 반환함.
  - 원인:
    1. 숫자가 1개도 읽히지 않았는데도 `return 1`을 수행함.
    2. `while` 문에서 숫자가 아닌 문자(`'a'`)를 `fgetc`로 꺼내 검사한 뒤 `ungetc`로 되돌리지 않아 스트림에서 글자가 유실됨.
- [B-1] format의 단일 공백과 filestream의 연속 공백 소비 불일치 의문
  - 학습자 의문 ($H_{\text{user}}$): format 포인터는 한 글자씩 넘어가는데 왜 stream에서는 공백을 모조리 스킵(`match_space`)해야 하는가?
  - man 3 scanf 명세: 포맷의 공백 지시자(whitespace directive)는 입력 스트림에서 0개 이상의 연속된 모든 공백(스페이스, 탭, 개행)과 매칭됨.
- [B-2] scanf의 -1(EOF) 반환 조건 혼란
  - 학습자 의문 ($H_{\text{user}}$): -1을 언제 반환해야 하는가? man page에 명시되어 있는가? fgetc의 에러(-1)인가?
  - man 3 scanf 명세:
    1. 첫 번째 변환(또는 일치 실패)이 일어나기 전에 이미 입력 스트림의 끝(EOF)에 도달한 경우.
    2. 스트림 읽기 에러(`ferror(f)`)가 발생한 경우.
    (그 외 변환 도중 실패하거나 입력이 맞지 않으면 지금까지 성공한 변환 개수 `nconv`를 반환함).

## Section 4: Blank-Slate Recall Log
