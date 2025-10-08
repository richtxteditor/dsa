//
//  strings.h
//  DSA-Project
//
//  Created by richie on 9/23/25.
//

#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <cassert>
#include <vector>

// Function to reverse a string in-place
void reverse_string(std::string& s);

// Function to check if a string is a palindrome
bool is_palindrome(const std::string& s);

// Function to find duplicate characters using a hash map
void find_duplicates_hashing(const std::string& s);

// Function to find duplicate characters using bitwise operations
void find_duplicates_bitwise(const std::string& s);

// Function to check if two strings are anagrams
bool are_anagrams_hash(const std::string& s1, const std::string& s2);

bool are_anagrams_bitwise(const std::string& s1, const std::string& s2);

std::vector<std::string> generate_permutations(const std::string& s);

std::vector<std::string> generate_permutations_backtracking(const std::string& s);

#endif // STRINGS_H
