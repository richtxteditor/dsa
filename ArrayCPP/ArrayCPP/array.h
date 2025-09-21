//
//  array.h
//  
//
//  Created by richie on 9/7/25.
//

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

class Array {
private:
    int *A;         // pointer to heap array
    size_t size;       // allocated size
    size_t length;     // num of elements currently in array
    
    // helper for swapping elements
    void swap(int *x, int *y);
    void resize();
    
public:
    // --- Constructor ---
    
    // can throw std::bad_alloc if 'new' afils
    Array(size_t sz = 10);
    
    // --- Rule of Five (memory management) ---
    ~Array();
    Array(const Array& other); // 2. Copy Constructor (Deep Copy)
    Array& operator = (const Array& other); // 3. Copy Assignment
    Array(Array&& other) noexcept; // 3. Move Constructor
    Array& operator = (Array&& other) noexcept; // 5. Move Assignment
    
    // --- Basic Operations ---
    void Display() const;
    void Append(int x);                             // Add to end
    void Insert(size_t index, int x);               // Insert at index (shifts elements)
    int Delete(size_t index);                       // delete from index (shifts elements)
    std::optional<int> Get(size_t  index) const;    // Get element at index
    void Set(size_t index, int x);                  // Set element at index
    
    // --- Search Operations ---
    std::optional<size_t> LinearSearch(int key);      // O(n) - Unsorted/Sorted
    std::optional<size_t> BinarySearchLoop(int key) const;  // O(log n) - Requires Sorted Array
    
    // --- Info / Aggregate Operations ---
    size_t GetLength() const { return length; }
    size_t GetSize() const { return size; }     // Get allocated size
    int Max() const;                            // O(n)
    int Min()const;                             // O(n)
    long long Sum() const;                      // O(n)
    double Avg() const;                                // O(n)
    bool isSorted() const;                             // O(n) - sort check
    
    // --- Modify Operations ---
    void Reverse();                 // O(n) - Creates a temporary array
    void ReverseInPlace();          // O(n) - Swaps elements in place (formerly RecursiveReverse)
    void InsertSort(int x);         // Insert element maintaining sorted order O(n)
    void Rearrange();               // Moves negative elements before positive O(n)
    
    // --- Set Operations (Require Sorted Arrays for Efficiency) ---
    Array Merge(const Array& arr2) const;           // Merge 2 sorted arrays
    Array Union(const Array& arr2) const;           // Union of 2 sorted arrays
    Array Intersection(const Array& arr2) const;    // Intersection of 2 sorted arrays
    Array Difference(const Array& arr2) const;      // Difference (this - arr2) '     '
    
    // --- Missing Element Operations ---
    std::optional<int> FindSingleMissingElementSorted() const; // requires sorted array (difference method)
    std::optional<int> FindSingleMissingElementUnsortedOptimal() const; // Works on UNSORTED array (XOR method)
    void FindMultipleMissingElementsSorted() const; // Requires SORTED array (Difference method)
    void FindMultipleMissingElementsHash() const; // Works on UNSORTED array (Hash method)


    void FindDuplicatesSorted() const;
    std::vector<std::pair<int, int>> FindDuplicatesUnsorted_BruteForce();
    void FindDuplicatesHashing() const;
    void CountDuplicates() const;
    
    std::optional<std::pair<int, int>> PairWithSum_Sorted(int k) const;
    std::optional<std::pair<int, int>> PairWithSum_Hashing(int k) const;
    std::optional<std::pair<int, int>> FindMinMax() const;
};

#endif // ARRAY_H
