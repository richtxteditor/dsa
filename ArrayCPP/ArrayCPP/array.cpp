//
//  array.cpp
//  
//
//  Created by richie on 9/7/25.
//

#include "array.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <utility>
#include <unordered_map>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::min;
using std::max;
using std::numeric_limits;
using std::to_string;
using std::overflow_error;
using std::out_of_range;
using std::logic_error;
using std::unordered_map;
using std::pair;


// --- Private Helper Implementations ---
void Array::swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Array::resize() {
    // If size is 0, grow to a default initial capacity. Otherwise, double it.
    size_t newSize = (size == 0) ? 10 : size * 2;
#ifdef DEBUG_MODE
    cout << "[Debug: Resizing from " << size << " to " << newSize << "]" << endl;
#endif
    int* newA = new int [newSize];
    
    for (size_t i = 0; i < length; ++i) {
        newA[i] = A[i];
    }
    
    delete[] A;
    
    A = newA;
    size = newSize;
}

// --- Constructor & Rule of Five Implementations ---

// 1. Constructor
Array::Array(size_t sz) : size(sz > 0 ? sz : 10), length(0) {
    if (size == 0) {
        A = nullptr;
    } else {
        A = new int[size];
    }
#ifdef DEBUG_MODE
    cout << "[Debug: Constructor called!]" << endl;
#endif
}

Array::~Array() {
    delete[] A;
}

// 2. Copy Constructor
// Creates a true, independent copy (deep copy) of an Array object.
// Prevents multiple Array objects from sharing the same underlying memory ('A'),
// which would lead to errors like double-free when they are destroyed.
Array::Array(const Array& other) : size(other.size), length(other.length) {
#ifdef DEBUG_MODE
    cout << "[Debug: Copy Constructor Called]" << endl;
#endif
    if (size == 0) { A = nullptr; return; } // handle case where other failed construction
    A = new int[size]; // Let std::bad_alloc propagate on failure.
    for (size_t i = 0; i < length; ++i) A[i] = other.A[i]; // copy actual data element by element.
}

// 3. Copy Assignment Operator
// Allows one existing Array object to safely take on the value of another existing Array object
// (e.g., 'arr1 = arr2;'). Performs a deep copy, cleans up the target object's old resources, and
// handles self-assignment
Array& Array::operator=(const Array& other) {
#ifdef DEBUG_MODE
    cout << "[Debug: Copy Assignment Called]" << endl;
#endif
    if (this == &other) return *this; // check for self-assignment to avoid errors
    // allocate new mem first before deleting old mem for exception safety
    int* newA = new int[other.size]; // throws std::bad_alloc on failure
    // copy data to new memory
    for (size_t i = 0; i < other.length; ++i) newA[i] = other.A[i];
    delete[] A;
    A = newA; // update object's members to point to new resources
    size = other.size;
    length = other.length;
    return *this; // return reference to allow chaining (a = b = c)
}

// 4. Move Constructor (C++11)
// Transfers ownership of resources (like the pointer 'A') from temporary or
// expiring objects (rvalues) to a newly created object.
// Avoids the cost of deep copying when the soruce object won't be needed anymore.
// Must leave the srouce object in a valid (destructible) state.
// 'noexcept' allows optimizations.
Array::Array(Array&& other) noexcept: A(other.A), size(other.size), length(other.length) { // "Steal" resources using initializer list.
    cout << "[Debug: Move Constructor Called]" << endl;
    // reset the source object so its destructor won't free the moved memory.
    other.A = nullptr; other.size = 0; other.length = 0;
}

// 5. Move Assignment Operator (C++11)
// Transfers ownership of resources from a temporary or expiring object (rvalue) to an existing
// object (e.g., 'arr1 = CreateTempArray();').
// Avoids costly deep copies, releases the target object's old resources, and leaves
// the source object valid.
Array& Array::operator=(Array&& other) noexcept {
    cout << "[Debug: Move Assignment Called]" << endl;
    if (this == &other) return *this; // although less common for move, good practice to check for self assignment
    delete[] A; // release own resource currently held by *this* obj
    // pilfer other's resource
    A = other.A; size = other.size; length = other.length;
    // reset source object
    other.A = nullptr; other.size = 0; other.length = 0;
    return *this;
}

// --- Method Implementations with exception handling---
void Array::Display() const {
    if (length == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    cout << "Elements (" << length << "/" << size << "): ";
    for (size_t i = 0; i < length; i++)
        cout << A[i] << " ";
    cout << endl;
}

void Array::Append(int x) {
    if (length >= size){
        resize();
    }
    A[length++] = x;
}

void Array::Insert(size_t index, int x) {
    if (length >= size) {
        resize();
    }
    if(index > length) {
        throw std::out_of_range("Index (" + to_string(index) + ") out of bounds for Insert. Length is " + to_string(length) + ".");
    }
    for(size_t i = length; i > index; i--) A[i] = A[i-1];
        A[index] = x;
        length++;
}

int Array::Delete(size_t index) {
    if (length == 0) {
        throw std::logic_error("Cannot delete from empty array.");
    }
    if(index >= length) {
        throw std::out_of_range("Index (" + to_string(index) + ") out of bounds for Delete. Length is " + to_string(length) + ".");
    }
    int x = A[index];
    for(size_t i = index; i < length - 1; i++) A[i] = A[i+1];
    length--;
    return x;
}

std::optional<int> Array::Get(size_t index) const {
    if (index < length) {
        return A[index];
    }
    return std::nullopt;
}

void Array::Set(size_t index, int x) {
    if (index >= length) {
        throw std::out_of_range("Index (" + to_string(index) + ") out of bounds for Set. Length is " + to_string(length) + ".");
    }
    A[index] = x;
}

// With move-to-front optimization, modifies array
std::optional<size_t> Array::LinearSearch(int key) {
    for(size_t i = 0; i < length; i++) {
        if(key == A[i]) {
            if (i > 0) {
                swap(&A[i], &A[i - 1]);
                return i - 1; // return new index
            }
            return i; // return current index
        }
    }
    return std::nullopt; // not found
}

// Requires sorted array
std::optional<size_t> Array::BinarySearchLoop(int key) const {
    size_t l = 0;
    size_t h = length; // use one past the end
    
    while (l < h) {
        size_t mid = l + (h - l) / 2;
        if (key == A[mid]) return mid;
        else if (key < A[mid]) h = mid;
        else l = mid + 1;
    }
    return std::nullopt; // not found
}

int Array::Max() const {
    if (length == 0) {
        throw std::logic_error("Cannot find maximum of empty array.");
    }
    int max_val = A[0];
    for(size_t i = 1;i < length; i++) {
        if (A[i] > max_val) max_val = A[i];
    }
    return max_val;
}

int Array::Min() const {
    if (length == 0) {
        throw std::logic_error("Cannot find minimum of empty array.");
    }
    int min_val = A[0];
    for(size_t i = 1; i < length; i++) {
        if(A[i] < min_val) min_val = A[i];
    }
    return min_val;
}

long long Array::Sum() const {
    long long s = 0;
    for(size_t i = 0; i < length; i++) s += A[i];
    return s;
}

double Array::Avg() const {
    if (length == 0) {
        throw std::logic_error("Cannot calculate average of empty array.");
    }
    return static_cast<double>(Sum()) / length;
}

bool Array::isSorted() const {
    for(size_t i = 0; i < length - 1; i++) {
        if(A[i] > A[i + 1]) return false; // Not sorted
    }
    return true;
}

// Uses auxilliary array
void Array::Reverse() {
    if (length == 0) return;
    int *B = new int[length];
    for (size_t i = 0; i < length; ++i) { // copy reverse of A to B
        B[i] = A[length - 1 - i];
    }
    for (size_t i = 0; i < length; i++) { // Copy back to A
        A[i] = B[i];
    }
    delete[] B; // free allocated memory
}

// Reverses in place using swap
void Array::ReverseInPlace() {
    if (length < 2) return;
    for (size_t i = 0, j = length - 1; i < j; i++, j--) {
        swap(&A[i], &A[j]);
    }
}

// Assumes array should be kept sorted
void Array::InsertSort(int x) {
    if (length >= size) {
        resize();
    }
    size_t i = length; // start checking from potential new end
    while (i > 0 && A[i - 1] > x) {
        A[i] = A[i - 1];
        i--;
    }
    A[i] = x;
    length++;
}

// Rearranges negative numbers before positive numbers
void Array::Rearrange() {
    if (length < 2) return;
    size_t i = 0, j = length - 1;
    
    while (i < j) {
        // find first non-negative from left
        while(i < j && A[i] < 0) i++;
        // find first negative from right
        while(j > i && A[j] >= 0) j--;
        
        if (i < j) { swap(&A[i], &A[j]); }
    }
}

// --- Set Operations  (return by value) ---
// Assumes this and arr2 are sorted.
Array Array::Merge(const Array& arr2) const {
    Array arr3(length + arr2.length);
    size_t i = 0, j= 0, k = 0;

    while(i < length && j < arr2.length) {
        if(A[i] <= arr2.A[j]) { // take from A if equal or smaller
            arr3.A[k++] = A[i++];
        } else {
            arr3.A[k++] = arr2.A[j++];
        }
    }
    while (i < length) arr3.A[k++] = A[i++];
    while (j < arr2.length) arr3.A[k++] = arr2.A[j++];
    
    arr3.length = k;
    return arr3; // Rely on RVO / Move semantics
}

// Assumes this and arr2 are sorted
Array Array::Union(const Array& arr2) const {
    Array arr3(length + arr2.length);
    size_t i = 0, j = 0, k = 0;
    
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j])
            arr3.A[k++] = A[i++];
        else if (arr2.A[j] < A[i])
            arr3.A[k++] = arr2.A[j++];
        else { // Elements are equal, copy one and advance both
            arr3.A[k++] = A[i++];
            j++; // skip duplicate
        }
    }
    // copy remaining elements
    for(; i < length; i++)
        arr3.A[k++] = A[i];
    for(; j < arr2.length; j++)
        arr3.A[k++] = arr2.A[j];
    
    arr3.length = k;
    return arr3;
}

// Assumes this and arr2 are sorted.
Array Array::Intersection(const Array& arr2) const {
    // max size allocation is min length
    Array arr3(min(length, arr2.length));
    size_t i = 0, j = 0, k = 0;
    
    while(i < length && j < arr2.length) {
        if(A[i] < arr2.A[j]) i++;
        else if(arr2.A[j] < A[i]) j++;
        else { // Equal
            arr3.A[k++] = A[i++];
            j++;
        }
    }
    arr3.length = k;
    return arr3;
}

Array Array::Difference(const Array& arr2) const {
    Array arr3(length + arr2.length);
    size_t i = 0, j = 0, k = 0;

    while(i < length && j < arr2.length) {
        if(A[i] < arr2.A[j]) {
            arr3.A[k++] = A[i++]; // In A, not B yet
        } else if (arr2.A[j] < A[i]) {
            j++; // In B, not A, ignore
        } else { // equal, skip both
            i++;
            j++;
        }
    }
    while (i < length) { // Copy remaining A
        arr3.A[k++] = A[i];
    }
    
    arr3.length=k;
    return arr3; // Caller must delete this later
}

// --- Missing Element Functions ---

// Requires SORTED Array
std::optional<int> Array::FindSingleMissingElementSorted() const {
    if (length == 0) return std::nullopt; // Cannot find missing in empty
    int expected_diff = A[0] - 0;
    for (size_t i = 0; i < length; i++) {
        if (A[i] - static_cast<int>(i) != expected_diff) {
            // The missing element is the expected value at this index
            return static_cast<int>(i) + expected_diff;
        }
    }
    return std::nullopt;
}

// Works on UNOSRTED array using XOR
std::optional<int> Array::FindSingleMissingElementUnsortedOptimal() const {
    if (length == 0) return std::nullopt;
    int min_val;
    try {
        min_val = Min();
    } catch (const std::logic_error& e) {
        cerr << "Error finding minimum value for missing element calculation " << e.what() << endl;
        return std::nullopt;
    }
    
    int xor_sum_array = 0;
    int xor_sum_expected = 0;
    
    // 1. Calculate XOR sum of elements in array O(n)
    for (size_t i = 0; i < length; i++) {
        xor_sum_array ^= A[i];
    }
    
    // 2. XOR sum of expected sequence (min_val to min_val + length)
    long long max_expected_11 = static_cast<long long>(min_val) + length;
    if (max_expected_11 > numeric_limits<int>::max() || max_expected_11 < numeric_limits<int>::min()) {
        cerr << "Warning: Expected range for XOR calculations might exceed integer limits." << endl;
    }
    int max_expected = static_cast<int>(max_expected_11);
    
    for (int current_expected = min_val; current_expected <= max_expected; ++current_expected) {
        xor_sum_expected ^= current_expected;
        if (current_expected == numeric_limits<int>::max() && current_expected < max_expected) break;
    }
    
    int missing_element = xor_sum_array ^ xor_sum_expected;
    // Basic validation removed for optional return - caller decides if value is valid
    return missing_element;
}

void Array::FindMultipleMissingElementsSorted() const {
    if (length == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    int expected_diff = A[0] - 0;
    bool found_missing = false;
    cout << "Missing elements (Sorted Method): ";
    for (int i = 0; i < length; i++)
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

// works on UNOSRTED array using hashing (simple boolean array)
void Array::FindMultipleMissingElementsHash() const {
    if (length == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    int min_val = Min();
    int max_val = Max();
    
    if (min_val == -1 || max_val == -1) { // Check if Min/Max failed
        cerr << "Error finding min/max value. Cannot proceed." << endl;
        return;
    }
    if (min_val == max_val && length > 0) {
        cout << "Array contains only one distinct value or is empty. No gaps possible within the range." << endl;
        return;
    }
    
    // create a boolean hash set for the range [min_val, max_val]
    int range_size = max_val - min_val + 1;
    if (range_size <= 0) {
        cerr << "Error: Invalid range calculated (max <= min)." << endl;
        return;
    }
    // use vector for dynamic allocation and RAII
    vector<bool> hash_set(range_size, false);
    
    // mark elements present in the array
    for (int i = 0; i < length; i++)
    {
        // check if element is within the calculated range before hashing
        if (A[i] >= min_val && A[i] <= max_val) {
            hash_set[A[i] - min_val] = true; // Index = Value - MinValue
        }
    }
    
    // Iterate through the hash set range and print unmarked elements
    bool found_missing = false;
    cout << "Missing elements (Hash method, range[" << min_val << ", " << max_val << "]}: ";
    for (int i = 0; i < range_size; i++)
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

void Array::FindDuplicatesSorted() const {
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

// The best general-purpose hashing method.
// Time: O(n), Space: O(k) where k is the number of unique elements.
void Array::FindDuplicatesHashing() const {
    if (length < 2) {
        cout << "Array has too few elements to contain duplicates." << endl;
        return;
    }
    
    // 1. Create a true hash map to store frequencies.
    // The key is the number from the array, the value is its count.
    unordered_map<int, int> freq_map;
    
    // 2. Populate the frequency map.
    // This loop takes O(n) time.
    for (size_t i = 0; i < length; ++i) {
        freq_map[A[i]]++;
    }
    
    // 3. Iterate through the map to find and print dupes.
    cout << "--- Duplicates Found. (Unordered Map Method) ---" << endl;
    bool any_duplicates_found = false;
    // The loop runs k times for k is the number of unique elements.
    for (const auto& pair : freq_map) {
        if (pair.second > 1) { // pair.first is the first number, pair.second is its count
            cout << pair.first << " occurs" << pair.second << " times." << endl;
            any_duplicates_found = true;
        }
    }
    if (!any_duplicates_found) {
        cout << "No duplciates found." << endl;
    }
}

// Finds duplicates using O(n^2) brute-force in a NON-DESTRUCTIVE way.
// It creates a temporary copy to avoid modifying the original array.
std::vector<std::pair<int, int>> Array::FindDuplicatesUnsorted_BruteForce() {
    std::vector<std::pair<int, int>> duplicates;
    if (length < 2) {
        return duplicates;
    }
    
    // 1. Create a temporary, modifiable copy of the array data.
    int* tempA = new int[length];
    for (size_t i = 0; i < length; ++i) {
        tempA[i] = A[i];
    }
    
    // 2. Perform the destructive algorithm on the copy.
    for (size_t i = 0; i < length - 1; ++i) {
        // NOTE: We now use a legit value from the original array A to check
        // against our temporary array.
        if (tempA[i] != -1) {
            int count = 1;
            // Inner loop compares A[i] with all subsequent elements.
            for (size_t j = i + 1; j < length; j++){
                if (tempA[i] == tempA[j]) {
                    count++;
                    tempA[j] = -1; // mark the found duplicate to avoid re-counting.
                }
            }
            
            // if more than one incstance was found, add it to the vector.
            if (count > 1) {
                duplicates.push_back({A[i], count});
            }
        }
    }
    delete[] tempA;
    return duplicates;
}
