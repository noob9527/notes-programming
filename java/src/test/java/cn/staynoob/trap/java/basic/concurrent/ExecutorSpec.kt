package cn.staynoob.trap.java.basic.concurrent

import org.assertj.core.api.Assertions
import org.assertj.core.api.Assertions.assertThat
import org.assertj.core.api.Assertions.assertThatThrownBy
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import java.util.concurrent.Callable
import java.util.concurrent.ExecutionException
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit
import java.util.concurrent.atomic.AtomicBoolean
import java.util.concurrent.atomic.AtomicReference

class ExecutorSpec {
    @Test
    @DisplayName("use ThreadFactory to create daemon threads")
    @Throws(InterruptedException::class)
    fun test100() {
        val executor = Executors.newSingleThreadExecutor { runnable: Runnable? ->
            val thread = Thread(runnable)
            thread.isDaemon = true
            thread
        }
        val isDaemon = AtomicBoolean(false)
        executor.submit { isDaemon.set(Thread.currentThread().isDaemon) }
        executor.awaitTermination(1, TimeUnit.SECONDS)
        Assertions.assertThat(isDaemon).isTrue
    }

    @Test
    @DisplayName("interrupt a thread won't effect subsequent task")
    @Throws(ExecutionException::class, InterruptedException::class)
    fun test200() {
        val executor = Executors.newSingleThreadExecutor()
        val thread = AtomicReference<Thread>()
        val callable = Callable<Boolean> {
            try {
                thread.set(Thread.currentThread())
                Thread.sleep(200)
                true
            } catch (e: InterruptedException) {
                false
            }
        }
        val future1 = executor.submit(callable)
        Thread.sleep(100)
        future1.cancel(true)
        val future2 = executor.submit(callable)
        Assertions.assertThat(future2.get()).isTrue()
        Assertions.assertThat(thread.get().state)
            .isEqualTo(Thread.State.WAITING)
    }

    @Nested
    inner class ExceptionHandler {
        @Test
        @DisplayName("execute method will print exception stacktrace")
        fun test100() {
            val executor = Executors.newSingleThreadExecutor()
            val executed = AtomicBoolean(false)
            val thread = Thread {
                executed.set(true)
                error("gotcha")
            }
            // the following line will print exception stacktrace
            executor.execute(thread)
            executor.shutdown()
            executor.awaitTermination(100, TimeUnit.MILLISECONDS)
            assertThat(executed.get()).isTrue
        }

        @Test
        @DisplayName("submit method will not print exception stacktrace")
        fun test200() {
            val executor = Executors.newSingleThreadExecutor()
            val executed = AtomicBoolean(false)
            val exception = Exception("gotcha")
            val thread = Thread {
                executed.set(true)
                throw exception
            }
            // the following line will silently ignore the exception
            val future = executor.submit(thread)
            executor.shutdown()
            executor.awaitTermination(100, TimeUnit.MILLISECONDS)
            assertThat(executed.get()).isTrue

            // catch exception when invoke future.get()
            assertThatThrownBy {
                future.get()
            }.isInstanceOf(ExecutionException::class.java)
                .hasCause(exception)
        }
    }

    @Nested
    inner class AwaitTerminationSpec {
        @Test
        @DisplayName("awaitTermination should return true")
        @Throws(InterruptedException::class)
        fun test100() {
            val executorService = Executors.newSingleThreadExecutor()
            val runnable = Runnable {
                try {
                    Thread.sleep(100)
                } catch (e: InterruptedException) {
                    e.printStackTrace()
                }
            }
            val future = executorService.submit(runnable)

            // the following line is necessary for executor terminates
            // when task is completed.
            // otherwise executor.awaitTermination always return false.
            executorService.shutdown()
            val terminated = executorService
                .awaitTermination(200, TimeUnit.MILLISECONDS)
            Assertions.assertThat(terminated).isTrue()
            Assertions.assertThat(future).isDone()
        }

        @Test
        @DisplayName("awaitTermination should return false")
        @Throws(InterruptedException::class)
        fun test200() {
            val executorService = Executors.newSingleThreadExecutor()
            val runnable = Runnable {
                try {
                    Thread.sleep(200)
                } catch (e: InterruptedException) {
                    e.printStackTrace()
                }
            }
            executorService.submit(runnable)
            executorService.shutdown()
            val terminated = executorService
                .awaitTermination(100, TimeUnit.MILLISECONDS)
            Assertions.assertThat(terminated).isFalse()
        }
    }
}
