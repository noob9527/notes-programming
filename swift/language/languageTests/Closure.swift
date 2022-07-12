//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class ClosureTests: XCTestCase {

    /**
     "A closure is said to escape a function when the closure is passed as an argument
     to the function, but is called after the function returns.
     When you declare a function that takes a closure as one of its parameters,
     you can write @escaping before the parameter’s type to indicate that the
     closure is allowed to escape."
     - Throws:
     */
    func testEscaping() throws {
        func doSomething(_ callback: () -> Void) {
            callback()
        }

        func doSomethingAsync(_ callback: @escaping () -> Void) {
            DispatchQueue.main.async {
                callback()
            }
        }

        doSomething {
            print("do something")
        }

        doSomethingAsync {
            print("do something async")
        }
    }

}

