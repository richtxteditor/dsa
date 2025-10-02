//
//  DSA-Project-Tests.mm
//  DSA-Project
//
//  Created by richie on 9/20/25.
//

#import <XCTest/XCTest.h>
#include "array.h" // Your single, complete header file
#include "strings.h"
#include <string>  // Needed for std::string tests
#include <sstream>

// The test class must still be an Objective-C interface
@interface ArrayTests : XCTestCase
@end

@implementation ArrayTests

// --- Tests for Integer Arrays (Array<int>) ---

- (void)testIntegerArray_DynamicResizing {
    // Arrange
    Array<int> arr(1);
    XCTAssertEqual(arr.GetSize(), 1);

    // Act
    arr.Append(10);
    arr.Append(20); // This should trigger a resize

    // Assert
    XCTAssertEqual(arr.GetSize(), 2);
    XCTAssertEqual(arr.GetLength(), 2);
    XCTAssertEqual(arr.Get(1).value_or(-1), 20);
}

- (void)testIntegerArray_PairWithSum_Sorted {
    // Arrange
    Array<int> arr(5);
    arr.Append(1);
    arr.Append(3);
    arr.Append(4);
    arr.Append(6);
    arr.Append(8);
    int k = 10;

    // Act
    std::optional<std::pair<int, int>> result = arr.PairWithSum_Sorted(k);

    // Assert
    XCTAssertTrue(result.has_value());
    XCTAssertEqual(result->first, 4);
    XCTAssertEqual(result->second, 6);
}

- (void)testIntegerArray_PairWithSum_Hashing {
    // Arrange
    Array<int> arr(5);
    arr.Append(6);
    arr.Append(3);
    arr.Append(8);
    arr.Append(2);
    int k = 10;

    // Act
    auto result = arr.PairWithSum_Hashing(k);

    // Assert
    XCTAssertTrue(result.has_value());
    XCTAssertEqual(result->first + result->second, 10);
}

- (void)testIntegerArray_FindMinMax {
    // Arrange
    Array<int> arr(7);
    arr.Append(5);
    arr.Append(-2);
    arr.Append(100);
    arr.Append(0);
    arr.Append(50);
    arr.Append(-10);
    arr.Append(25);

    // Act
    auto result = arr.FindMinMax();

    // Assert
    XCTAssertTrue(result.has_value());
    XCTAssertEqual(result->first, -10);
    XCTAssertEqual(result->second, 100);
}


// --- Tests for Double Arrays (Array<double>) ---

- (void)testDoubleArray_Functionality {
    // Arrange
    Array<double> arr(3);

    // Act
    arr.Append(3.14);
    arr.Append(9.81);
    arr.Append(2.71);
    
    // Assert
    XCTAssertEqual(arr.GetLength(), 3);
    XCTAssertEqual(arr.Min(), 2.71);
    XCTAssertEqual(arr.Max(), 9.81);
}


// --- Tests for String Arrays (Array<std::string>) ---

- (void)testStringArray_Functionality {
    // Arrange
    Array<std::string> arr(3);
    
    // Act
    arr.InsertSort("Hello");
    arr.InsertSort("World");
    arr.InsertSort("Apple");
    arr.InsertSort("Zoo");
    
    // Assert
    XCTAssertEqual(arr.GetLength(), 4);
    
    XCTAssertTrue(arr.Get(0).value_or("") == "Apple", "First element should be 'Apple'");
    XCTAssertTrue(arr.Get(1).value_or("") == "Hello", "Second element should be 'Hello'");
    XCTAssertTrue(arr.isSorted(), "Array should be sorted after InsertSort"); // "Apple", "Hello", "World", "Zoo" is sorted
    
    // Visually confirm display
    NSLog(@"Testing Display() with std::string:");
    arr.Display();
}

@end

@interface StringTests : XCTestCase
@end

@implementation StringTests

- (void)testReverseString {
    std::string s1 = "hello";
    reverse_string(s1);
    XCTAssertEqual(s1, std::string("olleh"));

    std::string s2 = "";
    reverse_string(s2);
    XCTAssertEqual(s2, std::string(""));

    std::string s3 = "a";
    reverse_string(s3);
    XCTAssertEqual(s3, std::string("a"));

    std::string s4 = "ab";
    reverse_string(s4);
    XCTAssertEqual(s4, std::string("ba"));
}

- (void)testIsPalindrome {
    XCTAssertTrue(is_palindrome("madam"));
    XCTAssertFalse(is_palindrome("hello"));
    XCTAssertTrue(is_palindrome(""));
    XCTAssertTrue(is_palindrome("a"));
    XCTAssertTrue(is_palindrome("level"));
    XCTAssertFalse(is_palindrome("levels"));
}

- (void)testFindDuplicatesHashing {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    find_duplicates_hashing("hello");
    std::string output = buffer.str();
    XCTAssertTrue(output.find("'l', Occurences: 2") != std::string::npos);

    buffer.str("");
    find_duplicates_hashing("world");
    output = buffer.str();
    XCTAssertTrue(output.find("Duplicates Found: ") != std::string::npos);
    
    std::cout.rdbuf(old);
}

- (void)testFindDuplicatesBitwise {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    find_duplicates_bitwise("hello");
    std::string output = buffer.str();
    XCTAssertTrue(output.find("'l' is a duplicate.") != std::string::npos);

    buffer.str("");
    find_duplicates_bitwise("world");
    output = buffer.str();
    XCTAssertTrue(output.find("No duplicate alphabetic characters found.") != std::string::npos);

    std::cout.rdbuf(old);
}

- (void)testAreAnagramsHash {
    XCTAssertTrue(are_anagrams_hash("listen", "silent"));
    XCTAssertFalse(are_anagrams_hash("hello", "world"));
    XCTAssertTrue(are_anagrams_hash("Debit card", "Bad credit"));
}

- (void)testAreAnagramsBitwise {
    XCTAssertTrue(are_anagrams_bitwise("listen", "silent"));
    XCTAssertFalse(are_anagrams_bitwise("hello", "world"));
    XCTAssertTrue(are_anagrams_bitwise("Debit card", "Bad credit"));
    XCTAssertTrue(are_anagrams_bitwise("hello", "olleh"));
}

@end

@interface ArrayComprehensiveTests : XCTestCase
@end

@implementation ArrayComprehensiveTests

- (void)testCopyConstructor {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(20);

    Array<int> arr2 = arr1;
    arr2.Append(30);

    XCTAssertEqual(arr1.GetLength(), 2);
    XCTAssertEqual(arr2.GetLength(), 3);
}

- (void)testCopyAssignment {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(20);

    Array<int> arr2;
    arr2.Append(100);

    arr2 = arr1;
    arr2.Append(30);

    XCTAssertEqual(arr1.GetLength(), 2);
    XCTAssertEqual(arr2.GetLength(), 3);
}

- (void)testMoveConstructor {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(20);

    Array<int> arr2 = std::move(arr1);

    XCTAssertEqual(arr1.GetLength(), 0);
    XCTAssertEqual(arr2.GetLength(), 2);
}

- (void)testMoveAssignment {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(20);

    Array<int> arr2;
    arr2.Append(100);

    arr2 = std::move(arr1);

    XCTAssertEqual(arr1.GetLength(), 0);
    XCTAssertEqual(arr2.GetLength(), 2);
}

- (void)testInsert {
    Array<int> arr;
    arr.Append(10);
    arr.Append(30);
    arr.Insert(1, 20);

    XCTAssertEqual(arr.Get(1).value(), 20);
    XCTAssertEqual(arr.GetLength(), 3);

    XCTAssertThrowsSpecific(arr.Insert(10, 100), std::out_of_range);
}

- (void)testDelete {
    Array<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);

    int deleted = arr.Delete(1);

    XCTAssertEqual(deleted, 20);
    XCTAssertEqual(arr.Get(1).value(), 30);
    XCTAssertEqual(arr.GetLength(), 2);

    XCTAssertThrowsSpecific(arr.Delete(10), std::out_of_range);
}

- (void)testLinearSearch {
    Array<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);

    auto result = arr.LinearSearch(20);
    XCTAssertTrue(result.has_value());
    XCTAssertEqual(result.value(), 0);

    result = arr.LinearSearch(100);
    XCTAssertFalse(result.has_value());
}

- (void)testBinarySearch {
    Array<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);

    auto result = arr.BinarySearchLoop(20);
    XCTAssertTrue(result.has_value());
    XCTAssertEqual(result.value(), 1);

    result = arr.BinarySearchLoop(100);
    XCTAssertFalse(result.has_value());
}

- (void)testReverse {
    Array<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);

    arr.Reverse();

    XCTAssertEqual(arr.Get(0).value(), 30);
    XCTAssertEqual(arr.Get(2).value(), 10);
}

- (void)testReverseInPlace {
    Array<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);

    arr.ReverseInPlace();

    XCTAssertEqual(arr.Get(0).value(), 30);
    XCTAssertEqual(arr.Get(2).value(), 10);
}

- (void)testMerge {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(30);

    Array<int> arr2;
    arr2.Append(20);
    arr2.Append(40);

    Array<int> arr3 = arr1.Merge(arr2);

    XCTAssertEqual(arr3.GetLength(), 4);
    XCTAssertEqual(arr3.Get(0).value(), 10);
    XCTAssertEqual(arr3.Get(1).value(), 20);
    XCTAssertEqual(arr3.Get(2).value(), 30);
    XCTAssertEqual(arr3.Get(3).value(), 40);
}

- (void)testUnion {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(30);

    Array<int> arr2;
    arr2.Append(10);
    arr2.Append(40);

    Array<int> arr3 = arr1.Union(arr2);

    XCTAssertEqual(arr3.GetLength(), 3);
    XCTAssertEqual(arr3.Get(0).value(), 10);
    XCTAssertEqual(arr3.Get(1).value(), 30);
    XCTAssertEqual(arr3.Get(2).value(), 40);
}

- (void)testIntersection {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(30);

    Array<int> arr2;
    arr2.Append(10);
    arr2.Append(40);

    Array<int> arr3 = arr1.Intersection(arr2);

    XCTAssertEqual(arr3.GetLength(), 1);
    XCTAssertEqual(arr3.Get(0).value(), 10);
}

- (void)testDifference {
    Array<int> arr1;
    arr1.Append(10);
    arr1.Append(30);

    Array<int> arr2;
    arr2.Append(10);
    arr2.Append(40);

    Array<int> arr3 = arr1.Difference(arr2);

    XCTAssertEqual(arr3.GetLength(), 1);
    XCTAssertEqual(arr3.Get(0).value(), 30);
}

@end
