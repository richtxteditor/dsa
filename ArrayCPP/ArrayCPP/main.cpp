//
//  main.cpp
//  ArrayCPP
//
//  Created by richie on 12/19/24.
//

#include <iostream>
#include <cstdlib> // for exit() if needed, replaces stdlib.h
#include <cctype> // for tolower()
#include <vector> // Using for boolean hash set in FindMultipleMissingElementsHash
#include <limits> // for numeric_limits if needed
#include <stdexcept> // for exceptions (otional, but good practice)
#include <utility> // for std::move
#include <algorithm> // for std::min, std::max
#include <string> // for to_string in main
#include <new> // for std::nothrow
#include <thread>
#include <chrono>
#include <optional> // for optional return values

using namespace std;

class Array
{
private:
    int *A;         // pointer to heap array
    size_t size;       // allocated size
    size_t length;     // num of elements currently in array
    
    // helper for swapping elements
    void swap(int *x, int *y) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }
    
public:
    // --- Constructor ---
    
    // can throw std::bad_alloc if 'new' afils
    Array(size_t sz = 10) : size(sz > 0 ? sz : 10), length(0) {
        if (size == 0) {
            A = nullptr;
        } else {
            A = new int[size];
        }
        cout << "[Debug: Construcor Called]" << endl;
    }
    
    // --- Rule of Five (memory management) ---
    ~Array() { delete[] A; } // 1. Destructor frees heap (dynamically allocated) mem pointed to by A.
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
    std::optional<size_t> LinearSearch(int key);      // O(n) - Unosrted/Sorted
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
    
};

// --- Rule of Five Implementations ---

// 2. Copy Constructor
// Creates a true, independent copy (deep copy) of an Array object.
// Prevents multiple Array objects from sharing the same underlying memory ('A'),
// which would lead to errors like double-free when they are destroyed.
Array::Array(const Array& other) : size(other.size), length(other.length) {
    cout << "[Debug: Copy Constructor Called]" << endl;
    if (size == 0) { A = nullptr; return; } // handle case where other failed construction
    A = new int[size]; // Let std::bad_alloc propagate on failure.
    for (size_t i = 0; i < length; ++i) A[i] = other.A[i]; // copy actual data element by element.
}

// 3. Copy Assignment Operator
// Allows one existing Array object to safely take on the value of another existing Array object
// (e.g., 'arr1 = arr2;'). Performs a deep copy, cleans up the target object's old resources, and
// handles self-assignment
Array& Array::operator=(const Array& other) {
    cout << "[Debug: Copy Assignment Called]" << endl;
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
        throw std::overflow_error("Array is full, cannot append.");
    }
    A[length++] = x;
}

void Array::Insert(size_t index, int x) {
    if (length >= size) {
        cerr << "Error: Array is full. Cannot insert." << endl;
        return;
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
        throw std::overflow_error("Array is full, cannot insert.");
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
    vector<bool> hash_set(range_size,
                          false);
    
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

// --- Helper Function to Create and Populate an Array ---
// used for set ops requiring a 2nd array
Array create_and_fill_array(size_t expected_size, bool must_be_sorted) {
    Array arr(expected_size); // create local array obj
    int num_elements;
    cout << "Enter number of elements for the 2nd array (max " << expected_size << "): ";
    // simple input validation loop
    while (!(cin >> num_elements) || num_elements < 0 || static_cast<size_t>(num_elements) > expected_size) {
        cout << "Invalid input. Please enter a number between 0 and " << expected_size << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "Enter " << num_elements <<  " elements";
    if (must_be_sorted) cout << " (in sorted order)";
    cout << ":" << endl;
    
    int val;
    for (int i = 0; i < num_elements; ++i) {
        // use the validation helper
        auto get_int = [](const string& prompt) {
            int v;
            cout << prompt;
            while (!(cin >> v)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            return v;
        };
        val = get_int("Element " + to_string(i+1) + ": ");
        
        if (must_be_sorted) {
            if (i > 0 && val < arr.Get(i-1)) { // use Get safely
                cout << "Warning: Elements entered out of border for sorted array requirement!" << endl;
            }
            arr.InsertSort(val);
        } else {
            arr.Append(val);
        }
    }

    if (must_be_sorted && !arr.isSorted()) {
        cout << "Warning: The second array provided is NOT sorted, set ops might yield incorrect results." << endl;
    }
    // Let RVO/Move semantics handle the return efficiently
    return arr;
}


// --- Main Function (Menu Driven) ---
int main() {
    Array *arr1 = nullptr; // Initialize to nullptr
    int ch = -1;
    size_t sz; // use size_t for size input
    
    cout << "Enter Size of Array: ";
    // basic input validation for size
    while (!(cin >> sz) || sz == 0) {
        cout << "Invalid input. Please enter a positive integer size.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    arr1 = new Array(sz); // Create the main array
    
    // check if allocatin failed in constructor
    if (arr1->GetSize() == 0) {
        cerr << "Exiting due to memory allocation failure." << endl;
        return 1;
    }
    
    bool intend_to_be_sorted = false;
    char sorted_choice;
    cout << "Do you intend to keep this array sorted? (y/n): ";
    cin >> sorted_choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume newline
    if(tolower(sorted_choice) == 'y') {
        intend_to_be_sorted = true;
        cout << "--> Array will be treated as sorted. Use appropriate sorting methods." << endl;
    } else {
        intend_to_be_sorted = false;
        cout << "--> Array will be treated as potentially unsorted."<< endl;
    }
    
    // --- Optional initial fill ---
    char fill_choice;
    cout << "Fill array with initial values now? (y/n): ";
    cin >> fill_choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume newline
    if (tolower(fill_choice) == 'y') {
        int num_to_fill;
        cout << "Enter number of elements to add initially (max " << arr1->GetSize() << "): ";
        while (!(cin >> num_to_fill) || num_to_fill < 0 || static_cast<size_t>(num_to_fill) > arr1->GetSize()) {
            cout << "Invalid input. Please enter a number between 0 and " << arr1->GetSize() << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Enter " << num_to_fill << " elements:\n";
        int x_fill;
        for (int i = 0; i < num_to_fill; ++i) {
            cout << "Element " + to_string(i + 1) + ": ";
            while (!(cin >> x_fill)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume newline
            if (intend_to_be_sorted) {
                arr1->InsertSort(x_fill);
            } else {
                arr1->Append(x_fill);
            }
        }
        cout << "Array after initial fill:" << endl;
        arr1->Display();
    }
    // --- End initial fill ---
    
    
    do
    {
        cout << "\n========= Menu (" << (intend_to_be_sorted ? "Sorted Mode" : "Unsorted Mode") << ") ============\n";
        // Add/Delete
        cout << "1. Append Element\n";
        cout << "2. Insert Element at Index\n";
        cout << "3. Insert Element (Keep Sorted - Use in Sorted Mode)\n";
        cout << "4. Delete Element at Index\n";
        
        // Search
        cout << "5. Search (Linear)\n";
        cout << "6. Search (Binary - Requires Sorted)\n";
        cout << "7. Get Element at Index\n";
        cout << "8. Set Element at Index \n";
        cout << "9. Display Array\n";
        cout << "10. Get Sum\n";
        cout << "11. Get Average\n";
        cout << "12. Get Maximum\n";
        cout << "13. Get Minimum\n";
        cout << "14. Check if Sorted\n";
        
        // Modify
        cout << "15. Reverse (Creates Temp Array)\n";
        cout << "16. Reverse (In Place)\n";
        cout << "17. Rearrange Negatives/Positives\n";
        
        // Set Operations (Requires Sorted)
        cout << "18. Merge with Second Array\n";
        cout << "19. Union with Second Array\n";
        cout << "20. Intersection with Second Array\n";
        cout << "21. Difference (Arr1 - Arr2)\n";
        cout << "22. Find Single Missing Element (Smart)\n";
        cout << "23. Find Multiple Missing Elements (Sorted Method)\n";
        cout << "24. Find Multiple Missing Elements (Unosrted Hash Method)\n";
        
        // Exit
        cout << "0. Exit\n";
        cout << "=============================================================\n";
        
        // Input
        cout << "Enter your choice: ";
        cin >> ch;
        
        // Input validation for ch
        while (!cin) {
            cout << "Invalid input. Please enter a number for the menu choice: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Prompt and read AGAIN inside loop
            cout << "=============================================================\n";
            cout << "Enter your choice: ";
            cin >> ch;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume new line after chioce
        
        // Input validation helpers (Lambdas)
        auto get_integer_input = [](const string& prompt) -> int {
            int val;
            cout << prompt;
            while (!(cin >> val)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        };
        
        auto get_index_input = [&](const string& prompt) -> size_t {
            int val; // read as int for easier validation range check
            size_t idx;
            cout << prompt;
            while (!(cin >> val) || val < 0) { // check for negative separately
                cout << "Invalid input. Please ener a non-negative integer index: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            idx = static_cast<size_t>(val);
            // warning if potentially out of bounds for current length, not size
            if (idx >= arr1->GetLength() && !(ch == 2 && idx == arr1->GetLength())) { // allow insert at index == length
                if (arr1->GetLength() > 0) cout << "Warning: index " << idx << " is >= current length " << arr1->GetLength() << "." << endl;
                else cout << "Warning: Index " << idx << "specified for empty array." << endl;
            }
            return idx;
        };
        
        int x = 0; size_t index = 0;
        cout << "------------------------------------------------\n";
        switch (ch) {
            case 1: // Append
                x = get_integer_input("Enter element to append: ");
                arr1->Append(x);
                arr1->Display();
                break;
            case 2: // Insert at Index
                x = get_integer_input("Enter element to insert: ");
                index = get_index_input("Enter index ");
                arr1->Insert(index, x);
                arr1->Display();
                break;
            case 3: // Insert Keeping Sort
                x = get_integer_input("Enter element to insert (keeping sorted): ");
                arr1->InsertSort(x);
                arr1->Display();
                break;
            case 4: // Delete
                index = get_index_input("Enter index to delete: ");
                x = arr1->Delete(index);
                // Check if Delete returned error value
                cout << "Deleted: " << x << "\n";
                arr1->Display();
                break;
            case 5: { // Linear Search
                x = get_integer_input("Enter element to search (Linear): ");
                auto result = arr1->LinearSearch(x);
                if (result)
                    cout << "Element found at index: " << index << "\n";
                else
                    cout << "Element not found.\n";
                break;
            }
            case 6: { // Binary search
                if (!arr1->isSorted()) {
                    cout << "ERROR: Array must be sorted for Binary Search.\n";
                } else {
                    x = get_integer_input("Enter element to search (Binary): ");
                    auto result= arr1->BinarySearchLoop(x);
                    if (result)
                        cout << "Element found at index: " << index << "\n";
                    else
                        cout << "Element not found.\n";
                }
                break;
            }
                // --- Get/Set ---
            case 7: { // Get
                index = get_index_input("Enter index to get element from: ");
                auto result = arr1->Get(index);
                if (result) // check for error value
                    cout << "Element at index " << index << " is: " << x << "\n";
                break;
            }
            case 8: { // Set
                index = get_index_input("Enter index to set element at: ");
                x = get_integer_input("Enter new value: ");
                arr1->Set(index, x); // Set handles its own error message
                arr1->Display();
                break;
            }
                
            // --- Info ---
            case 9: arr1->Display(); break;
            case 10: cout << "Sum of elements: " << arr1->Sum() << "\n"; break;
            case 11: cout << "Average: " << arr1->Avg() << "\n"; break;
            case 12: cout << "Maximum elements: " << arr1->Max() << "\n"; break;
            case 13: cout << "Minimum elements: " << arr1->Min() << "\n"; break;
            case 14: cout << "Array is " << (arr1->isSorted() ? "SORTED" : "NOT SORTED") << ".\n"; break;
                // --- Modify ---
            case 15: cout << "Reversing array (using temp array)..." << endl; arr1->Reverse(); arr1->Display(); break;
            case 16: cout << "Reversing array in place..." << endl; arr1->ReverseInPlace(); arr1->Display(); break;
            case 17: cout << "Rearranging negatives before positives..." << endl; arr1->Rearrange(); arr1->Display(); break;
                // --- Set Operations ---
            case 18: case 19: case 20: case 21:
            {
                cout << "--- Set Operation requires a second SORTED array ---" << endl;
                if (!arr1->isSorted()) {
                    cout << "Warning: The main array (Arr1) is not sorted. Results may be incorrect." << endl;
                }
                
                // Create and fill the second array (return by val)
                Array arr2_local = create_and_fill_array(100, true); // size 100 for temp array
                cout << "Arr1: "; arr1->Display();
                cout << "Arr2: "; arr2_local.Display();
                
                // result array created locally by return-by-value
                Array result_array;
                if (ch == 18) result_array = arr1->Merge(arr2_local);
                else if (ch == 19) result_array = arr1->Union(arr2_local);
                else if (ch == 20) result_array = arr1->Intersection(arr2_local);
                else if (ch == 21) result_array = arr1->Difference(arr2_local);
                
                cout << "Result: ";
                result_array.Display();
                // result_array and arr2_local go out of scope here, destructors called automatically
            }
                break;
                
                // --- Missing Elements ---
            case 22: // Find Single Missing (Smart)
                if (arr1->GetLength() == 0) {
                    cout << "Array is empty." << endl; break;
                }
                if (intend_to_be_sorted) {
                    if (!arr1->isSorted()) { cout << "ERROR: Array not sorted.\n"; }
                    else {
                        auto result = arr1->FindSingleMissingElementSorted();
                        if (result) cout << "Missing(Sorted): " << *result << "\n";
                        else cout << "None found (Sorted).\n";
                    }
                } else {
                    auto result = arr1->FindSingleMissingElementUnsortedOptimal();
                    if (result) cout << "Missing (Unsorted): " << *result << "\n";
                    else cout << "Coud not determine (e.g. Min failed).\n";
                }
                break;
            case 23: // Find Multiple Missing (Sorted)
                if (!arr1->isSorted()) {
                    cout << "ERROR: Array must be sorted for this method.\n";
                } else {
                    arr1->FindMultipleMissingElementsSorted();
                }
                break;
            case 24: // Find Multiple Missing (Unsorted Hash)
                arr1->FindMultipleMissingElementsHash();
                break;
                
                
            case 0: cout << "Exiting program." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl; break;
        }
        cout << "------------------------------------------------\n";
        
        // Timed Pause logic here
        if (ch != 0) {
            cout << "\nJust a moment...\n";
        }
        this_thread::sleep_for(chrono::seconds(3));
    } while (ch != 0);
    
    // --- Cleanup ---
    delete arr1; // Delete the main array allocated in main
    
    return 0;
}
