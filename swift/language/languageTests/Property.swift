//
// Created by 许炎 on 2022/2/7.
//

import XCTest

/**
 https://docs.swift.org/swift-book/LanguageGuide/Properties.html
 */
class PropertyTests: XCTestCase {

    class Sample {
        var oldValueWillSet = 0
        var newValueWillSet = 0
        var oldValueDidSet = 0
        var newValueDidSet = 0

        var counter: Int = 0 {
            willSet {
                // here we have conventional name "newValue"
                oldValueWillSet = counter
                newValueWillSet = newValue
            }
            didSet {
                // here we have conventional name "oldValue"
                oldValueDidSet = oldValue
                newValueDidSet = counter
            }
        }
    }

    /**
     Property Observers
     - Throws:
     */
    func testPropertyObserver100() throws {
        let sample = Sample()
        sample.counter = 1
        sample.counter = 2
        XCTAssertEqual(sample.oldValueWillSet, 1)
        XCTAssertEqual(sample.newValueWillSet, 2)
        XCTAssertEqual(sample.oldValueDidSet, 1)
        XCTAssertEqual(sample.newValueDidSet, 2)
    }

    @propertyWrapper
    struct SampleWrapper {
        var value = 0

        // here we have conventional name "wrappedValue"
        var wrappedValue: Int {
            get {
                return value
            }
            set {
                // here we have conventional name "newValue"
                value = -newValue
            }
        }
    }

    struct SampleWrapperContainer {
        @SampleWrapper var height: Int
        @SampleWrapper var width: Int

        var heightWrapper: SampleWrapper {
            get {
                // here we have conventional rule
                // that is, we use underscore + property name
                // to access the property wrapper
                return _height
            }
            set {
                // here we have conventional rule
                // that is, we use underscore + property name
                // to access the property wrapper
                _height.wrappedValue = newValue
            }
        }
    }

    func testPropertyWrapper100() throws {
        let container = SampleWrapperContainer()
        container.height = 10
        XCTAssertEqual(container.heightWrapper.wrappedValue, -10)
        XCTAssertEqual(container.heightWrapper.value, -10)
    }

}

