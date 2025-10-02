# DSA-Project: C++ Data Structures and Algorithms

This project provides robust, feature-rich, and generic implementations of common data structures and algorithms in C++.

## Data Structures

### Generic Advanced C++ Dynamic Array

This project provides a robust, feature-rich, and generic implementation of a dynamic array in C++ using templates (`Array<T>`). This design allows the array to store a wide variety of data types, such as `int`, `double`, or `std::string`, making it a highly reusable data structure.

The implementation is a header-only library (`ds/array.h`), which is standard practice for C++ templates. A `main.cpp` file provides an interactive command-line interface for demonstrating and testing the features of an `Array<int>`.

#### Key Features

##### 1. Generic and Modern C++ Integration

*   **Template-Based Design:** Built as a template class (`Array<T>`), allowing it to be instantiated with any data type that supports standard comparison and copy operations.
*   **Iterator Support:** The class includes `begin()` and `end()` methods, making it fully compatible with C++'s range-based `for` loops and many Standard Library algorithms.
    ```cpp
    Array<std::string> arr;
    arr.Append("Hello");
    arr.Append("World");
    
    for (const auto& value : arr) {
        std::cout << value << " "; // Prints "Hello World "
    }
    ```

##### 2. Modern C++ Memory Management (The Rule of Five)

*   **Destructor:** Properly deallocates memory.
*   **Copy Constructor & Copy Assignment:** Implements deep copying to prevent data corruption.
*   **Move Constructor & Move Assignment:** Provides efficient resource transfer from temporary objects.

##### 3. Robustness and Safety

*   **Dynamic Resizing:** The array automatically grows in size when it runs out of space, preventing overflow errors.
*   **Exception Handling:** Uses `std::out_of_range` and `std::logic_error` to signal invalid operations.
*   **`std::optional`:** Search and `Get` functions return `std::optional<T>` to safely handle cases where a value may not be found or an index is invalid, avoiding the use of magic numbers like `-1`.

##### 4. Comprehensive Functionality

*   **Core Operations:** `Append`, `Insert`, `Delete`, `Get`, `Set`.
*   **Search Algorithms:** `LinearSearch` (with move-to-front optimization) and `BinarySearchLoop`.
*   **Array Analysis:** `Max`, `Min`, `Sum`, `Avg`, `isSorted`.
*   **Manipulation:** `Reverse` (out-of-place), `ReverseInPlace`, `InsertSort`, and `Rearrange` (partitioning for numeric types).
*   **Set Operations (for sorted arrays):** `Merge`, `Union`, `Intersection`, `Difference`.
*   **Advanced Algorithms:**
    *   Finding single or multiple missing elements in both sorted and unsorted numeric arrays.
    *   Finding duplicate elements using various techniques (for sorted and unsorted arrays).

## Algorithms

### String Algorithms

A collection of string manipulation algorithms are available in `algo/strings.h` and implemented in `algo/strings.cpp`.

*   **`reverse_string`**: Reverses a string in-place.
*   **`is_palindrome`**: Checks if a string is a palindrome.
*   **`find_duplicates_hashing`**: Finds duplicate characters in a string using a hash map.
*   **`find_duplicates_bitwise`**: Finds duplicate characters in a string using bitwise operations.
*   **`are_anagrams_hash`**: Checks if two strings are anagrams using a hash map.
*   **`are_anagrams_bitwise`**: Checks if two strings are anagrams using bitwise operations.

## How to Compile and Run

1.  Navigate to the project's root directory.
2.  Compile the `main.cpp` source file using a C++20 compatible compiler.

    ```bash
    g++ -std=gnu++20 main.cpp algo/strings.cpp -o advanced_array_demo
    ```
    *Note: Because `Array` is a template class, all of its implementation is contained within the `ds/array.h` header file. There is no `array.cpp` file to compile.*

3.  Run the executable:
    ```bash
    ./advanced_array_demo
    ```
4.  The program will first demonstrate the string algorithms and then provide an interactive menu to explore the features of an `Array<int>`.
