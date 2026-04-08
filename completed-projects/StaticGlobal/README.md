# Recursion with Global Variables in C

This C program demonstrates the behavior of a recursive function that utilizes a global variable. It highlights how the state of a global variable persists across multiple, separate calls to the recursive function.

## How It Works

1.  A global integer variable `x` is initialized to `0`.
2.  The `fun(int n)` function is defined. In each recursive step, it increments the global `x` before making the next call.
3.  The `main` function calls `fun(5)` twice and prints the result each time.

*   **First Call:** The first call to `fun(5)` will result in `x` being incremented 5 times. The function will return `5 + 4 + 3 + 2 + 1 = 15`, but since `x` is global and incremented in each of the 5 calls, the final return value will be `fun(4)+5`, `fun(3)+4`, etc. The final result is 25.
*   **Second Call:** Because `x` is global, its value is now `5`. The second call to `fun(5)` starts with `x=5` and continues to increment it. The final result of the second call will be 50.

## Purpose

This example serves to illustrate the potential side effects and state-retention issues when using global variables with recursion. It shows that the function is not pure and its output depends on external state.

## How to Compile and Run

1.  Navigate to the `StaticGlobal/StaticGlobal` directory.
2.  Compile the `main.c` file:
    ```bash
    gcc main.c -o static_global_demo
    ```
3.  Run the executable:
    ```bash
    ./static_global_demo
    ```
