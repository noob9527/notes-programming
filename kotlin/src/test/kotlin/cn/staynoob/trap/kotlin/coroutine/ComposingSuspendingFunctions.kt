package cn.staynoob.trap.kotlin.coroutine

import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test
import kotlin.system.measureTimeMillis

/**
 * https://kotlinlang.org/docs/composing-suspending-functions.html
 */
class ComposingSuspendingFunctions {

    suspend fun doSomethingUsefulOne(): Int {
        delay(100L) // pretend we are doing something useful here
        return 13
    }

    suspend fun doSomethingUsefulTwo(): Int {
        delay(100L) // pretend we are doing something useful here, too
        return 29
    }

    @Test
    @DisplayName("sequential")
    fun test100() {
        runBlocking {
            val time = measureTimeMillis {
                val one = doSomethingUsefulOne()
                val two = doSomethingUsefulTwo()
                println("The answer is ${one + two}")
            }
            println("Completed in $time ms")
        }
    }

    @Test
    @DisplayName("concurrent")
    fun test200() {
        runBlocking {
            val time = measureTimeMillis {
                val one = async { doSomethingUsefulOne() }
                val two = async { doSomethingUsefulTwo() }
                println("The answer is ${one.await() + two.await()}")
            }
            println("Completed in $time ms")
        }
    }

    /**
     * Conceptually, async is just like launch. It starts a separate coroutine
     * which is a light-weight thread that works concurrently with all the
     * other coroutines. The difference is that launch returns a Job and does
     * not carry any resulting value, while async returns a Deferred — a
     * light-weight non-blocking future that represents a promise to provide
     * a result later. You can use .await() on a deferred value to get its
     * eventual result, but Deferred is also a Job, so you can cancel it if needed.
     *
     * https://kotlinlang.org/docs/composing-suspending-functions.html#concurrent-using-async
     */
    @Test
    @DisplayName("launch vs async")
    fun test300() {
        runBlocking {
            val time = measureTimeMillis {
                val job = launch {
                    doSomethingUsefulOne()
                }
                val deferred = async {
                    doSomethingUsefulTwo()
                }
                job.join()
                deferred.await()
            }
            println("Completed in $time ms")
        }
    }
}
