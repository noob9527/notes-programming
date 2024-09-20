package cn.staynoob.trap.kotlin.coroutine

import kotlinx.coroutines.coroutineScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test

/**
 * https://kotlinlang.org/docs/coroutines-basics.html
 */
class CoroutineBasic {

    /**
     * https://kotlinlang.org/docs/coroutines-basics.html#your-first-coroutine
     */
    @Test
    @DisplayName("basic case")
    fun test100() {
        runBlocking {
            launch { // launch a new coroutine and continue
                delay(100L) // non-blocking delay for 1 second (default time unit is ms)
                println("World!") // print after delay
            }
            println("Hello") // main coroutine continues while a previous one is delayed
        }
    }

    /**
     * https://kotlinlang.org/docs/coroutines-basics.html#extract-function-refactoring
     */
    @Test
    @DisplayName("a Suspend function example")
    fun test200() {
        // this is your first suspending function
        suspend fun doWorld1() {
            // Suspend function 'delay' should be called only
            // from a coroutine or another suspend function
            delay(100L)
            println("World!")
        }

        // incorrect
        //  Suspend function 'doWorld' should be called only from a coroutine or another suspend function
//        doWorld()

        runBlocking {
            launch { // launch a new coroutine and continue
                // correct
                doWorld1()
            }
            println("Hello") // main coroutine continues while a previous one is delayed
        }
    }


    /**
     * https://kotlinlang.org/docs/coroutines-basics.html#scope-builder
     */
    @Test
    @DisplayName("coroutineScope example")
    fun test300() {
        // incorrect
//        suspend fun doWorld2() {
//            // launch
//            launch {
//                delay(1000L)
//                println("World!")
//            }
//            println("Hello")
//        }

        // correct
        suspend fun doWorld2() = coroutineScope {
            // launch
            launch {
                delay(100L)
                println("World!")
            }
            println("Hello")
        }

        runBlocking {
            doWorld2()
        }
    }

    /**
     * https://kotlinlang.org/docs/coroutines-basics.html#scope-builder-and-concurrency
     */
    @Test
    @DisplayName("coroutineScope example 2")
    fun test400() {
        // Concurrently executes both sections
        suspend fun doWorld() = coroutineScope { // this: CoroutineScope
            launch {
                delay(200L)
                println("World 2")
            }
            launch {
                delay(100L)
                println("World 1")
            }
            println("Hello")
        }

        // Sequentially executes doWorld followed by "Done"
        runBlocking {
            doWorld()
            println("Done")
        }
    }

    /**
     * https://kotlinlang.org/docs/coroutines-basics.html#an-explicit-job
     */
    @Test
    @DisplayName("job example")
    fun test500() {
        runBlocking {
            // launch a new coroutine and keep a reference to its Job
            val job = launch {
                delay(100L)
                println("World!")
            }
            println("Hello")
            job.join() // wait until child coroutine completes
            println("Done")
        }
    }
}
