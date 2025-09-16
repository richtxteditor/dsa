//
//  ArrayTests.mm
//  ArrayCPP
//
//  Created by richie on 9/15/25.
//

// ArrayTests.mm

#import <XCTest/XCTest.h>
#include "Array.h" // Include your C++ header

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

@end
