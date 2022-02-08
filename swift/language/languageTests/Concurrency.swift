//
// Created by 许炎 on 2022/2/7.
//

import XCTest

class ConcurrencyTests: XCTestCase {

    func testBasic() async throws {
        let before = Int(Date().timeIntervalSince1970)
        try await Task.sleep(nanoseconds: 2 * 1_000_000_000) //2 seconds
        let after = Int(Date().timeIntervalSince1970)
        XCTAssertEqual(after - before, 2)
    }


    func testSerialExecution() async throws {
        let before = Int(Date().timeIntervalSince1970)
        try await Task.sleep(nanoseconds: 2 * 1_000_000_000)
        try await Task.sleep(nanoseconds: 2 * 1_000_000_000)
        try await Task.sleep(nanoseconds: 2 * 1_000_000_000)
        let after = Int(Date().timeIntervalSince1970)
        XCTAssertEqual(after - before, 2 * 3)
    }

    // async-let
    func testParallelExecution() async throws {
        let before = Int(Date().timeIntervalSince1970);
        async let t1 = Task.sleep(nanoseconds: 2 * 1_000_000_000)
        async let t2 = Task.sleep(nanoseconds: 2 * 1_000_000_000)
        async let t3 = Task.sleep(nanoseconds: 2 * 1_000_000_000)
        try await [t1, t2, t3]
        let after = Int(Date().timeIntervalSince1970)
        XCTAssertEqual(after - before, 2)
    }

    actor BoolRef {
        var value: Bool = false

        func setExecuted() {
            value = true
        }
    }

    func testCallAsyncFuncFromSyncContext() async  throws {
        let before = Int(Date().timeIntervalSince1970)
        let ref = BoolRef()
        let task = Task {
            do {
                try await Task.sleep(nanoseconds: 2 * 1_000_000_000) //2 seconds
                let after = Int(Date().timeIntervalSince1970)
                XCTAssertEqual(after - before, 2)
                await ref.setExecuted()
            }
        }
        let after = Int(Date().timeIntervalSince1970)
        XCTAssertEqual(after - before, 0)

        try await task.result // wait task finished

        let executed = await ref.value
        XCTAssertEqual(executed, true)
    }
}
