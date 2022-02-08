//
// Created by 许炎 on 2022/2/7.
//

import XCTest

/**
 https://www.cocoaphile.com/posts/string-slicing-in-swift
 */
class StringTests: XCTestCase {

    /**
     #defect: overcomplicated string manipulation
     - Throws:
     */
    func testSlice() throws {
        let str = "0123456789"

        let str012 = String(str[str.startIndex..<str.index(str.startIndex, offsetBy: 3)])
        XCTAssertEqual(str012, "012")
        let str345 = String(str[str.firstIndex(of: "3")!...str.firstIndex(of: "5")!])
        XCTAssertEqual(str345, "345")
    }

}
