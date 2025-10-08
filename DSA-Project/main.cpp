//
//  main.cpp
//  ArrayCPP
//
//  Created by richie on 12/19/24.
//

#include <iostream>
#include <cctype>
#include <limits>
#include <string>
#include <thread>
#include <chrono>
#include "ds/array.h"
#include "algo/strings.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::to_string;
using std::numeric_limits;
using std::streamsize;


int get_validated_integer(const string& prompt,
                          int min_val = numeric_limits<int>::min(),
                          int max_val = numeric_limits<int>::max()) {
    int value;
    cout << prompt;
    
    while (!(cin >> value) || value < min_val || value > max_val) {
        cout << "invalid input. Please enter an integer";
        if (min_val != numeric_limits<int>::min() || max_val != numeric_limits<int>::max()) {
            cout << " between " << min_val << " and " << max_val;
        }
        cout << " : ";
        cin.clear(); // clear the error flag on cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
    }
    // Discard any leftover chars in the input buffer (like new line)
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return value;
}

// --- Helper Function to Create and Populate an Array ---
// used for set ops requiring a 2nd array
Array<int> create_and_fill_array(size_t expected_size, bool must_be_sorted) {
    Array<int> arr(expected_size); // create local array obj
    
    // Use the helper to get the number of elements, enforcing the range [0, expected_size]
    string prompt = "Enter number of elements for the 2nd array(max " +to_string(expected_size) + "): ";
    int num_elements = get_validated_integer(prompt, 0, static_cast<int>(expected_size));
    if (num_elements > 0) {
        cout << "Enter " << num_elements << " elements";
        if (must_be_sorted) cout << " (in sorted order)";
        cout << " : " << endl;
    }
    
    for (int i = 0; i < num_elements; ++i) {
        int val = get_validated_integer("Element " + to_string(i + 1) + ": ");
        
        if (must_be_sorted) {
            arr.InsertSort(val); // InsertSort is better herer as it maintains order
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

void demonstrate_string_algorithms() {
    cout << "\n--- Demonstrating String Algorithms ---" << endl;
    
    // 1. Reverse string
    cout << "\n1. Reversing a given string" << endl;
    std::string str_to_reverse = "Hello World";
    cout << "Original: \"" << str_to_reverse << "\"" << endl;
    reverse_string(str_to_reverse);
    cout << "Reversed: \"" << str_to_reverse << "\"" << endl;
    
    // 2. is_palindrome
    cout << "\n2. Checking for Palindromes" << endl;
    std::string p1 = "RACECAR";
    std::string p2 = "HELLO";
    std::string p3 = "";
    
    cout << "\"" << p1 << "\" is a palindrome: " << (is_palindrome(p1) ? "Yes" : "No") << endl;
    cout << "\"" << p2 << "\" is not a palindrome: " << (is_palindrome(p2) ? "Yes" : "No") << endl;
    cout << "\"\" (empty string) is a palindrome: " << (is_palindrome(p3) ? "Yes" : "No") << endl;
    
    // --- 3. Test duplicate finding (case-insensitive) ---
    cout << "\n3. Finding Duplicates (case insensitive)\n" << endl;
    std::string dup_str_complex = "A quick brown Fox jumps over the lazy Dog";
    
    cout << "Testing string: \"" << dup_str_complex << "\"\n" << endl;
    
    cout << "--- Hashing Method Output ---" << endl;
    find_duplicates_hashing(dup_str_complex);
    
    cout << "\n--- Bitwise Method Output ---" << endl;
    find_duplicates_bitwise(dup_str_complex);
    
    cout << "Testing string with no alphabetic duplicates in hashing method..." << endl;
    std::string dup_str_simple = "JUMPING!";
    find_duplicates_hashing(dup_str_simple);
    
    // 4. --- Testing are_anagrams (hashing method) ---
    std::string ana1 = "decimal";
    std::string ana2 = "medical";
    std::string ana3 = "apple";
    std::string ana4 = "pleap";
    std::string ana5 = "hello";
    
    cout << "\"" << ana1 << "\" and \"" << ana2 << "\" are anagrams: " << (are_anagrams_hash(ana1, ana2) ? "Yes" : "No") << endl;
    cout << "\"" << ana3 << "\" and \"" << ana4 << "\" are anagrams: " << (are_anagrams_hash(ana3, ana4) ? "Yes" : "No") << endl;
    cout << "\"" << ana1 << "\" and \"" << ana5 << "\" are anagrams: "<< (are_anagrams_hash(ana1, ana5) ? "Yes" : "No") << endl;
    
    
    // --- 5. Test have_same_character_set (Bitwise Method) ---
    cout << "\n5. Checking for Same Character Set (Bitwise Method)" << endl;
    std::string set1 = "decimal"; // No duplicate letters
    std::string set2 = "medical"; // No duplicate letters
    std::string set3 = "apple";   // Has duplicate letters
    std::string set4 = "planet";  // Different set of letters

    cout << "(\"" << set1 << "\", \"" << set2 << "\") have the same character set: " << (are_anagrams_bitwise(set1, set2) ? "Yes" : "No") << endl;
    cout << "(\"" << set1 << "\", \"" << set4 << "\") have the same character set: " << (are_anagrams_bitwise(set1, set4) ? "Yes" : "No") << endl;

    // The following line will cause the program to crash in Debug mode because of the assert,
    // which is the INTENDED behavior. You can uncomment it to test your assert.
    // cout << "\n--- Testing assert with invalid input ---" << endl;
    // have_same_character_set(set3, set1); // This should crash with an assertion failure.
    
    // --- 6. Test Permutations ---
    cout << "\n6. Generating Permutations for \"ABC\"" << endl;
    
    cout << endl;
    
    std::string perm_str = "ABC";

    // Method 1: Swapping
    cout << "--- Swapping Method ---" << endl;
    std::vector<std::string> permutations1 = generate_permutations(perm_str);
    for (const auto& p : permutations1) {
        cout << p << " ";
    }
    
    cout << endl;
    
    // Method 2: Backtracking
    cout << "\n--- Backtracking Method ---" << endl;
    std::vector<std::string> permutations2 = generate_permutations_backtracking(perm_str);
    for (const auto& p : permutations2) {
        cout << p << " ";
    }
   
    cout << endl;
    
    cout << "\n---------------------------------------\n" << endl;
}


// --- Main Function (Menu Driven) ---
int main() {
    
    cout << "Welcome to the DSA-Project!" << endl;
    
    // string algos first
    demonstrate_string_algorithms();
    
    Array<int> *arr1 = nullptr; // Initialize to nullptr
    int ch = -1;
    size_t sz; // use size_t for size input
    
    cout << "Enter Size of Array: ";
    // basic input validation for size
    while (!(cin >> sz) || sz == 0) {
        cout << "Invalid input. Please enter a positive integer size.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    arr1 = new Array<int>(sz); // Create the main array
    
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
        cout << "\n=== Menu (" << (intend_to_be_sorted ? "Sorted Mode" : "Unsorted Mode") << ") ===" << endl;
        // Add/Delete
        cout << "1. Append Element\n";
        cout << "2. Insert Element at Index\n";
        cout << "3. Insert Element (Requires Sorted Array)\n";
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
        
        // Array Operations
        cout << "22. Find Single Missing Element (Smart)\n";
        cout << "23. Find Multiple Missing Elements (Sorted Method)\n";
        cout << "24. Find Multiple Missing Elements (Unosrted Hash Method)\n";
        cout << "25. Find Duplicated Elements (Sorted Array Method)\n";
        cout << "26. Find Duplciates (Unsorted Brute Force)\n";
        cout << "27. Find Pair with Sum K\n";
        cout << "28. Find Min and Max (Single Scan) K\n";
        
        // Exit
        cout << "0. Exit\n";
        cout << "==========================\n";
        
        // Input
        cout << "Enter your choice: ";
        cin >> ch;
        
        // Input validation for ch
        while (!cin) {
            cout << "Invalid input. Please enter a number for the menu choice: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Prompt and read AGAIN inside loop
            cout << "====================\n";
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
                Array<int> arr2_local = create_and_fill_array(100, true); // size 100 for temp array
                cout << "Arr1: "; arr1->Display();
                cout << "Arr2: "; arr2_local.Display();
                
                // result array created locally by return-by-value
                Array<int> result_array;
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
            case 24: // Find Multiple Missing Elements in an Unsorted Hash map
                arr1->FindMultipleMissingElementsHash();
                break;
            case 25: // Find duplicates in a sorted array
                if (!arr1->isSorted()) {
                    cout << "ERROR: Array must be sorted to find duplicates using this method.\n";
                    cout << "Please sort the first array or use a method for unsorted arrays.\n";
                } else {
                    arr1->FindDuplicatesSorted();
                }
            case 26: // Count duplicates
            {
                auto duplicates_list = arr1->FindDuplicatesUnsorted_BruteForce();
                
                if(duplicates_list.empty()) {
                    cout << "No duplicates found in the array." << endl;
                } else {
                    cout << "\nDuplciates Found:" << endl;
                    for (const auto& pair : duplicates_list) {
                        cout << "The value" << pair.first
                        <<", occurrs " << pair.second << " times." << endl;
                    }
                }
                break;
            }
            case 27:
            {
                int k = get_validated_integer("Enter the target sum k: ");
                
                // Use the best method dependong on if the user intends the array to be sorted
                std::optional<std::pair<int, int>> result;
                if (intend_to_be_sorted) {
                    cout << "Using sorted array method..." << endl;
                    result = arr1->PairWithSum_Sorted(k);
                } else {
                    cout << "Using hashing method..." << endl;
                    result = arr1->PairWithSum_Hashing(k);
                }
                
                if (result) {
                    cout << "Pair found: (" << result->first << ", " << result->second << ")" << endl;
                } else {
                    cout << "No pair found with the sum" << k << "." << endl;
                }
                break;
            }
            case 28:
            {
                auto result = arr1->FindMinMax();
                if (result) {
                    cout << "Minimum element: " << result->first << endl;
                    cout << "Maximum element: " << result->second << endl;
                } else {
                    cout << "Array is empty." << endl;
                }
                break;
            }
            case 0: cout << "Exiting program." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl; break;
        }
        cout << "------------------------------------------------\n";
        
        // Timed Pause logic here
        if (ch != 0) {
            cout << "\nJust a moment...\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(4));
    } while (ch != 0);
    
    // --- Cleanup ---
    delete arr1; // Delete the main array allocated in main
    
    return 0;
}
