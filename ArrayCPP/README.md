# Advanced C++ Dynamic Array

This project provides a robust and feature-rich implementation of a dynamic array in C++. It is designed to demonstrate modern C++ best practices, including comprehensive memory management, exception handling, and the use of `std::optional` for safe data retrieval.

The implementation is split into a header file (`array.h`) for the class definition and a source file (`array.cpp`) for the implementation, with a `main.cpp` file that provides an interactive command-line interface for testing.

## Key Features

### 1. Modern C++ Memory Management (The Rule of Five)

*   **Destructor:** Properly deallocates memory.
*   **Copy Constructor & Copy Assignment:** Implements deep copying to prevent data corruption.
*   **Move Constructor & Move Assignment:** Provides efficient resource transfer from temporary objects.

### 2. Robustness and Safety

*   **Dynamic Resizing:** The array automatically grows in size when it runs out of space, preventing overflow errors.
*   **Exception Handling:** Uses `std::out_of_range` and `std::logic_error` to signal invalid operations.
*   **`std::optional`:** Search and `Get` functions return `std::optional` to safely handle cases where a value may not be found or an index is invalid, avoiding the use of magic numbers like `-1`.

### 3. Comprehensive Functionality

*   **Core Operations:** `Append`, `Insert`, `Delete`, `Get`, `Set`.
*   **Search Algorithms:** `LinearSearch` (with move-to-front optimization) and `BinarySearchLoop`.
*   **Array Analysis:** `Max`, `Min`, `Sum`, `Avg`, `isSorted`.
*   **Manipulation:** `Reverse` (out-of-place), `ReverseInPlace`, `InsertSort`, and `Rearrange` (partitioning).
*   **Set Operations (for sorted arrays):** `Merge`, `Union`, `Intersection`, `Difference`.
*   **Advanced Algorithms:**
    *   Finding single or multiple missing elements in both sorted and unsorted arrays.
    *   Finding duplicate elements using various techniques (for sorted and unsorted arrays).

## How to Compile and Run

1.  Navigate to the `ArrayCPP/ArrayCPP` directory.
2.  Compile the source files using a C++17 compatible compiler:
    ```bash
    g++ -std=c++17 main.cpp array.cpp -o advanced_array_demo
    ```
3.  Run the executable:
    ```bash
    ./advanced_array_demo
    ```
4.  Follow the interactive menu to explore the array's features.
