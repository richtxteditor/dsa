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
    // --- Constructors ---
    // default constructor
    Array(size_t sz = 10): size(sz > 0 ? sz : 10), length(0) {
        A = new (nothrow) int[size]; // use nothrow to avoid exception, check pointer
        if (!A) {
            cerr << "FATAL ERROR: Memory allocation failed in constructor!" << endl;
            // handle allocation faliure, maybe exit or set a failed state
            size = 0; // indicate failed state
            length = 0;
            // consider throwing std::bad_alloc here
        }
    }
    
    // --- Rule of Five (memory management) ---
    // 1. Destructor
    ~Array() {
        delete[] A; // safe even if a is nullptr
    }

    // 2. Copy Constructor (Deep Copy)
    Array(const Array& other) : size(other.size), length(other.length) {
        cout << "[Debug: COpy Constructor Called]" << endl;
        A = new (nothrow) int[size];
        if (!A) {
            cerr << "FATAL ERROR: Memory allocation failed in copy constructor!" << endl;
            size = 0; length = 0; return; // failed state
        }
        for (size_t i = 0; i < length; ++i) {
            A[i] = other.A[i];
        }
    }
    // 3. Copy Assignment Operator (Deep Copy)
    // pick up HERE!!!
    
    // 4. Move Constructor (C++11)
    
    // 5. Move Assignment Operator (C++11)
    
    
    
    
    // --- Basic Operations ---
    void Display();
    void Append(int x);             // Add to end
    void Insert(int index,int x);   // Insert at index (shifts elements)
    int Delete(int index);          // delete from index (shifts elements)
    int Get(int index);             // Get element at index
    void Set(int index, int x);             // Set element at index

    // --- Search Operations ---
    int LinearSearch(int key);      // O(n) - Unosrted/Sorted
    int BinarySearchLoop(int key);  // O(log n) - Requires Sorted Array
    
    // --- Info / Aggregate Operations ---
    int GetLength() { return length; } // Get number of elements
    int GetSize() { return size; }     // Get allocated size
    int Max();                         // O(n)
    int Min();                         // O(n)
    int Sum();                         // O(n)
    float Avg();                       // O(n)
    int isSorted();                    // O(n) - sort check

    // --- Modify Operations ---
    void Reverse();                 // O(n) - Creates a temporary array
    void ReverseInPlace();          // O(n) - Swaps elements in place (formerly RecursiveReverse)
    void InsertSort(int x);         // Insert element maintaining sorted order O(n)
    void Rearrange();               // Moves negative elements before positive O(n)
    
    // --- Set Operations (Require Sorted Arrays for Efficiency) ---
    Array* Merge(Array arr2);           // Merge 2 sorted arrays
    Array* Union(Array arr2);           // Union of 2 sorted arrays
    Array* Intersection(Array arr2);    // Intersection of 2 sorted arrays
    Array* Difference(Array arr2);      // Difference (this - arr2) '     '
    
    // --- Missing Element Operations ---
    // Find the first missing element in a sequence assumed to start from A[0]
    int FindSingleMissingElementSorted(); // Requires SORTED array (Difference method)
    
    // Finds the single missing element assuming consecutive numbers from Min()
    int FindSingleMissingElementUnsortedOptimal(); // Works on UNSORTED array (XOR method)
    
    // Finds multiple missing elements in a sequence assumed to start from A[0]
    void FindMultipleMissingElementsSorted(); // Requires SORTED array (Difference method)
    
    // Finds mutliple missing elements between Min() and Max()
    void FindMultipleMissingElementsHash(); // Works on UNSORTED array (Hash method)
    
};

// --- Method Implementations ---

void Array::Display()
{
    if (length == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    cout<<"Elements (" << length << "/" << size << "): ";
    for(int i = 0; i < length; i++)
        cout<<A[i]<<" ";
    cout<<endl;
}

void Array::Append(int x)
{
    if (length < size)
        A[length++] = x;
    else
        cout << "Error: Array is full, cannot append." << endl;
}

void Array::Insert(int index,int x)
{
    if (length >= size) {
        cout << "Error: Array is full. Cannot insert." << endl;
        return;
    }
    if(index >= 0 && index <= length)
    {
        for(int i = length; i > index; i--)
            A[i] = A[i-1];
        A[index] = x;
        length++;
    } else {
         cout << "Error: invalid index for insert." << endl;
     }
 }

int Array::Delete(int index)
{
    int x = 0; // Consider returning a special value like numeric_limits<int>::min() for error
    if (length == 0) {
        cout << "Error: Array is empty. Cannot delete." << endl;
        return x; // or some error code
    }
    if(index >= 0 && index < length)
    {
        x = A[index];
        for(int i = index; i < length-1; i++)
            A[i] = A[i+1];
        length--;
        return x;
    } else {
        cout << "Error: Invalid index for delete." << endl;
        return x; // or some error code
    }
}

void Array::swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Linear search with move-to-front optimization
int Array::LinearSearch(int key)
{
    for(int i = 0; i < length; i++)
    {
        if(key == A[i])
        {
            // optimiztion: move found element one step towards the front
            if (i > 0) // check boundary cond.
            {
                swap(&A[i], &A[i-1]);
                return i; // return the original index if it was already at the front
            }
        }
    }
    return -1; // not found
}

int Array::BinarySearchLoop(int key)
{
    int l, mid, h;
    l = 0;
    h = length - 1;
    
    while (l <= h)
    {
        mid = l + (h - l) / 2;
        if (key == A[mid])
            return mid;
        else if (key < A[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

int Array::Get(int index)
{
    if(index >= 0 && index < length)
        return A[index];
    return -1;
}

void Array::Set(int index, int x)
{
    if(index >= 0 && index < length)
        A[index] = x;
    else
        cout << "Error: Invalid index for Set." << endl;
}

int Array::Max()
{
    if (length == 0) {
        cerr << "Error: Cannot find maximum of an empty array." << endl;
        // consider throwing an exception or returning numeric_limits<int>::min()
        return -1; // simplfied error indication
    }
    int max_val = A[0];
    for(int i = 1;i < length; i++)
    {
        if (A[i] > max_val)
            max_val = A[i];
    }
    return max_val;
}

int Array::Min()
{
    if (length == 0) {
        cerr << "Error: Cannot find maximum of an empty array." << endl;
        // consider throwing an exception or returning numeric_limits<int>::min()
        return -1; // simplfied error indication
    }
    int min_val = A[0];
    for(int i = 1; i < length; i++)
    {
        if(A[i] < min_val)
            min_val = A[i];
    }
    return min_val;
}

int Array::Sum()
{
    int s = 0;
    for(int i = 0; i < length; i++)
        s += A[i];
    
    return s;
}

float Array::Avg()
{
    if (length == 0) {
        cerr << "Error: Cannot calculate average of an empty array." << endl;
        return 0.0f; // or NAN
    }
    return (float)Sum() / length;
}

// Uses auxilliary array
void Array::Reverse()
{
    if (length == 0 ) return;
    int *B = new int[length];
    int i,j;
    for (i = length - 1, j = 0; i >= 0; i--, j++)
        B[j] = A[i];
    for (i = 0; i < length; i++)
        A[i] = B[i];
    delete[] B; // free allocated memory
}

// Reverses in place using swap
void Array::ReverseInPlace()
{
    int i,j;
    for (i = 0,j = length - 1; i < j; i++, j--) {
        swap(&A[i],&A[j]);
    }
}

// Assumes array should be kept sorted
void Array::InsertSort(int x)
{
    if (length >= size) {
        cout << "Error: Array is full. Cannot insert." << endl;
        return;
    }
    int i = length - 1;
    if (length == size)
        return;
    while (i >= 0 && A[i] > x)
    {
        A[i+1] = A[i];
        i--;
    }
    A[i+1] = x;
    length++;
}

int Array::isSorted()
{
    for(int i = 0; i < length - 1; i++)
    {
        if(A[i]> A[i + 1])
            return 0; // Not sorted
    }
    return 1; // Sorted (or empty/single element)
}

// Rearranges negative numbers before positive numbers
void Array::Rearrange()
{
    int i = 0;
    int j= length - 1;
    
    while (i < j)
    {
        while(i < length && A[i] < 0) i++; // find first non-negative from left
        while(j >= 0 && A[j] >= 0) j--;    // Find first negative from right
        if (i < j)
            swap(&A[i], &A[j]);
        
    }
}

// Assumes this and arr2 are sorted. Returns a NEW array.
Array* Array::Merge(Array arr2)
{
    int i = 0, j= 0, k = 0;
    
    Array *arr3 = new Array(length + arr2.length); // Allocate new array
    
    while(i < length && j < arr2.length)
    {
        if(A[i] < arr2.A[j])
            arr3-> A[k++] = A[i++];
        else
            arr3->A[k++] = arr2.A[j++];
    }
    // copy remaining elements
    for(; i < length; i++)
        arr3->A[k++] = A[i];
    for(;j<arr2.length;j++)
        arr3->A[k++]=arr2.A[j];
    
    arr3->length=length+arr2.length;
    return arr3; // Caller MUST delete this later
}

// Assumes this and arr2 are sorted. Returns a NEW array.
Array* Array::Union(Array arr2)
{
    int i = 0, j = 0, k = 0;
    
    Array *arr3 = new Array(length + arr2.length);
    
    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else if (arr2.A[j] < A[i])
            arr3->A[k++] = arr2.A[j++];
        else // Elements are equal, copy one and advance both
        {
            arr3->A[k++] = A[i++];
            j++;
        }
    }
    // copy remaining elements
    for(;i<length;i++)
        arr3->A[k++]=A[i];
    for(;j<arr2.length;j++)
        arr3->A[k++]=arr2.A[j];
    
    arr3->length=k;
    // optional: resize arr3->A if you want exact size (more complex)
    return arr3; // caller must delete
}

// Assumes this and arr2 are sorted. Returns a NEW array.
Array* Array::Intersection(Array arr2)
{
    int i = 0, j = 0, k = 0;
    
    // Worst case intersection size is min(length, arr2.length)
    Array *arr3 = new Array(length + arr2.length);
    
    while(i < length && j < arr2.length)
    {
        if(A[i] < arr2.A[j])
            i++;
        else if(arr2.A[j] < A[i])
            j++;
        else
        {
            arr3->A[k++] = A[i++];
            j++;
        }
    }
    arr3->length = k;
    return arr3; // caller must delete
}

// Assumes this and arr2 are sorted. Returns a NEW array. (elements in this but not in arr2)
Array* Array::Difference(Array arr2)
{
    int i = 0, j = 0, k = 0;
    
    // worst case difference size is length
    Array *arr3 = new Array(length + arr2.length);
    
    while(i<length && j<arr2.length)
    {
        if(A[i] < arr2.A[j]) // Element only in A
            arr3->A[k++] = A[i++];
        else if(arr2.A[j] < A[i]) // Element only in B, ignore B
            j++;
        else // Elements are equal, skip in both
        {
            i++;
            j++;
        }
    }
    // Copy remaining elements of A (these are definitely not in B)
    for(; i < length; i++)
        arr3->A[k++] = A[i];
    
    arr3->length=k;
    return arr3; // Caller must delete this later
}

// --- Missing Element Functions ---

// Requires SORTED Array
int Array::FindSingleMissingElementSorted()
{
    if (length == 0) return -1; // Cannot find missing in empty
    int expected_diff = A[0] - 0;
    
    for (int i = 0; i < length; i++)
    {
        if (A[i] - i != expected_diff)
        {
            // The missing element is the expected value at this index
            return i + expected_diff;
        }
    }
    // If loop completes, no gap found *within* the elements.
    // Could be missing after the last, or none missing in sequence.
    return -1; // Indicate no gap found by this logic
}

// Works on UNOSRTED array using XOR
int Array::FindSingleMissingElementUnsortedOptimal()
{
    if (length == 0)
    {
        cout<<"Array is empty, cannot find missing element."<<endl;
        return -1;
    }
    
    int min_val = Min();
    if (min_val == -1 && length > 0) { // Check if Min() failed
        cerr << "Error finding mininmum value." << endl;
        return -1;
    }

    int xor_sum_array = 0;
    int xor_sum_expected = 0;
    
    // 1. Calculate XOR sum of elements in array O(n)
    for (int i = 0; i < length; i++)
    {
        xor_sum_array ^= A[i];
    }
    
    // 2. XOR sum of expected sequence (min_val to min_val + length)
    int max_expected = min_val + length;
    for (int current_expected = min_val; current_expected <= max_expected; ++current_expected) {
        xor_sum_expected ^= current_expected;
    }
    
    // 3. Result is the XOR of the 2 sums
    int missing_element = xor_sum_array ^ xor_sum_expected;
    
    // optional basic validation
    if (missing_element < min_val || missing_element > max_expected)
    {
        cout << "Warning: Calculated missing value " << missing_element
             << " is outside the expected range [" << min_val << ", " << max_expected
             << "]. Assumptions might be violated (e.g. multiple missing, non-consecutive numbers)." << endl;
    }
    
    return missing_element;
}

// Requires SORTED array
void Array::FindMultipleMissingElementsSorted()
{
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
void Array::FindMultipleMissingElementsHash()
{
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

// --- Helper Function to Create and Populate an Array ---
// used for set ops requiring a 2nd array
Array* create_and_fill_array(int expected_size, bool must_be_sorted) {
    Array* arr = new Array(expected_size);
    int num_elements, val;
    cout << "Enter number of elements for the second array (max " << expected_size << "): ";
    cin >> num_elements;
    if (num_elements > expected_size || num_elements < 0) {
        cout << "Invalid number of elements. Using 0." << endl;
        num_elements = 0;
    }
    
    cout << "Enter " << num_elements << " elements";
    if (must_be_sorted) cout << " (in sorted order)";
    cout << ":" << endl;
    
    for (int i = 0; i < num_elements; ++i) {
        cin >> val;
        if (must_be_sorted && i > 0 && val < arr->Get(i-1)) {
            cout << "Warning: Elements entered out of order for sorted array requirement!" << endl;
            // Handle appropriately - maybe stop, or just continue with unsorted data
        }
        arr->Append(val); // Append here is simpler than InsertSort()
    }
    
    // If strict sorting needed for Append, use InsertSort instead:
    // for (int i = 0; i < num_elements; ++i) { cin>> val; arr->InsertSort(val); }
    if (must_be_sorted && !arr->isSorted()) {
        cout << "Warning: The second array provided is not sorted, set operations might yield incorrect results." << endl;
    }
    return arr;
}


// --- Main Function (Menu Driven) ---
int main()
{
    Array *arr1 = nullptr; // Initialize to nullptr
    Array *arr2 = nullptr; // for set operations
    Array *arr3 = nullptr; // for results of set operations
    int ch = -1, sz;
    int x, index;
    bool intend_to_be_sorted = false;
    
    cout << "Enter Size of Array: ";
    cin >> sz;
    if (sz <= 0) {
        cout << "Invalid size. Defaulting to 10." << endl;
        sz = 10;
    }
    arr1 = new Array(sz); // Create the main array
    
    char sorted_choice;
    cout << "Do you intend to keep this array sorted? (y/n): ";
    cin >> sorted_choice;
    if(tolower(sorted_choice) == 'y') {
        intend_to_be_sorted = true;
        cout << "--> Array will be treated as sorted. Use 'Insert keeping sort (option 8) to add elements correctly." << endl;
    } else {
        intend_to_be_sorted = false;
        cout << "--> Array will be treated as potentially unsorted."<< endl;
    }
    do
    {
        // clean up result array from previous set operation if it exists
        if (arr3 != nullptr) {
            delete arr3;
            arr3 = nullptr;
        }
        
        // Clean up temporary second arry if it exists
        if (arr2 != nullptr) {
            delete arr2;
            arr2 = nullptr;
        }
        
        
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
        cout << "9 Display Array\n";
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
        cout << "===================================\n";
        cout << "Enter your choice: ";
        cin >> ch;
        
        // Input validation helper
        auto get_int = [](const string& prompt) {
            int val;
            cout << prompt;
            while (!(cin >> val)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            return val;
        };
        
        auto get_index = [&](const string& prompt) {
            int idx = get_int(prompt);
            // Basic validation, specific methods might have more
            if (idx < 0 || idx >= arr1->GetSize()) {
                cout << "Warning: Index might be out of bounds for current operation." << endl;
            }
            return idx;
        };
        
        switch (ch) {
            case 1: // Append
                if (intend_to_be_sorted && arr1->GetLength() > 0){
                    cout << "Warning: Appending may break sort order in Sorted Mode.\n" << endl;
                }
                x = get_int("Enter element to append: ");
                arr1->Append(x);
                arr1->Display();
                break;
            case 2: // Insert at Index
                if (intend_to_be_sorted) {
                    cout << "Warning: Inserting at index may break sort order in Sorted Mode.\n";
                }
                x = get_int("Enter element to insert: ");
                index = get_index("Enter index ");
                arr1->Insert(index, x);
                arr1->Display();
                break;
            case 3:
                x = get_int("Enter element to insert (keeping sorted): ");
                arr1->InsertSort(x);
                arr1->Display();
                break;
            case 4:
                index = get_index("Enter index to delete: ");
                x = arr1->Delete(index);
                if(index >= 0 && index < arr1->GetLength()+1) { // Check if delete was likely valid
                    cout << "Deleted Element was: " << x << "\n";
                } // Delete method prints errors for invalid index
                arr1->Display();
                break;
                
                // --- Search ---
            case 5: // Linear Search
                x = get_int("Enter element to search (Linear): ");
                index = arr1->LinearSearch(x);
                if (index != -1)
                    cout << "element found at index " << index << "\n";
                else
                    cout << "Element not found.\n";
                break;
            case 6: // Binary search
                if (!arr1->isSorted()) {
                    cout << "ERROR: Array must be sorted for Binary Search.\n";
                } else {
                    x = get_int("Enter element to search (Binary): ");
                    index = arr1->BinarySearchLoop(x);
                    if (index != -1)
                        cout << "Element found at index: " << index << "\n";
                    else
                        cout << "Element not found.\n";
                }
                break;
                // --- Get/Set ---
            case 7: // Get
                index = get_index("Enter index to get element from: ");
                x = arr1->Get(index);
                if (x != -1 || (index >= 0 && index < arr1->GetLength())) {
                    cout << "Element at index " << index << " is: " << x << "\n";
                }
                break;
            case 8: // Set
                
                break;
                
                // --- Info ---
            case 9: // Display
                arr1->Display();
                break;
            case 10: // Sum
                cout << "Sum of elements: " << arr1->Sum() << "\n";
                break;
            case 11: // Average
                cout << "Average of elements: " << arr1->Avg() << "\n";
                break;
            case 12: // Max
                cout << "Maximum elements: " << arr1->Max() << "\n";
                break;
            case 13: // Min
                cout << "Minimum elements: " << arr1->Min() << "\n";
                break;
            case 14: // isSorted
                if (arr1->isSorted())
                    cout << "Array IS currently sorted.\n";
                else
                    cout << "Array is NOT currently sorted.\n";
                break;
                
                // --- Modify ---
            case 15: // Reverse (Temp Array)
                cout << "Reversing array (using temp array)..." << endl;
                arr1->Reverse();
                arr1->Display();
                break;
            case 16: // Reverse (in place)
                cout << "Reversing array in place..." << endl;
                arr1->ReverseInPlace();
                arr1->Display();
                break;
            case 17: // Rearrange
                cout << "Rearranging negatives before positives..." << endl;
                arr1->Rearrange();
                arr1->Display();
                break;
                
                // --- Set Operations ---
            case 18: case 19: case 20: case 21: // Merge, Union, Intersection, Difference
            { // Use block scope for arr2 and arr3
                cout << "--- Set Operation ---" << endl;
                cout << "This operation requires a second SORTED array." << endl;
                if (!arr1->isSorted()) {
                    cout << "Warning: The main array (Arr1) is not sorted. Results may be incorrect." << endl;
                }
                // Create and fill the second array
                arr2 = create_and_fill_array(1000, true); // allows up to 1000 elements for arr2
                cout << "Arr1: "; arr1->Display();
                cout << "Arr2: "; arr2->Display();
                
                if (ch == 18) arr3 = arr1->Merge(*arr2);
                else if (ch == 19) arr3 = arr1->Union(*arr2);
                else if (ch == 20) arr3 = arr1->Intersection(*arr2);
                else if (ch == 21) arr3 = arr1->Difference(*arr2);
                
                if (arr3 != nullptr) {
                    cout << "Result: ";
                    arr3->Display();
                    // IMPORTANT: arr3 needs deletion, handled at start of loop
                } else {
                    cout << "Operation failed or resulted in null array." << endl;
                }
                // arr2 needs deletion, handled at start of loop
            }
                break; // end of set ops blocks
                
                // --- Missing Elements ---
            case 22: // Find Single Missing Element (Smart)
                if (intend_to_be_sorted) {
                    cout << "Finding single missing element using SORTED logic...\n";
                    if (!arr1->isSorted()) {
                        cout << "ERROR: Array is currently NOT sorted, cannot use this method accurately.\n";
                    } else {
                        int missing = arr1->FindSingleMissingElementSorted();
                        if (missing != -1)
                            cout << "Missing element (Sorted method) is: " << missing << "\n";
                        else
                            cout << "No single missing element found using the sorted method's logic.\n";
                    }
                } else {
                    cout << "Finding single missing element using UNSORTED OPTIMAL logic...\n";
                    int missing = arr1->FindSingleMissingElementUnsortedOptimal();
                    // handles empty array case, may print warnings itself
                    if (arr1->GetLength() > 0) {
                        cout << "Calculated missing element (unsorted optimal) is: " << missing << "\n";
                    }
                }
                break;
            case 23: // Find Multiple Missing (Sorted)
                if (!arr1->isSorted()) {
                    cout << "ERROR: Array must be sorted for this method.\n";
                } else {
                    arr1->FindMultipleMissingElementsSorted();
                }
                break;
            case 24: // Find Multiple Missing (Unsorted hash)
                arr1->FindMultipleMissingElementsHash();
                break;
            
            // --- Exit ---
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (ch != 0); // Loop until exit choice
        
        // --- Cleanup ---
        delete arr1; // Clean up memory
        if (arr2!= nullptr) delete arr2; // delete second array if it exists
        if (arr3!= nullptr) delete arr3;// delete result arra if it exists
        
        return 0;
    }
