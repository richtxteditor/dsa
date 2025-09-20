//
//  ArrayCPPTests.mm
//  ArrayCPP
//
//  Created by richie on 9/20/25.
//

#import <XCTest/XCTest.h>
#include "Array.h" // Include your C++ header
#include <vector>
#include <utility>
#include <algorithm>

// The test class must be an Objective-C interface
@interface ArrayTests : XCTestCase
@end

@implementation ArrayTests

- (void)testDynamicResizingOnAppend {
    // 1. Arrange: Create an array with a known, small capacity.
    Array arr(2);
    XCTAssertEqual(arr.GetSize(), 2, "Initial size should be 2");

    // 2. Act: Add elements to fill and then exceed the initial capacity.
    arr.Append(10);
    arr.Append(20);
    
    XCTAssertEqual(arr.GetLength(), 2, "Length should be 2 before resizing");

    // This append should trigger the resize
    arr.Append(30);

    // 3. Assert: Verify the array's state is correct after resizing.
    XCTAssertEqual(arr.GetLength(), 3, "Length should be 3 after resizing");
    XCTAssertEqual(arr.GetSize(), 4, "Size should have doubled to 4 after resizing");
    
    // Also check that the data is still correct
    std::optional<int> val = arr.Get(2);
    XCTAssertTrue(val.has_value(), "Element at index 2 should exist");
    XCTAssertEqual(val.value_or(-1), 30, "The newly appended element should be 30");
}

- (void)testDynamicResizingOnInsert {
    // Arrange
    Array arr(1);
    arr.Append(100);
    
    XCTAssertEqual(arr.GetSize(), 1, "Initial size should be 1");
    
    // Act: This insert should trigger a resize
    arr.Insert(0, 99);
    
    // Assert
    XCTAssertEqual(arr.GetLength(), 2, "Length should be 2 after insert");
    XCTAssertEqual(arr.GetSize(), 2, "Size should have doubled to 2");
    XCTAssertEqual(arr.Get(0).value_or(-1), 99, "New element should be at index 0");
    XCTAssertEqual(arr.Get(1).value_or(-1), 100, "Old element should be at index 1");
}

- (void)testFindDuplicatesUnsorted_BruteForce {
    // 1. Arrange: Create an array with known duplicates.
    Array arr;
    arr.Append(8);
    arr.Append(3);
    arr.Append(6);
    arr.Append(4);
    arr.Append(6);
    arr.Append(5);
    arr.Append(6);
    arr.Append(8);
    arr.Append(2);
    arr.Append(7);

    // 2. Act: Call the function to find duplicates.
    std::vector<std::pair<int, int>> duplicates = arr.FindDuplicatesUnsorted_BruteForce();

    // 3. Assert: Verify the duplicates and their counts are correct.
    XCTAssertEqual(duplicates.size(), 2, "Should find 2 duplicate values");

    // Sort for consistent order
    std::sort(duplicates.begin(), duplicates.end());

    bool found6 = false;
    bool found8 = false;

    for (const auto& p : duplicates) {
        if (p.first == 6) {
            XCTAssertEqual(p.second, 3, "Value 6 should appear 3 times");
            found6 = true;
        } else if (p.first == 8) {
            XCTAssertEqual(p.second, 2, "Value 8 should appear 2 times");
            found8 = true;
        }
    }

    XCTAssertTrue(found6, "Duplicate value 6 was not found");
    XCTAssertTrue(found8, "Duplicate value 8 was not found");
}

- (void)testRearrangePartitionsNegativesAndPositives {
    // 1. Arrange
    Array testArr(10);
    testArr.Append(-6);
    testArr.Append(3);
    testArr.Append(-8);
    testArr.Append(10);
    testArr.Append(5);
    testArr.Append(-1);
    testArr.Append(-15);
    testArr.Append(2);

    // 2. Act
    testArr.Rearrange();

    // 3. Assert
    bool found_positive = false;
    for (size_t i = 0; i < testArr.GetLength(); ++i) {
        int val = testArr.Get(i).value();
        if (val >= 0) {
            found_positive = true;
        }
        // If we have already found a positive number, any subsequent
        // number MUST also be positive. If not, the test fails.
        if (found_positive) {
            XCTAssertGreaterThanOrEqual(val, 0, "Found a negative number after a positive one, partitioning failed.");
        }
    }
}

@end

