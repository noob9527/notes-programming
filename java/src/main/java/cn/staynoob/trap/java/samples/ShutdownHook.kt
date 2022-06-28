package cn.staynoob.trap.java.samples

import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit

class ShutdownHook {
    companion object {

        private val executor = Executors.newSingleThreadExecutor()

        /**
         * gracefully handle SIGTERM, SIGINT
         * wait executor to finish its job
         */
        @JvmStatic
        fun main(args: Array<String>) {
            executor.execute {
                (1..100).forEach {
                    println(it)
                    Thread.sleep(100)
                }
            }

            Runtime.getRuntime().addShutdownHook(Thread {
                try {
                    println("execute shutdown handler")
                    // the following line is necessary for executor terminates
                    // when task is completed.
                    // otherwise executor.awaitTermination always return false.
                    executor.shutdown()

                    if (executor.awaitTermination(30, TimeUnit.SECONDS)) {
                        println("executor.awaitTermination = true")
                    } else {
                        println("executor.awaitTermination = false")
                        executor.shutdownNow()
                    }
                } catch (e: InterruptedException) {
                    e.printStackTrace()
                    println("thread is interrupted")
                    executor.shutdownNow()
                    Thread.currentThread().interrupt()
                }
            })
        }
    }
}
