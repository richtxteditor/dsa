# Complexity Documentation for DSA-Project

This document explains the **time complexity** and **space complexity** of each public method
and key private helper within the `Array<T>` class and the functions in `strings.cpp`.

---

## `Array<T>` Class

### Constructor & Rule of Five

- **Array(size_t sz = 10)**
  - Time Complexity: O(sz) (for allocating initial array of size `sz`)
  - Space Complexity: O(sz) (size of allocated array)
- **Destructor (~Array)**: O(1)
- **Copy Constructor**: O(n)
- **Copy Assignment**: O(n)
- **Move Constructor**: O(1)
- **Move Assignment**: O(1)

---

### Basic Operations

- **Display()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **Append(const T& x)**
  - Time Complexity: Amortized O(1). O(n) in the worst case when resizing is needed.
  - Space Complexity: O(1)

- **Insert(size_t index, const T& x)**
  - Time Complexity: O(n) (shifts elements to make space)
  - Space Complexity: O(1)

- **Delete(size_t index)**
  - Time Complexity: O(n) (shifts elements after deletion)
  - Space Complexity: O(1)

- **Get(size_t index)**
  - Time Complexity: O(1)
  - Space Complexity: O(1)

- **Set(size_t index, const T& x)**
  - Time Complexity: O(1)
  - Space Complexity: O(1)

---

### Search Operations

- **LinearSearch(const T& key)**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **BinarySearchLoop(const T& key)**
  - Time Complexity: O(log n)
  - Space Complexity: O(1)

---

### Info / Aggregate Operations

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

### Modify Operations

- **Reverse()**
  - Time Complexity: O(n)
  - Space Complexity: O(n) (extra temporary array)

- **ReverseInPlace()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **InsertSort(const T& x)**
  - Time Complexity: O(n) (shifting elements)
  - Space Complexity: O(1)

- **Rearrange()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

---

### Set Operations (Require Sorted Arrays)

- **Merge(const Array<T>& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(n + m)

- **Union(const Array<T>& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(n + m)

- **Intersection(const Array<T>& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(min(n, m))

- **Difference(const Array<T>& arr2)**
  - Time Complexity: O(n + m)
  - Space Complexity: O(n)

Where:

- `n` = length of first array
- `m` = length of second array

---

### Numeric-Specific Algorithms

- **FindSingleMissingElementSorted()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **FindMultipleMissingElementsSorted()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **FindSingleMissingElementUnsortedOptimal()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **FindMultipleMissingElementsHash()**
  - Time Complexity: O(n + range_size)
  - Space Complexity: O(range_size)
    - `range_size` = (max_val - min_val + 1)

- **FindDuplicatesSorted()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **FindDuplicatesHashing()**
  - Time Complexity: O(n)
  - Space Complexity: O(n) in the worst case (all unique elements)

- **FindDuplicatesUnsorted_BruteForce()**
  - Time Complexity: O(n^2)
  - Space Complexity: O(1) (excluding space for duplicates vector)

- **PairWithSum_Sorted(const T& k)**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **PairWithSum_Hashing(const T& k)**
  - Time Complexity: O(n)
  - Space Complexity: O(n) in the worst case

- **FindMinMax()**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

---

## `strings.cpp` Functions

- **reverse_string(std::string& s)**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **is_palindrome(const std::string& s)**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **find_duplicates_hashing(const std::string& s)**
  - Time Complexity: O(n)
  - Space Complexity: O(k) where k is the number of unique characters

- **find_duplicates_bitwise(const std::string& s)**
  - Time Complexity: O(n)
  - Space Complexity: O(1)

- **are_anagrams_hash(const std::string& s1, const std::string& s2)**
  - Time Complexity: O(n)
  - Space Complexity: O(k) where k is the number of unique characters

- **are_anagrams_bitwise(const std::string& s1, const std::string& s2)**
  - Time Complexity: O(n)
  - Space Complexity: O(1)