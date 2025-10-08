//
//  strings.cpp
//  DSA-Project
//
//  Created by richie on 9/23/25.
//

#include "strings.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <cassert>


void perm_build_helper(const std::string& original, std::string& current_perm,
                       std::vector<bool>& used, size_t k,
                       std::vector<std::string>& results) {
    // base case: if we have filled all the slots (k is the length of the string),
    // we have a complete permutation.
    if (k == original.length()) {
        results.push_back(current_perm);
        return;
    }
    
    // recursive step: try to place each available character in the current slot 'k'.
    for (size_t i = 0; i < original.length(); ++i) {
        // check if the character at index 'i' in the original string is available.
        if (!used[i]) {
            // place the character
            current_perm[k] = original[i];
            
            // mark as used
            used[i] = true;
            
            // recurse to fill the next slot (k + 1)
            perm_build_helper(original, current_perm, used, k + 1, results);
            
            // backtrack: un-mark the character as used,
            // so it can be picked for a different position
            // in another branch of the recursion.
            used[i] = false;
        }
    }
}

std::vector<std::string> generate_permutations_backtracking(const std::string& s) {
    std::vector<std::string> results;
    if (s.empty()) {
        results.push_back("");
        return results;
    }
    
    // recursion state
    std::string current_perm(s.length(), ' ');
    std::vector<bool> used(s.length(), false);
   
    // start the recursion at the first slot (k = 0)
    perm_build_helper(s, current_perm, used, 0, results);
    
    return results;
}



void perm_helper(std::string& s, size_t low, size_t high, std::vector<std::string>& result) {
    // Base case: if low and high meet, we have a complete permutation.
    if (low == high) {
        result.push_back(s);
        return;
    }
    
    for (size_t i = low; i <= high; ++i) {
        std::swap(s[low], s[i]);
        // recurse on the rest of the string.
        perm_helper(s, low + 1, high, result);
        // backtrack
        std::swap(s[low], s[i]);
    }
}


std::vector<std::string> generate_permutations(const std::string& s) {
    std::vector<std::string> result;
    if (s.empty()) {
        return result;
    }
    
    std::string s_copy = s;
    
    perm_helper(s_copy, 0, s.length() - 1, result);
    return result;
}

void reverse_string(std::string& s) {
    if (s.empty()) return;
    size_t low = 0, high = s.length() - 1;
    while (low < high) {
        std::swap(s[low], s[high]);
        ++low;
        --high;
    }
}

bool is_palindrome(const std::string& s) {
    if (s.empty()) return true;
    size_t low = 0, high = s.length() - 1;
    while (low < high) {
        if (s[low] != s[high]) {
            return false;
        }
        ++low;
        --high;
    }
    return true;
}

void find_duplicates_hashing(const std::string& s) {
    std::unordered_map<char, int> freq_map;
    for (char c : s) {
        char normalized_char = tolower(c);
        freq_map[normalized_char]++;
    }
    
    std::cout << "\nDuplicates Found: ";
    for (const auto& pair : freq_map) {
        // pair.first is the key, pair.second is its count (value)
        if (pair.second > 1) {
            // add a check to avoid reporting spaces or punctuation as duplicates.
            if (isalpha(pair.first)) {
                std::cout << "\nCharacter: '" << pair.first << "', Occurences: " << pair.second << std::endl;
            }
        }
    }
}

void find_duplicates_bitwise(const std::string& s) {
    long long flags = 0;
    long long duplicates = 0;
    
    for (char original_char : s) {
        
        if (!isalpha(original_char)) {
            continue;
        }
        
        char c = tolower(original_char);
        
        // calculate how much to shift
        long long mask = 1LL << (c - 'a');
        
        // check if letter's bti is already 'on' in our flags.
        if ((flags & mask) > 0) {
            
            // it's a duplicate. Turn on its bit in the 'duplicates' field.
            duplicates |= mask;
        }
        // in either case, mark that we've seen this letter by turning its bits 'on'.
        flags |= mask;
    }
    
    std::cout << "\nDuplicates found (bitwise method):\n" << std::endl;
    bool any_duplicates_found = false;
    for (size_t i = 0; i < 26; i++) {
        long long mask = 1LL << i;
        if ((duplicates & mask) > 0) {
            std::cout << "'" << static_cast<char>('a' + i) << "' is a duplicate.\n" << std::endl;
            any_duplicates_found = true;
        }
    }
    
    if (!any_duplicates_found) {
        std::cout << "No duplicate alphabetic characters found.\n" << std::endl;
    }
}

bool are_anagrams_hash(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) return false;
    if (s1 == s2) return false;
    std::unordered_map<char, int> freq_map;
    for (char c : s1) freq_map[tolower(c)]++;
    for (char c: s2) freq_map[tolower(c)]--;
    for (const auto& pair : freq_map) if (pair.second != 0) return false;
    return true;
}

bool are_anagrams_bitwise(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) return false;

    long long char_counts[26] = {0};

    for (char c : s1) {
        if (isalpha(c)) {
            char_counts[tolower(c) - 'a']++;
        }
    }

    for (char c : s2) {
        if (isalpha(c)) {
            char_counts[tolower(c) - 'a']--;
        }
    }

    for (int i = 0; i < 26; ++i) {
        if (char_counts[i] != 0) {
            return false;
        }
    }

    return true;
}
