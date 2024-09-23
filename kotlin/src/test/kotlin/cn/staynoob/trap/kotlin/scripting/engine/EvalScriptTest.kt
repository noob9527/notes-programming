package cn.staynoob.trap.kotlin.scripting.engine

import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import org.junit.jupiter.api.Disabled
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test
import kotlin.system.measureTimeMillis

class EvalScriptTest {
    @Test
    fun test100() {
        val script = """
            fun resolve(model: Model): String {
                return model.prop1
            }
            ::resolve
        """.trimIndent()
        val res = Engine.process(
            script = script, model = Model()
        )
        println(res)
    }

    val jsr223KtsTextEngineV2 = Jsr223KtsTextEngineV2()

    @Test
    @Disabled
    @DisplayName("perf test")
    fun test200() {
        val script = """
            fun resolve(model: Model): String {
                return model.prop1
            }
            ::resolve
        """.trimIndent()
        val total = 100
        val model = Model()
        runBlocking {
            launch {
                val time = measureTimeMillis {
                    repeat(100) {
                        Engine.process(
                            script = script, model = Model()
                        )
                    }
                }
                println(": $time")
            }
            launch {
                val time = kotlin.time.measureTime {
                    repeat(total) {
                        jsr223KtsTextEngineV2.process(script, model = model)
                    }
                }
                println("${jsr223KtsTextEngineV2.name}: $time")
            }
        }
    }
}
