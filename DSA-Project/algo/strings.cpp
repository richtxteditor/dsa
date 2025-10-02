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
        // pair.first is the key, pari.second is its count (value)
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
