//
//  ArrayCPPTests.mm
//  ArrayCPP
//
//  Created by richie on 9/20/25.
//

#import <XCTest/XCTest.h>
#include "array.h" // Your single, complete header file
#include <string>  // Needed for std::string tests

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
