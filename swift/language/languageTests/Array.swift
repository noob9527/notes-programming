//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class ArrayTests: XCTestCase {

    /**
     if you just want to add(kotlin plus) a single element, you still need to wrap it in an array
     - Throws:
     */
    func testImmutableArrayManipulation() throws {
        let arr1 = [1, 2, 3]
        let arr2 = arr1 + [4]
        XCTAssertEqual(arr1, [1, 2, 3])
        XCTAssertEqual(arr2, [1, 2, 3, 4])
    }

}

