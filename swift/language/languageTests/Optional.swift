//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class OptionalTests: XCTestCase {

    func testOptionalIsEnum() throws {
        let foo: Int? = Optional.some(123)
        let bar: Int? = Optional.none
        let baz: Optional<Int> = 123
        let qux: Optional<Int> = nil

        XCTAssertEqual(foo, 123)
        XCTAssertNil(bar)
        XCTAssertEqual(baz, 123)
        XCTAssertNil(qux)
    }

    func testBasic() throws {
        let foo: Int? = 123
        let bar: Int? = nil
        XCTAssertEqual(foo, 123)
        XCTAssertNil(bar)
    }

    func testForceUnwrap() throws {
        let foo: Int? = 123
        XCTAssertEqual(foo!, 123)
    }

    /**
     This code can be read as:
     “If the optional Int contains a value,
      set a new constant to the value contained in the optional.”
     */
    func testOptionalBinding() throws {
        let foo: Int? = 123

        if let bar = foo {
            // here bar is unwrapped
            XCTAssertNotNil(foo)
        }
    }

    /**
      When you use an implicitly unwrapped optional value,
      Swift first tries to use it as an ordinary optional value;
      if it can’t be used as an optional, Swift force-unwraps the value.
     */
    func testImplicitlyUnwrap() throws {
        let foo: Int! = 123
        let bar: Int = foo  // no need for an exclamation point
        let baz = foo
    }

    /**
        #defect: multiple question mark, multiple exclamation
        sometimes, you need multiple question mark
        or multiple exclamation to handle optional value
     */
    func testHigherOrderOptional() throws {
        let dict: [Int: String?] = [1: "foo"]
        let a = dict[1]

        XCTAssertEqual(a??.count, 3)

        let foo : String???? = "foo"
        XCTAssertEqual(foo????.count, 3)
        XCTAssertEqual(foo!!!!.count, 3)
    }

}
