//
//  languageTests.swift
//  languageTests
//
//  Created by 许炎 on 2022/1/24.
//

import XCTest
@testable import language

class languageTests: XCTestCase {

    override func setUpWithError() throws {
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }

    override func tearDownWithError() throws {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
    }

    func testExample() throws {
        let arr1 = [1,2,3]
        var arr2 = [1,2,3]
//        arr1.append(4)
        arr2.append(4)
        print(arr1)
        print(arr2)
        print("gotcha")
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
    }

    func testPerformanceExample() throws {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }

}
