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

## Next Steps: An Integrated Learning Plan

For an interactive, checkable version of this study plan, please see the **[Consolidated Study Plan](zCheck_List/index.html)**.

This plan integrates the Udemy course **"Data Structures and Algorithms using C++"** with the industry-standard interview prep book **"Cracking the Coding Interview" (CTCI)**.

The learning cycle for each new data structure is:

1. **Learn the Theory (Udemy):** Watch the course lectures to understand the concept, operations, and Big O complexity.
2. **Implement from Scratch (IDE):** Build the data structure yourself to solidify your understanding.
3. **Reinforce and Strategize (CTCI):** Read the corresponding chapter in CTCI for an interview-focused review of key points and trade-offs.
4. **Practice with Problems (CTCI):** Solve the chapter problems to apply your knowledge.

---

### **Step 1: Strings and Matrices** (Natural extension of Arrays)

* **Udemy:** Progress to the sections on "Strings" and "Matrices."
* **Personal Implementation:** Implement common string algorithms (e.g., palindrome check, permutation check) and create a simple `Matrix` class or use `vector<vector<int>>` for matrix rotation and search algorithms.


* **CTCI Reading:** **Chapter 1: "Arrays and Strings."**
* **CTCI Practice:** "Is Unique", "Check Permutation", "URLify", "String Compression", "Zero Matrix".

### **Step 2: Linked Lists** (The first major conceptual leap)

* **Udemy:** Watch the lectures on Singly, Doubly, and Circular Linked Lists. Focus on pointer manipulation.
* **Personal Implementation:** Create a `LinkedList` class from scratch with a private `Node` struct. Implement `append`, `insert`, `delete`, `display`, and `reverse`.
* **CTCI Reading:** **Chapter 2: "Linked Lists."** Internalize the **"Runner" (fast/slow pointer) technique**.
* **CTCI Practice:** "Remove Dups", "Return Kth to Last", "Delete Middle Node", "Partition", "Sum Lists", "Intersection".

### **Step 3: Stacks and Queues** (Abstract Data Types)

* **Udemy:** Cover the theory of Stacks (LIFO) and Queues (FIFO).
* **Personal Implementation:** Implement both `Stack` and `Queue` classes. Do this twice: once using an array as the backing store, and again using your `LinkedList`. This demonstrates the power of abstraction.
* **CTCI Reading:** **Chapter 3: "Stacks and Queues."**
* **CTCI Practice:** "Three in One", "Stack Min", "Stack of Plates", "Queue via Stacks", "Animal Shelter".

### **Step 4: Trees** (Moving to non-linear data)

* **Udemy:** Cover Binary Trees, Binary Search Trees (BSTs), and Heaps. Master tree **traversals (In-order, Pre-order, Post-order, Level-order)**.
* **Personal Implementation:**
    1. Create a `BinarySearchTree` class. Implement `insert`, `search`, `delete`, and the traversal algorithms using recursion.
    2. Implement a `MinHeap` or `MaxHeap` class using a vector/array as the underlying structure.
* **CTCI Reading:** **Chapter 4: "Trees and Graphs."** Focus on the tree sections first.
* **CTCI Practice:** "Minimal Tree", "List of Depths", "Check Balanced", "Validate BST", "Successor", "First Common Ancestor".

### **Step 5: Graphs and Advanced Algorithms**

* **Udemy:** Progress to advanced sorting (Merge Sort, Quick Sort) and Graphs (representations, BFS, DFS).
* **Personal Implementation:** Implement Merge Sort and Quick Sort. Create a `Graph` class (supporting both Adjacency List and Matrix representations) and implement Breadth-First Search and Depth-First Search.
* **CTCI Reading:** The rest of **Chapter 4 ("Trees and Graphs")** and **Chapter 10 ("Sorting and Searching")**.
* **CTCI Practice:**
  * **Graphs:** "Route Between Nodes", "Build Order", "Shortest Path".
  * **Sorting:** "Sorted Merge", "Group Anagrams", "Search in Rotated Array".

### **Problem-Solving Mindset**

When tackling problems from CTCI, adopt a "whiteboard" approach:

1. **Clarify:** Understand the problem, constraints, and edge cases.
2. **Brute-Force:** Formulate the simplest, most obvious solution first.
3. **Optimize:** Analyze the bottlenecks (time or space) of the brute-force solution. Can a better data structure (like a hash map) or algorithm be used?
4. **Whiteboard:** Sketch out the logic of your optimized approach before writing a single line of code.
5. **Code:** Implement your final, optimized solution.
