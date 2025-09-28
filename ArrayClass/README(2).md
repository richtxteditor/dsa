# Simple Array Class in C++

This project is an introductory step toward object-oriented data structure implementation in C++. It encapsulates basic array functionalities within a C++ `Array` class, managing memory with a raw pointer and manual `new`/`delete` operations in the constructor and destructor.

## Features

*   **Class-Based:** Wraps the array data (`int *A`), `size`, and `length` into a class.
*   **Constructor/Destructor:** Handles basic memory allocation and deallocation.
*   **Core Methods:**
    *   `Display()`: Prints the elements of the array.
    *   `Insert()`: Inserts an element at a specified index.
    *   `Delete()`: Deletes an element from a specified index.

## How to Compile and Run

1.  Navigate to the `ArrayClass/ArrayClass` directory.
2.  Compile the `main.cpp` file using a C++ compiler like `g++`:
    ```bash
    g++ main.cpp -o array_class_demo
    ```
3.  Run the executable:
    ```bash
    ./array_class_demo
    ```
