# C++ Data Structures: Dynamic Array Implementation

## Project Overview

This project implements a dynamic array class in C++ from first principles. It serves as a foundational exercise for understanding data structure mechanics, memory management, and algorithm implementation. The goal is not to replace standard library containers like `std::vector`, but to learn how such containers operate under the hood.

The code provides a single `Array` class that encapsulates array data and operations, along with an interactive command-line menu for testing various functionalities. The implementation covers basic CRUD operations, search algorithms, set operations, and more complex analysis algorithms for finding missing elements and duplicates. A detailed breakdown of the time and space complexity of each function is available in the `ArrayCPP/ArrayCPP/complexity_docs.md` file.

## Features Implemented

The `Array` class supports a wide range of operations, categorized below:

### 1. Core Functionality & Memory Management

* **Dynamic Sizing:** The array distinguishes between its total allocated `size` and its current `length` (number of elements).
* **The Rule of Five:** Full implementation of modern C++ memory management principles to ensure safe copying, moving, and destruction of objects.
  * **Destructor:** Frees dynamically allocated memory.
  * **Copy Constructor:** Performs a deep copy for safe object duplication.
  * **Copy Assignment Operator:** Safely handles assignment between existing objects (`arr1 = arr2`).
  * **Move Constructor & Move Assignment Operator:** Efficiently transfers resources from temporary objects without costly copies.

### 2. Basic Array Operations

* **`Append(int x)`:** Adds an element to the end of the array (time complexity: O(1)).
* **`Insert(size_t index, int x)`:** Inserts an element at a specified index, shifting existing elements (time complexity: O(n)).
* **`Delete(size_t index)`:** Removes an element from a specified index, shifting remaining elements (time complexity: O(n)).
* **`Get(size_t index)` / `Set(size_t index, int x)`:** Accessor and mutator methods for elements at a specific index.

### 3. Search Algorithms

* **`LinearSearch(int key)`:** Standard sequential search (time complexity: O(n)). Includes a move-to-front optimization.
* **`BinarySearchLoop(int key)`:** Efficient search for **sorted arrays** (time complexity: O(log n)).

### 4. Array Analysis & Manipulation

* **Aggregate Functions:** `Sum()`, `Avg()`, `Max()`, `Min()`.
* **State Check:** `isSorted()` verifies if the array elements are in ascending order.
* **Reversal Algorithms:** Includes both an out-of-place `Reverse()` (using an auxiliary array) and an in-place `ReverseInPlace()` (using a two-pointer swap technique).
* **Sorted Insertion:** `InsertSort(int x)` inserts an element while maintaining the array's sorted order.
* **Partitioning:** `Rearrange()` segregates negative and positive numbers within the array.

### 5. Set Operations (for Sorted Arrays)

* **`Merge(const Array& arr2)`:** Combines two sorted arrays into a single new sorted array.
* **`Union(const Array& arr2)`:** Creates a new array containing unique elements from both source arrays.
* **`Intersection(const Array& arr2)`:** Creates a new array containing only elements common to both source arrays.
* **`Difference(const Array& arr2)`:** Creates a new array containing elements present in the first array but not in the second.

### 6. Advanced Algorithms

* **Finding Missing Elements (Sorted):** Detects single or multiple missing numbers from a sorted sequence based on expected index-value differences.
* **Finding Missing Elements (Unsorted):**
  * **XOR Method:** Efficiently finds a single missing element in an unsorted sequence without sorting.
  * **Hash Method:** Uses a boolean hash table (bitset) to identify multiple missing elements within the range of the array's values.
* **Finding Duplicates (Sorted):** Identifies duplicate elements and their frequencies in a sorted array by comparing adjacent elements.

## Technical Highlights and C++ Concepts

This code demonstrates several key C++ programming concepts:

* **RAII (Resource Acquisition Is Initialization):** The constructor acquires the memory resource (`new int[size]`), and the destructor releases it (`delete[] A`), encapsulating resource lifetime within the object's scope.
* **Exception Handling:** Uses `std::overflow_error` and `std::out_of_range` to signal runtime errors like attempting to append to a full array or accessing an invalid index.
* **Safe Return Values:** Employs `std::optional` for functions like `Get()` and search operations. This avoids returning magic numbers (like -1) to indicate failure and forces the caller to check if a value was successfully returned.

## How to Compile and Run

1. Ensure you have a C++ compiler (like g++ or clang) that supports C++17 or later.
2. Compile the code from your terminal:

    ```bash
    g++ main.cpp array.cpp -o array_demo -std=c++17 -Wall
    ```

3. Run the executable:

    ```bash
    ./array_demo
    ```

4. Follow the interactive menu prompts to test different array operations.

---

## Project Status and Next Steps

For an interactive, up-to-date view of the project plan and study progress, please see the **[Consolidated Study Plan](zCheck_List/index.html)**.

### Completed Milestones
- Implemented dynamic resizing to handle overflow automatically.
- Split monolithic code into `.h` (header) and `.cpp` (source) files.
- Added a simple unit test function and set up an XCTest target.
- Replaced `using namespace std;` with specific `using` declarations.
- Implemented and tested various duplicate-finding methods.
- Set up a simple build system with CMake.

### Current Goals
- Implement Iterators to make the `Array` class compatible with range-based `for` loops.
- Convert the `Array` class to a template class to support generic data types (e.g., `Array<T>`).
- Implement additional sorting algorithms (e.g., Merge Sort, Quick Sort) as methods of the `Array` class.

