# Dynamic 2D Array Allocation in C

This project demonstrates two different methods for dynamically allocating a 2D array on the heap in C.

## Methods Demonstrated

1.  **Array of Pointers:**
    *   An array of integer pointers (`int *B[3]`) is created on the stack.
    *   Each element of this array is then assigned the address of a dynamically allocated 1D array on the heap.

2.  **Pointer to a Pointer:**
    *   A double pointer (`int **C`) is created.
    *   Memory is first allocated on the heap for an array of pointers.
    *   Then, a loop iterates through this pointer array, allocating memory on the heap for each row.

## Purpose

This code serves as an educational example for understanding how to work with multi-dimensional arrays when the size is not known at compile time. It highlights the different levels of indirection and memory mapping involved in each approach.

## How to Compile and Run

1.  Navigate to the `Recursion/Recursion` directory.
2.  Compile the `main.c` file:
    ```bash
    gcc main.c -o 2d_array_demo
    ```
3.  Run the executable:
    ```bash
    ./2d_array_demo
    ```
    *Note: The program allocates memory but does not produce any meaningful output as the allocated arrays are not initialized.*
