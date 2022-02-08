//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class StructTests: XCTestCase {

    struct Struct {
        var name: String
    }

    class Class {
        var name: String

        init(name: String) {
            self.name = name
        }
    }

    /**
     Classes are reference type,
     Structs are value type objects
     - Throws:
     */
    func testStruct() throws {
        let struct1 = Struct(name: "foo")
        var struct2 = struct1
        struct2.name = "bar"
        XCTAssertEqual(struct1.name, "foo")
        XCTAssertEqual(struct2.name, "bar")
    }

    func testClass() throws {
        let class1 = Class(name: "foo")
        let class2 = class1
        class2.name = "bar"
        XCTAssertEqual(class1.name, "bar")
        XCTAssertEqual(class2.name, "bar")
    }

}
