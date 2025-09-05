# Mastering Data Structures & Algorithms using C and C++

## Dynamic Array Implementation

## Project Overview

This project implements a dynamic array class in C++ from first principles. It serves as a foundational exercise for understanding data structure mechanics, memory management, and algorithm implementation. The goal is not to replace standard library containers like `std::vector`, but to learn how such containers operate under the hood.

The code provides a single `Array` class that encapsulates array data and operations, along with an interactive command-line menu for testing various functionalities. The implementation covers basic CRUD operations, search algorithms, set operations, and more complex analysis algorithms for finding missing elements and duplicates.

## Features Implemented

The `Array` class supports a wide range of operations, categorized below:

### 1. Core Functionality & Memory Management

*   **Dynamic Sizing:** The array distinguishes between its total allocated `size` and its current `length` (number of elements).
*   **The Rule of Five:** Full implementation of modern C++ memory management principles to ensure safe copying, moving, and destruction of objects.
    *   **Destructor:** Frees dynamically allocated memory.
    *   **Copy Constructor:** Performs a deep copy for safe object duplication.
    *   **Copy Assignment Operator:** Safely handles assignment between existing objects (`arr1 = arr2`).
    *   **Move Constructor & Move Assignment Operator:** Efficiently transfers resources from temporary objects without costly copies.

### 2. Basic Array Operations

*   **`Append(int x)`:** Adds an element to the end of the array (time complexity: O(1)).
*   **`Insert(size_t index, int x)`:** Inserts an element at a specified index, shifting existing elements (time complexity: O(n)).
*   **`Delete(size_t index)`:** Removes an element from a specified index, shifting remaining elements (time complexity: O(n)).
*   **`Get(size_t index)` / `Set(size_t index, int x)`:** Accessor and mutator methods for elements at a specific index.

### 3. Search Algorithms

*   **`LinearSearch(int key)`:** Standard sequential search (time complexity: O(n)). Includes a move-to-front optimization.
*   **`BinarySearchLoop(int key)`:** Efficient search for **sorted arrays** (time complexity: O(log n)).

### 4. Array Analysis & Manipulation

*   **Aggregate Functions:** `Sum()`, `Avg()`, `Max()`, `Min()`.
*   **State Check:** `isSorted()` verifies if the array elements are in ascending order.
*   **Reversal Algorithms:** Includes both an out-of-place `Reverse()` (using an auxiliary array) and an in-place `ReverseInPlace()` (using a two-pointer swap technique).
*   **Sorted Insertion:** `InsertSort(int x)` inserts an element while maintaining the array's sorted order.
*   **Partitioning:** `Rearrange()` segregates negative and positive numbers within the array.

### 5. Set Operations (for Sorted Arrays)

*   **`Merge(const Array& arr2)`:** Combines two sorted arrays into a single new sorted array.
*   **`Union(const Array& arr2)`:** Creates a new array containing unique elements from both source arrays.
*   **`Intersection(const Array& arr2)`:** Creates a new array containing only elements common to both source arrays.
*   **`Difference(const Array& arr2)`:** Creates a new array containing elements present in the first array but not in the second.

### 6. Advanced Algorithms

*   **Finding Missing Elements (Sorted):** Detects single or multiple missing numbers from a sorted sequence based on expected index-value differences.
*   **Finding Missing Elements (Unsorted):**
    *   **XOR Method:** Efficiently finds a single missing element in an unsorted sequence without sorting.
    *   **Hash Method:** Uses a boolean hash table (bitset) to identify multiple missing elements within the range of the array's values.
*   **Finding Duplicates (Sorted):** Identifies duplicate elements and their frequencies in a sorted array by comparing adjacent elements.

## Technical Highlights and C++ Concepts

This code demonstrates several key C++ programming concepts:

*   **RAII (Resource Acquisition Is Initialization):** The constructor acquires the memory resource (`new int[size]`), and the destructor releases it (`delete[] A`), encapsulating resource lifetime within the object's scope.
*   **Exception Handling:** Uses `std::overflow_error` and `std::out_of_range` to signal runtime errors like attempting to append to a full array or accessing an invalid index.
*   **Safe Return Values:** Employs `std::optional` for functions like `Get()` and search operations. This avoids returning magic numbers (like -1) to indicate failure and forces the caller to check if a value was successfully returned.

## How to Compile and Run

1.  Ensure you have a C++ compiler (like g++ or clang) that supports C++17 or later.
2.  Compile the code from your terminal:
    ```bash
    g++ main.cpp -o array_demo -std=c++17 -Wall
    ```
3.  Run the executable:
    ```bash
    ./array_demo
    ```
4.  Follow the interactive menu prompts to test different array operations.

---

## Next Steps in Mastering Data Structures and Algorithms

### 1. Expanding Array-Based Structures

*   **Strings:** You'll likely dive deeper into string manipulation algorithms, treating strings as arrays of characters. Topics include finding duplicates in strings, checking for anagrams, and permutation algorithms.
*   **Matrices:** Move from single-dimensional to two-dimensional arrays. Key topics here involve matrix representation (e.g., lower triangular, diagonal matrices) and operations like matrix addition and multiplication.

### 2. Introduction to Linked Data Structures

This is the most critical next step. Arrays have a major limitation: insertion and deletion are slow (O(n)) because elements must be shifted. Linked lists solve this problem.

*   **Linked Lists:** You will learn to implement a `Node` structure and connect nodes using pointers.
    *   **Singly Linked List:** Basic operations (insert, delete, search, reverse).
    *   **Circular Linked List:** The last node points back to the first node.
    *   **Doubly Linked List:** Nodes have pointers to both the next and previous elements, enabling efficient backward traversal and deletion.

### 3. Abstract Data Types (ADTs)

Once you have both arrays and linked lists, you'll implement ADTs using these underlying structures.

*   **Stacks:** A Last-In, First-Out (LIFO) structure. You will implement `push()`, `pop()`, and `peek()` operations, first using an array (like this project) and then using a linked list. Applications include parenthesis matching and expression conversion (infix to postfix).
*   **Queues:** A First-In, First-Out (FIFO) structure. You'll implement `enqueue()` and `dequeue()`. This requires careful management when implemented with a standard array (leading to circular queues) or more straightforward implementation with a linked list.

### 4. Non-Linear Data Structures: Trees and Heaps

After mastering linear structures, you'll move to hierarchical data.

*   **Binary Trees:** A foundational non-linear structure where each node has at most two children. You'll learn traversal algorithms: **Preorder, Inorder, Postorder, and Level Order**.
*   **Binary Search Trees (BST):** A sorted binary tree where all elements to the left of a node are smaller, and all elements to the right are larger. This structure combines fast search (O(log n) average) with efficient insertion/deletion.
*   **Heaps:** A specialized tree (usually a binary heap) where nodes satisfy the heap property (e.g., parent node is always larger than child nodes). Heaps are crucial for implementing **Priority Queues** and for **Heap Sort**.
*   **AVL Trees / Red-Black Trees:** Self-balancing BSTs that guarantee O(log n) performance even in worst-case scenarios by performing rotations during insertion and deletion.

### 5. Advanced Topics

*   **Hashing:** A deeper dive into hash tables, collision resolution strategies (linear probing, quadratic probing, chaining), and time-space tradeoffs.
*   **Sorting Algorithms:** A comprehensive study of different sorting techniques beyond simple insertion sort, including **Merge Sort**, **Quick Sort**, and **Radix Sort**, analyzing their time complexity and stability.
*   **Graphs:** The most versatile data structure, representing networks. You'll learn graph representations (adjacency matrix, adjacency list) and fundamental algorithms like **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**, as well as algorithms for finding minimum spanning trees (Kruskal's, Prim's) and shortest paths (Dijkstra's).