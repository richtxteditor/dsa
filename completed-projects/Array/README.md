# Basic Dynamic Array in C

This project is a simple implementation of a dynamic array data structure in C. It uses a `struct` to encapsulate the array data, its size, and its current length, with all operations performed through functions that manipulate this struct.

## Features

*   **Dynamic Memory:** The array's storage is allocated on the heap using `malloc`.
*   **Core Operations:**
    *   `Display()`: Prints all elements in the array.
    *   `Append()`: Adds an element to the end of the array.
    *   `Insert()`: Inserts an element at a given index.
    *   `Delete()`: Removes an element from a given index.
*   **Search Algorithms:**
    *   `LinearSearch()`: A simple sequential search.
    *   `BinarySearchLoop()`: An iterative binary search for sorted arrays.
    *   `RecursiveBinarySearch()`: A recursive binary search.
*   **Array Manipulation:**
    *   `Reverse()`: Reverses the array (out-of-place).
    *   `RecursiveReverse()`: Reverses the array (in-place).
    *   `InsertSort()`: Inserts an element while maintaining sorted order.
    *   `isSorted()`: Checks if the array is sorted.
    *   `Rearrange()`: Partitions the array with negative numbers on one side and positive numbers on the other.
*   **Set Operations (for sorted arrays):**
    *   `Merge()`: Merges two sorted arrays.
    *   `Union()`: Creates a union of two sorted arrays.
    *   `Intersection()`: Creates an intersection of two sorted arrays.
    *   `Difference()`: Creates a difference of two sorted arrays.

## How to Compile and Run

1.  Navigate to the `Array/Array` directory.
2.  Compile the `main.c` file using a C compiler like `gcc`:
    ```bash
    gcc main.c -o array_demo
    ```
3.  Run the executable:
    ```bash
    ./array_demo
    ```
4.  Follow the interactive menu to test the array operations.
