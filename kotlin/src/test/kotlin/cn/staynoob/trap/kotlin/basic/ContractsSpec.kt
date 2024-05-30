package cn.staynoob.trap.kotlin.basic

import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test
import kotlin.contracts.ExperimentalContracts
import kotlin.contracts.InvocationKind
import kotlin.contracts.contract

/**
 * since kotlin 1.3
 *
 * https://kotlinlang.org/docs/whatsnew13.html#contracts
 */
class ContractsSpec {

    @OptIn(ExperimentalContracts::class)
    fun require(condition: Boolean) {
        // This is a syntax form which tells the compiler:
        // "if this function returns successfully, then the passed 'condition' is true"
        contract { returns() implies condition }
        if (!condition) throw IllegalArgumentException("Condition doesn't match")
    }

    @Test
    @DisplayName("Improving smartcasts analysis by declaring the relation between a function's call outcome and the passed arguments values")
    fun test100() {
        // s is smartcast to 'String' here, because otherwise
        // 'require' would have thrown an exception
        fun foo(s: String?) {
            require(s is String)
        }
    }

    @OptIn(ExperimentalContracts::class)
    fun synchronize(lock: Any?, block: () -> Unit) {
        // It tells the compiler:
        // "This function will invoke 'block' here and now, and exactly one time"
        contract { callsInPlace(block, InvocationKind.EXACTLY_ONCE) }
    }

    @Test
    @DisplayName("Improving the variable initialization analysis in the presence of higher-order functions")
    fun test200() {
        val x: Int
        synchronize(this) {
            x = 42 // Compiler knows that lambda passed to 'synchronize' is called
            // exactly once, so no reassignment is reported
        }
        println(x) // Compiler knows that lambda will be definitely called, performing
        // initialization, so 'x' is considered to be initialized here
    }
}
