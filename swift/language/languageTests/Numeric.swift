//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class NumericTests: XCTestCase {

    func testIntLiterals() throws {
        let binary = 0b0101
        let octal = 0o21
        let hexadecimal = 0x11

        let padded = 000123
        let million = 1_000_000
    }

    func testDoubleLiterals() throws {
        let decimal1 = 1.25e2
        let decimal2 = 0xFp2

        let padded = 000123.456
        let million = 1_000_000.000_0001
    }

}
