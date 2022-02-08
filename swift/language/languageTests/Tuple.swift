//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class TupleTests: XCTestCase {

    func testBasic() throws {
        let http404 = (404, "Not Found")
    }

    func testDestruct() throws {
        let http404 = (404, "Not Found")
        let (int, str) = http404
    }

    func testPlaceholder() throws {
        let foo = (0, 1, 2, 3)
        let (_, _, two, _) = foo
        XCTAssertEqual(two, 2)
    }

    func testAccessByIndex() throws {
        let foo = (0, 1, 2, 3)
        let two = foo.2
        XCTAssertEqual(two, 2)
    }

    func testNamedTuple() throws {
        let http404 = (code: 404, description: "Not Found")
        let code = http404.code
        XCTAssertEqual(code, 404)
    }
}
