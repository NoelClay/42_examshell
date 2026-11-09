# Persistent ZPD Brain: Misconception Ledger & Master Domain Index

## Active Session Pointer
- Topic: `tsp`
- State File: `references/zpd-states/tsp.md`
- Active Phase: Conceptual Study Complete (생각정리.md Ready)

## Consolidated Concepts
1. GNL 4-stage lifecycle: Buffer check -> Read until \n -> Return line -> Move leftover to front.
2. Pointer arithmetic: `tmp - b + 1` calculates slice length including newline directly from address difference.
3. Memory overlap: In-place buffer shifting requires `memmove` principles.
4. Unsigned underflow: `size_t` decrements never drop below zero (`i >= 0` is an infinite loop).
5. Dynamic memory append: Reallocation lifecycle (malloc new -> copy old & new -> free old -> assign).
6. Local pointer initialization: Stack garbage addresses bypass `!s` guards, causing crashes on dereference.
7. EOF return contract: Empty string `""` has a non-NULL pointer; GNL must return `NULL` on EOF to terminate caller loops.
8. Orphaned heap blocks on NULL returns: Even 1-byte empty strings (`malloc(1)`) must be `free`d before returning `NULL`.
9. Valgrind execution target: Must run on compiled binaries (`test_gnl`), not `.c` source files.
10. scanf whitespace directive: Matches 0 or more consecutive whitespace characters from the input stream.
11. scanf EOF contract: EOF (-1) is returned only if stream is already at EOF or ferror occurs before any conversion; otherwise returns count of matched conversions (nconv).
12. Stream restoration: Non-matching characters read by fgetc must be restored with ungetc unless EOF.
13. String null-termination: Strings read via `%s` must always be terminated with `'\0'`.
14. TSP in-place swap invariant: Swapping within path preserves 1-to-1 bijection (all cities visited exactly once, zero extra memory, L1 cache locality).
15. TSP circular symmetry: Fixing city 0 at index 0 reduces N! permutations to (N-1)! by removing N rotational duplicates.

## Consolidated Concepts
1. GNL 4-stage lifecycle: Buffer check -> Read until \n -> Return line -> Move leftover to front.
2. Pointer arithmetic: `tmp - b + 1` calculates slice length including newline directly from address difference.
3. Memory overlap: In-place buffer shifting requires `memmove` principles.
4. Unsigned underflow: `size_t` decrements never drop below zero (`i >= 0` is an infinite loop).
5. Dynamic memory append: Reallocation lifecycle (malloc new -> copy old & new -> free old -> assign).
6. Local pointer initialization: Stack garbage addresses bypass `!s` guards, causing crashes on dereference.
7. EOF return contract: Empty string `""` has a non-NULL pointer; GNL must return `NULL` on EOF to terminate caller loops.
8. Orphaned heap blocks on NULL returns: Even 1-byte empty strings (`malloc(1)`) must be `free`d before returning `NULL`.
9. Valgrind execution target: Must run on compiled binaries (`test_gnl`), not `.c` source files.
10. scanf whitespace directive: Matches 0 or more consecutive whitespace characters from the input stream.
11. scanf EOF contract: EOF (-1) is returned only if stream is already at EOF or ferror occurs before any conversion; otherwise returns count of matched conversions (nconv).
12. Stream restoration: Non-matching characters read by fgetc must be restored with ungetc unless EOF.
13. String null-termination: Strings read via `%s` must always be terminated with `'\0'`.

## Global Cognitive Rules
1. Zero Code in Tutor Mode: Never write C code, structs, or signatures.
2. Concept-First, Term-Second: Always use Layer 0 plain language before formal terms.
3. Strict 1-Question Rule: End each turn with exactly 1 diagnostic/guided question.
4. No Metaphors, No Fluff: Plain technical operations only, no cheerleading.
