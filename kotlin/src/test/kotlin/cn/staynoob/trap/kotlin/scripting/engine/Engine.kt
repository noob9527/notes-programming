package cn.staynoob.trap.kotlin.scripting.engine

import kotlin.reflect.KFunction
import kotlin.script.experimental.api.ResultValue
import kotlin.script.experimental.api.ResultWithDiagnostics
import kotlin.script.experimental.api.ScriptDiagnostic
import kotlin.script.experimental.api.valueOrNull

object Engine {
    fun process(script: String, model: Any): String? {
        val res = evalScript(script, emptyMap())

        res.reports.forEach {
            if (it.severity > ScriptDiagnostic.Severity.DEBUG) {
                println(" : ${it.message}" + if (it.exception == null) "" else ": ${it.exception}")
            }
        }

        when (res) {
            is ResultWithDiagnostics.Failure -> {
                throw RuntimeException("Script evaluation failed: ${res.reports.joinToString()}")
            }

            is ResultWithDiagnostics.Success -> {
                val resultValue = res.valueOrNull()?.returnValue
                requireNotNull(resultValue)
                requireNotNull(resultValue as? ResultValue.Value)
                @Suppress("UNCHECKED_CAST") val fn =
                    ((resultValue as ResultValue.Value).value as KFunction<String?>)
                println(fn)
                val ret = fn.call(Model())
                println(ret)
                return ret
            }
        }
    }
}
