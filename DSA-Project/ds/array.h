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
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>

// --- Use specific using declarations inside the header ---
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::pair;
using std::unordered_map;
using std::unordered_set;
using std::min;
using std::max;

// The template declaration applies to the whole class
template<typename T>
class Array {
private:
    T* A;
    size_t size;
    size_t length;

    void swap(T* x, T* y);
    void resize();

public:
    // --- Iterator Support ---
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    // --- Constructor & Rule of Five ---
    Array(size_t sz = 10);
    ~Array();
    Array(const Array<T>& other);
    Array<T>& operator=(const Array<T>& other);
    Array(Array<T>&& other) noexcept;
    Array<T>& operator=(Array<T>&& other) noexcept;

    // --- Basic Operations ---
    void Display() const;
    void Append(const T& x);
    void Insert(size_t index, const T& x);
    T Delete(size_t index);
    std::optional<T> Get(size_t index) const;
    void Set(size_t index, const T& x);

    // --- Search Operations ---
    std::optional<size_t> LinearSearch(const T& key);
    std::optional<size_t> BinarySearchLoop(const T& key) const;

    // --- Info / Aggregate Operations ---
    size_t GetLength() const { return length; }
    size_t GetSize() const { return size; }
    T Max() const;
    T Min() const;
    T Sum() const;
    double Avg() const;
    bool isSorted() const;

    // --- Modify Operations ---
    void Reverse();
    void ReverseInPlace();
    void InsertSort(const T& x);
    void Rearrange();

    // --- Set Operations (Require Sorted Arrays) ---
    Array<T> Merge(const Array<T>& arr2) const;
    Array<T> Union(const Array<T>& arr2) const;
    Array<T> Intersection(const Array<T>& arr2) const;
    Array<T> Difference(const Array<T>& arr2) const;

    // --- Numeric-Specific Algorithms ---
    std::optional<T> FindSingleMissingElementSorted() const;
    void FindMultipleMissingElementsSorted() const;
    std::optional<T> FindSingleMissingElementUnsortedOptimal() const;
    void FindMultipleMissingElementsHash() const;
    void FindDuplicatesSorted() const;
    void FindDuplicatesHashing() const;
    std::vector<pair<T, int>> FindDuplicatesUnsorted_BruteForce();
    std::optional<pair<T, T>> PairWithSum_Sorted(const T& k) const;
    std::optional<pair<T, T>> PairWithSum_Hashing(const T& k) const;
    std::optional<pair<T, T>> FindMinMax() const;
};

// =================================================================================
// =================== IMPLEMENTATION MOVED FROM .CPP FILE =========================
// =================================================================================

// --- Private Helper Implementations ---

template<typename T>
void Array<T>::swap(T* x, T* y) {
    T temp = *x;
    *x = *y;
    *y = temp;
}

template<typename T>
void Array<T>::resize() {
    size_t newSize = (size == 0) ? 10 : size * 2;
#ifdef DEBUG_MODE
    cout << "[Debug: Resizing from " << size << " to " << newSize << "]" << endl;
#endif
    T* newA = new T[newSize];
    for (size_t i = 0; i < length; ++i) {
        newA[i] = A[i];
    }
    delete[] A;
    A = newA;
    size = newSize;
}

// --- Iterator Implementations ---

template<typename T>
T* Array<T>::begin() {
    return A;
}

template<typename T>
T* Array<T>::end() {
    return A + length;
}

template<typename T>
const T* Array<T>::begin() const {
    return A;
}

template<typename T>
const T* Array<T>::end() const {
    return A + length;
}

// --- Constructor & Rule of Five Implementations ---

template<typename T>
Array<T>::Array(size_t sz) : size(sz > 0 ? sz : 10), length(0) {
    A = (size == 0) ? nullptr : new T[size];
#ifdef DEBUG_MODE
    cout << "[Debug: Constructor called!]" << endl;
#endif
}

template<typename T>
Array<T>::~Array() {
    delete[] A;
}

template<typename T>
Array<T>::Array(const Array<T>& other) : size(other.size), length(other.length) {
#ifdef DEBUG_MODE
    cout << "[Debug: Copy Constructor Called]" << endl;
#endif
    A = (size == 0) ? nullptr : new T[size];
    for (size_t i = 0; i < length; ++i) A[i] = other.A[i];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
#ifdef DEBUG_MODE
    cout << "[Debug: Copy Assignment Called]" << endl;
#endif
    if (this == &other) return *this;
    T* newA = new T[other.size];
    for (size_t i = 0; i < other.length; ++i) newA[i] = other.A[i];
    delete[] A;
    A = newA;
    size = other.size;
    length = other.length;
    return *this;
}

template<typename T>
Array<T>::Array(Array<T>&& other) noexcept : A(other.A), size(other.size), length(other.length) {
#ifdef DEBUG_MODE
    cout << "[Debug: Move Constructor Called]" << endl;
#endif
    other.A = nullptr;
    other.size = 0;
    other.length = 0;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept {
#ifdef DEBUG_MODE
    cout << "[Debug: Move Assignment Called]" << endl;
#endif
    if (this == &other) return *this;
    delete[] A;
    A = other.A;
    size = other.size;
    length = other.length;
    other.A = nullptr;
    other.size = 0;
    other.length = 0;
    return *this;
}

// --- Method Implementations ---

template<typename T>
void Array<T>::Display() const {
    if (length == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    cout << "Elements (" << length << "/" << size << "): ";
    for (size_t i = 0; i < length; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

template<typename T>
void Array<T>::Append(const T& x) {
    if (length >= size) {
        resize();
    }
    A[length++] = x;
}

template<typename T>
void Array<T>::Insert(size_t index, const T& x) {
    if (length >= size) {
        resize();
    }
    if (index > length) {
        throw std::out_of_range("Index out of bounds for Insert.");
    }
    for (size_t i = length; i > index; i--) {
        A[i] = A[i - 1];
    }
    A[index] = x;
    length++;
}

template<typename T>
T Array<T>::Delete(size_t index) {
    if (length == 0 || index >= length) {
        throw std::out_of_range("Index out of bounds for Delete.");
    }
    T x = A[index];
    for (size_t i = index; i < length - 1; i++) {
        A[i] = A[i + 1];
    }
    length--;
    return x;
}

template<typename T>
std::optional<T> Array<T>::Get(size_t index) const {
    if (index < length) {
        return A[index];
    }
    return std::nullopt;
}

template<typename T>
void Array<T>::Set(size_t index, const T& x) {
    if (index >= length) {
        throw std::out_of_range("Index out of bounds for Set.");
    }
    A[index] = x;
}

template<typename T>
std::optional<size_t> Array<T>::LinearSearch(const T& key) {
    for (size_t i = 0; i < length; i++) {
        if (key == A[i]) {
            if (i > 0) {
                swap(&A[i], &A[i - 1]);
                return i - 1;
            }
            return i;
        }
    }
    return std::nullopt;
}

template<typename T>
std::optional<size_t> Array<T>::BinarySearchLoop(const T& key) const {
    size_t l = 0, h = length;
    while (l < h) {
        size_t mid = l + (h - l) / 2;
        if (key == A[mid]) return mid;
        else if (key < A[mid]) h = mid;
        else l = mid + 1;
    }
    return std::nullopt;
}

template<typename T>
T Array<T>::Max() const {
    if (length == 0) throw std::logic_error("Cannot find max of empty array.");
    T max_val = A[0];
    for (size_t i = 1; i < length; i++) {
        if (A[i] > max_val) max_val = A[i];
    }
    return max_val;
}

template<typename T>
T Array<T>::Min() const {
    if (length == 0) throw std::logic_error("Cannot find min of empty array.");
    T min_val = A[0];
    for (size_t i = 1; i < length; i++) {
        if (A[i] < min_val) min_val = A[i];
    }
    return min_val;
}

template<typename T>
T Array<T>::Sum() const {
    if (length == 0) return T{}; // Return default-constructed T (e.g., 0 for int)
    T s = A[0];
    for (size_t i = 1; i < length; i++) s += A[i];
    return s;
}

template<typename T>
double Array<T>::Avg() const {
    if (length == 0) return 0.0;
    return static_cast<double>(Sum()) / length;
}

template<typename T>
bool Array<T>::isSorted() const {
    for (size_t i = 0; i < length - 1; i++) {
        if (A[i] > A[i + 1]) return false;
    }
    return true;
}

template<typename T>
void Array<T>::Reverse() {
    if (length == 0) return;
    T* B = new T[length];
    for (size_t i = 0; i < length; ++i) {
        B[i] = A[length - 1 - i];
    }
    for (size_t i = 0; i < length; i++) {
        A[i] = B[i];
    }
    delete[] B;
}

template<typename T>
void Array<T>::ReverseInPlace() {
    if (length < 2) return;
    for (size_t i = 0, j = length - 1; i < j; i++, j--) {
        swap(&A[i], &A[j]);
    }
}

template<typename T>
void Array<T>::InsertSort(const T& x) {
    if (length >= size) resize();
    size_t i = length;
    while (i > 0 && A[i - 1] > x) {
        A[i] = A[i - 1];
        i--;
    }
    A[i] = x;
    length++;
}

template<typename T>
void Array<T>::Rearrange() {
    if (length < 2) return;
    size_t i = 0, j = length - 1;
    while (i < j) {
        while (i < j && A[i] < 0) i++;
        while (j > i && A[j] >= 0) j--;
        if (i < j) swap(&A[i], &A[j]);
    }
}

template<typename T>
Array<T> Array<T>::Merge(const Array<T>& arr2) const {
    Array<T> arr3(length + arr2.length);
    size_t i = 0, j = 0, k = 0;
    while (i < length && j < arr2.length) {
        arr3.A[k++] = (A[i] <= arr2.A[j]) ? A[i++] : arr2.A[j++];
    }
    while (i < length) arr3.A[k++] = A[i++];
    while (j < arr2.length) arr3.A[k++] = arr2.A[j++];
    arr3.length = k;
    return arr3;
}

template<typename T>
Array<T> Array<T>::Union(const Array<T>& arr2) const {
    Array<T> arr3(length + arr2.length);
    size_t i = 0, j = 0, k = 0;
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j]) arr3.A[k++] = A[i++];
        else if (arr2.A[j] < A[i]) arr3.A[k++] = arr2.A[j++];
        else {
            arr3.A[k++] = A[i++];
            j++;
        }
    }
    while (i < length) arr3.A[k++] = A[i++];
    while (j < arr2.length) arr3.A[k++] = arr2.A[j++];
    arr3.length = k;
    return arr3;
}

template<typename T>
Array<T> Array<T>::Intersection(const Array<T>& arr2) const {
    Array<T> arr3(min(length, arr2.length));
    size_t i = 0, j = 0, k = 0;
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j]) i++;
        else if (arr2.A[j] < A[i]) j++;
        else {
            arr3.A[k++] = A[i++];
            j++;
        }
    }
    arr3.length = k;
    return arr3;
}

template<typename T>
Array<T> Array<T>::Difference(const Array<T>& arr2) const {
    Array<T> arr3(length);
    size_t i = 0, j = 0, k = 0;
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j]) arr3.A[k++] = A[i++];
        else if (arr2.A[j] < A[i]) j++;
        else {
            i++;
            j++;
        }
    }
    while (i < length) arr3.A[k++] = A[i++];
    arr3.length = k;
    return arr3;
}

template<typename T>
void Array<T>::FindDuplicatesHashing() const {
    if (length < 2) return;
    unordered_map<T, int> freq_map;
    for (size_t i = 0; i < length; ++i) {
        freq_map[A[i]]++;
    }
    cout << "--- Duplicates Found (Hashing) ---" << endl;
    bool found = false;
    for (const auto& pair : freq_map) {
        if (pair.second > 1) {
            cout << "Value: " << pair.first << ", Occurrences: " << pair.second << endl;
            found = true;
        }
    }
    if (!found) cout << "No duplicates found." << endl;
}

template<typename T>
std::vector<pair<T, int>> Array<T>::FindDuplicatesUnsorted_BruteForce() {
    vector<pair<T, int>> duplicates;
    if (length < 2) return duplicates;

    T magic_val = T{}; // Use default-constructed value, e.g., 0 for int
    // This is still not robust for all types, but is a generic placeholder.
    
    T* tempA = new T[length];
    for (size_t i = 0; i < length; ++i) tempA[i] = A[i];
    
    for (size_t i = 0; i < length; ++i) {
        if (tempA[i] != magic_val) {
             int count = 1;
             for (size_t j = i + 1; j < length; j++) {
                 if (tempA[i] == tempA[j]) {
                     count++;
                     tempA[j] = magic_val;
                 }
             }
             if (count > 1) {
                 duplicates.push_back({A[i], count});
             }
        }
    }
    delete[] tempA;
    return duplicates;
}

template<typename T>
std::optional<pair<T, T>> Array<T>::PairWithSum_Sorted(const T& k) const {
    if (!isSorted()) {
        cerr << "Error: Array must be sorted for this method." << endl;
        return std::nullopt;
    }
    size_t low = 0, high = length - 1;
    while (low < high) {
        T current_sum = A[low] + A[high];
        if (current_sum == k) return std::make_pair(A[low], A[high]);
        else if (current_sum < k) low++;
        else high--;
    }
    return std::nullopt;
}

template<typename T>
std::optional<pair<T, T>> Array<T>::PairWithSum_Hashing(const T& k) const {
    unordered_set<T> seen_elements;
    for (size_t i = 0; i < length; ++i) {
        T complement = k - A[i];
        if (seen_elements.count(complement)) {
            return std::make_pair(complement, A[i]);
        }
        seen_elements.insert(A[i]);
    }
    return std::nullopt;
}

template<typename T>
std::optional<pair<T, T>> Array<T>::FindMinMax() const {
    if (length == 0) return std::nullopt;
    if (length == 1) return std::make_pair(A[0], A[0]);

    T min_val, max_val;
    size_t start_index;

    if (length % 2 == 0) {
        if (A[0] < A[1]) { min_val = A[0]; max_val = A[1]; }
        else { min_val = A[1]; max_val = A[0]; }
        start_index = 2;
    } else {
        min_val = A[0]; max_val = A[0];
        start_index = 1;
    }

    for (size_t i = start_index; i < length - 1; i += 2) {
        if (A[i] < A[i + 1]) {
            if (A[i] < min_val) min_val = A[i];
            if (A[i + 1] > max_val) max_val = A[i + 1];
        } else {
            if (A[i + 1] < min_val) min_val = A[i + 1];
            if (A[i] > max_val) max_val = A[i];
        }
    }
    return std::make_pair(min_val, max_val);
}

template<typename T>
void Array<T>::FindDuplicatesSorted() const {
    if (length < 2) {
        cout << "No duplicates found in this sorted array." << endl;
        return;
    }
    

        bool found = false;
        for (size_t i = 0; i < length - 1; ) {
            if (A[i] == A[i + 1]) {
                found = true;
                size_t count = 2; // We already have two identical elements: A[i] and A[i+1]
                size_t j = i + 2;
                
                while (j < length && A[j] == A[i]){
                    ++count;
                    j++;
                }
                cout << "Duplicate value: " << A[i] << "\nOccurrences: " << count << " times." << endl;
                i = j; // skip ahead to the next distinct element
            } else {
                ++i;
            }
        }
        if (!found) {
            cout << "No duplicates found in this sorted array." << endl;
        }
    }

// Requires SORTED Array
template<typename T>
std::optional<T> Array<T>::FindSingleMissingElementSorted() const {
    if (length == 0) return std::nullopt; // Cannot find missing in empty
    int expected_diff = A[0] - 0;
    for (size_t i = 0; i < length; i++) {
        if (A[i] - static_cast<T>(i) != expected_diff) {
            // The missing element is the expected value at this index
            return static_cast<T>(i) + expected_diff;
        }
    }
    return std::nullopt;
}

template<typename T>
void Array<T>::FindMultipleMissingElementsSorted() const {
    if (length == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    T expected_diff = A[0] - 0;
    bool found_missing = false;
    cout << "Missing elements (Sorted Method): ";
    for (T i = 0; i < length; i++)
    {
        if (A[i] - i != expected_diff)
        {
            // found a gap, pritn missing elements until difference matches again
            while (expected_diff < A[i] - i)
            {
                cout << (i + expected_diff) << " ";
                expected_diff++;
                found_missing = true;
            }
        }
    }
    if (!found_missing) {
        cout << "None found in sequence.";
    }
    cout << endl;
}

// Works on UNOSRTED array using XOR
template<typename T>
std::optional<T> Array<T>::FindSingleMissingElementUnsortedOptimal() const {
    if (length == 0) return std::nullopt;
    T min_val;
    try {
        min_val = Min();
    } catch (const std::logic_error& e) {
        cerr << "Error finding minimum value for missing element calculation " << e.what() << endl;
        return std::nullopt;
    }
    
    T xor_sum_array = 0;
    T xor_sum_expected = 0;
    
    // 1. Calculate XOR sum of elements in array O(n)
    for (size_t i = 0; i < length; i++) {
        xor_sum_array ^= A[i];
    }
    
    // 2. XOR sum of expected sequence (min_val to min_val + length)
    long long max_expected_11 = static_cast<long long>(min_val) + length;
    if (max_expected_11 > std::numeric_limits<T>::max() || max_expected_11 < std::numeric_limits<T>::min()) {
        cerr << "Warning: Expected range for XOR calculations might exceed integer limits." << endl;
    }
    T max_expected = static_cast<T>(max_expected_11);
    
    for (T current_expected = min_val; current_expected <= max_expected; ++current_expected) {
        xor_sum_expected ^= current_expected;
        if (current_expected == std::numeric_limits<T>::max() && current_expected < max_expected) break;
    }
    
    T missing_element = xor_sum_array ^ xor_sum_expected;
    // Basic validation removed for optional return - caller decides if value is valid
    return missing_element;
}

// works on UNOSRTED array using hashing (simple boolean array)
template<typename T>
void Array<T>::FindMultipleMissingElementsHash() const {
    if (length == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    T min_val = Min();
    T max_val = Max();
    
    if (min_val == -1 || max_val == -1) { // Check if Min/Max failed
        cerr << "Error finding min/max value. Cannot proceed." << endl;
        return;
    }
    if (min_val == max_val && length > 0) {
        cout << "Array contains only one distinct value or is empty. No gaps possible within the range." << endl;
        return;
    }
    
    // create a boolean hash set for the range [min_val, max_val]
    T range_size = max_val - min_val + 1;
    if (range_size <= 0) {
        cerr << "Error: Invalid range calculated (max <= min)." << endl;
        return;
    }
    // use vector for dynamic allocation and RAII
    vector<bool> hash_set(range_size, false);
    
    // mark elements present in the array
    for (T i = 0; i < length; i++)
    {
        // check if element is within the calculated range before hashing
        if (A[i] >= min_val && A[i] <= max_val) {
            hash_set[A[i] - min_val] = true; // Index = Value - MinValue
        }
    }
    
    // Iterate through the hash set range and print unmarked elements
    bool found_missing = false;
    cout << "Missing elements (Hash method, range[" << min_val << ", " << max_val << "]}: ";
    for (T i = 0; i < range_size; i++)
    {
        if (!hash_set[i])
        {
            cout << (i + min_val) << " "; // Missing number = Index + MinValue
            found_missing = true;
        }
    }
    if (!found_missing) {
        cout << "None found in range.";
    }
    cout << endl;
    // vector cleans itself up automatically (RAII)
}


#endif // ARRAY_H
