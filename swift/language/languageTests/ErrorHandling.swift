//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class ErrorHandlingTests: XCTestCase {
    enum SampleError: Error {
        case foo(message: String)
        case bar
        case baz
    }

    func func1() throws {
        throw SampleError.foo(message: "gotcha")
    }

    func func2() {
    }

    func testBasic() throws {
        do {
            try func1()
            func2()
        } catch SampleError.foo(let message) {
            XCTAssertEqual(message, "gotcha")
        }
    }

}
