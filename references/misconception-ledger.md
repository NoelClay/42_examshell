# Persistent ZPD Brain: Misconception Ledger & Master Domain Index

## Active Session Pointer
- Topic: `broken_gnl`
- State File: `references/zpd-states/broken_gnl.md`
- Active Phase: Complete (All tests passed)

## Consolidated Concepts
1. GNL 4-stage lifecycle: Buffer check -> Read until \n -> Return line -> Move leftover to front.
2. Pointer arithmetic: `tmp - b + 1` calculates slice length including newline directly from address difference.
3. Memory overlap: In-place buffer shifting requires `memmove` principles.
4. Unsigned underflow: `size_t` decrements never drop below zero (`i >= 0` is an infinite loop).
5. Dynamic memory append: Reallocation lifecycle (malloc new -> copy old & new -> free old -> assign).

## Global Cognitive Rules
1. Zero Code in Tutor Mode: Never write C code, structs, or signatures.
2. Concept-First, Term-Second: Always use Layer 0 plain language before formal terms.
3. Strict 1-Question Rule: End each turn with exactly 1 diagnostic/guided question.
4. No Metaphors, No Fluff: Plain technical operations only, no cheerleading.
