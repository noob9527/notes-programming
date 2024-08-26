package cn.staynoob.trap.kotlin.scripting

import org.junit.jupiter.api.Test
import kotlin.script.experimental.api.ResultWithDiagnostics
import kotlin.script.experimental.api.ScriptDiagnostic
import kotlin.script.experimental.api.valueOrNull

class EvalScriptTest {
    @Test
    fun test100() {
        val res = evalScript(script = """
            println("hello world")
            1+1
        """.trimIndent(), data = emptyMap())
        println(res)

        res.reports.forEach {
            if (it.severity > ScriptDiagnostic.Severity.DEBUG) {
                println(" : ${it.message}" + if (it.exception == null) "" else ": ${it.exception}")
            }
        }

        when(res) {
            is ResultWithDiagnostics.Failure -> {
                throw RuntimeException("Script evaluation failed: ${res.reports.joinToString()}")
            }
            is ResultWithDiagnostics.Success -> {
                println(res.valueOrNull())
                println(res.valueOrNull()?.returnValue)
            }
        }
    }
}
