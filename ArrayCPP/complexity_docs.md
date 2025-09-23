# Complexity Documentation for ArrayCPP

This document explains the **time complexity** and **space complexity** of each public method
and key private helper within `Array` as implemented in `main.cpp`.

---

## Constructor & Rule of Five

- **Array(size_t sz = 10)**
  - Time Complexity: O(n) (for allocating initial array of size `sz`)
  - Space Complexity: O(n) (size of allocated array)
- **Destructor (~Array)**: O(1)
- **Copy Constructor**: O(n)
- **Copy Assignment**: O(n)
- **Move Constructor**: O(1)
- **Move Assignment**: O(1)

---

## Basic Operations

- **Display()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **Append(int x)**
  - Time Complexity: O(1)
  - Space Complexity: O(1)

- **Insert(size_t index, int x)**
  - Time Complexity: O(n) (shifts elements to make space)
  - Space Complexity: O(1)

- **Delete(size_t index)**
  - Time Complexity: O(n) (shifts elements after deletion)
  - Space Complexity: O(1)

- **Get(size_t index)**
  - Time Complexity: O(1)
  - Space Complexity: O(1)

- **Set(size_t index, int x)**
  - Time Complexity: O(1)
  - Space Complexity: O(1)

---

## Search Operations

- **LinearSearch(int key)**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **BinarySearchLoop(int key)**
  - Time Complexity: O(log n)
  - Space Complexity: O(1)

---

## Info / Aggregate Operations

- **GetLength(), GetSize()**
  - Time Complexity: O(1)
  - Space Complexity: O(1)

- **Max()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **Min()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **Sum()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **Avg()**
  - Time Complexity: O(n) (depends on Sum())
  - Space Complexity: O(1)

- **isSorted()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

---

## Modify Operations

- **Reverse()**
  - Time Complexity: O(n)
  - Space Complexity: O(n) (extra temporary array)

- **ReverseInPlace()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **InsertSort(int x)**
  - Time Complexity: O(n) (shifting elements)
  - Space Complexity: O(1)

- **Rearrange()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

---

## Set Operations (Require Sorted Arrays)

- **Merge(const Array& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(n + m)

- **Union(const Array& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(n + m)

- **Intersection(const Array& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(min(n, m))

- **Difference(const Array& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(n)

Where:

- `n` = length of first array
- `m` = length of second array

---

## Missing Element Operations

- **FindSingleMissingElementSorted()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **FindSingleMissingElementUnsortedOptimal()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **FindMultipleMissingElementsSorted()**
  - Time Complexity: O(n + k) (where k is the number of missing elements)
  - Space Complexity: O(1)

- **FindMultipleMissingElementsHash()**
  - Time Complexity: O(n + range_size)
  - Space Complexity: O(range_size)
    - `range_size` = (max_val - min_val + 1)

---

## Duplicate Operations

- **FindDuplicatesSorted()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **FindDuplicatesUnsorted()** *(calls hashing internally)*
  - Time Complexity: O(n + k)
    - k = range of values (max_val - min_val)
  - Space Complexity: O(k)

- **FindDuplicatesHashing()**
  - Time Complexity: O(n + k)
  - Space Complexity: O(k)

---

## Helper Function

- **create_and_fill_array()**
  - Time Complexity: O(n)
  - Space Complexity: O(n)

---

## Main Menu Logic

- **Overall Program Complexity**:
  - Depends on the chosen menu option.
  - Most operations are O(n) or better.
