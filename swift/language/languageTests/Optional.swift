//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class OptionalTests: XCTestCase {

    // check if a variable is optional type
    // https://stackoverflow.com/questions/32536420/determine-if-any-type-is-optional
    func isOptional(_ instance: Any) -> Bool {
        let mirror = Mirror(reflecting: instance)
        let style = mirror.displayStyle
        return style == .optional
    }

    func testIsOptional() {
        let optional1: Int? = 1
        let optional2: Optional<Int> = 1
        let optional3: Optional<Int> = Optional.none
        let nonOptional1: Int = 1

        XCTAssertTrue(isOptional(optional1))
        XCTAssertTrue(isOptional(optional2))
        XCTAssertTrue(isOptional(optional3))
        XCTAssertFalse(isOptional(nonOptional1))
    }

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
            XCTAssertFalse(isOptional(bar))
        }

        // as you may guess,
        // outside the scope, foo is still an optional int
        // and you can't access "bar" here
        // so you can't apply the so called "early return" technique here.
        // this is one of the reasons why they invented "guard" keyword
        XCTAssertTrue(isOptional(foo))
    }

    func testSafeUnwrapViaGuard() throws {
        let foo: Int? = 123

        guard let bar = foo else {
            XCTFail("won't go here")
        }

        XCTAssertTrue(isOptional(foo))
        XCTAssertFalse(isOptional(bar))
        XCTAssertEqual(bar, foo)
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
