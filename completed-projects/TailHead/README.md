# Head Recursion Example in C

This C program provides a simple and clear example of head recursion.

## What is Head Recursion?

In head recursion, the recursive call is the first statement in the function. Any processing that the function does occurs *after* the recursive call, as the function is "returning" or "unwinding."

## How It Works

1.  The `fun(int n)` function is called with `n=3`.
2.  The function checks if `n > 0`. It is.
3.  It immediately calls `fun(n-1)`, which is `fun(2)`.
4.  This continues until `fun(0)` is called. The `n > 0` condition is false, and `fun(0)` returns.
5.  Now, `fun(1)` resumes. It executes `printf("%d ", n)`, printing `1`.
6.  `fun(2)` resumes and prints `2`.
7.  Finally, the original call `fun(3)` resumes and prints `3`.

The final output is `1 2 3`.

## Purpose

This program is a classic illustration of head recursion, demonstrating how actions can be delayed until the recursive stack unwinds. This is the opposite of tail recursion, where the processing happens before the recursive call.

## How to Compile and Run

1.  Navigate to the `TailHead/TailHead` directory.
2.  Compile the `main.c` file:
    ```bash
    gcc main.c -o head_recursion_demo
    ```
3.  Run the executable:
    ```bash
    ./head_recursion_demo
    ```
