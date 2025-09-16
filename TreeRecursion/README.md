# Tree Recursion Example in C

This C program demonstrates the concept of tree recursion.

## What is Tree Recursion?

Tree recursion occurs when a function makes more than one recursive call to itself within its execution path. This pattern of calls forms a tree-like structure.

## How It Works

1.  The `fun(int n)` function is called with `n=3`.
2.  It prints the current value of `n`.
3.  It then calls itself twice: `fun(n-1)` and `fun(n-1)`.

This process creates a binary tree of function calls. The trace of execution is as follows:

*   `fun(3)` prints `3` and calls `fun(2)` twice.
*   Each `fun(2)` prints `2` and calls `fun(1)` twice.
*   Each `fun(1)` prints `1` and calls `fun(0)` twice.
*   `fun(0)` is the base case and does nothing.

The resulting output will be: `3 2 1 1 2 1 1`

## Purpose

This program serves as a classic example of tree recursion, which is foundational to many algorithms related to tree data structures (like binary tree traversals) and more complex problems like the Fibonacci sequence.

## How to Compile and Run

1.  Navigate to the `TreeRecursion/TreeRecursion` directory.
2.  Compile the `main.c` file:
    ```bash
    gcc main.c -o tree_recursion_demo
    ```
3.  Run the executable:
    ```bash
    ./tree_recursion_demo
    ```
