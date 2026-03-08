# CS3339 Homework 2 - Floating-Point Overflow Checker

## Team Members
- Nathaniel Jones

## Description
This program detects potential floating-point overflow in C++ loop constructs. Given a loop bound and a loop counter as 32-bit floating-point values, it determines whether the counter's increment will be lost due to insufficient precision in the fraction segment of the IEEE 754 representation.

## How to Compile
```bash
g++ -o fp_overflow_checker fp_overflow_checker.cpp
```

## How to Run
```bash
./fp_overflow_checker <loop_bound> <loop_counter>
```

**Arguments:**
- `loop_bound` — a positive floating-point value representing the loop's upper bound
- `loop_counter` — a positive floating-point value representing the loop's increment

**Examples:**
```bash
./fp_overflow_checker 1e+08 1.0
./fp_overflow_checker 1e+05 2.0
./fp_overflow_checker 1.4567 3.14
```
