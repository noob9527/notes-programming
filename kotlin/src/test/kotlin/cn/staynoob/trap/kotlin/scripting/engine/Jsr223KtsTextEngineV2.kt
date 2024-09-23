package cn.staynoob.trap.kotlin.scripting.engine

import org.slf4j.LoggerFactory
import java.lang.reflect.InvocationTargetException
import javax.script.ScriptEngine
import javax.script.ScriptEngineManager
import kotlin.jvm.internal.FunctionReference
import kotlin.reflect.KClass
import kotlin.reflect.jvm.jvmErasure

/**
 * while we explicit refer to the parameter, it introduces another problem:
 *
 * 1. kotlin is a statical typed language, which doesn't fit well in this situation,
 * to be concrete, if we want to define a function, we typically need to specify the type of the parameter.
 *   which usually involve to a `import` statement. e.g. `import com.cpvsn.core.svc.tpl.core.NdbTplData`
 *   if we rename/move this class, it breaks everything.
 */
class Jsr223KtsTextEngineV2(
    private val engine: ScriptEngine = ScriptEngineManager()
        .getEngineByExtension("kts"),
) {

    private val logger = LoggerFactory.getLogger(this::class.java)

    companion object {
        const val ENGINE_NAME = "JSR223_KTS_V2"
    }

    val name: String = ENGINE_NAME

    private val error_hint = """
      Script should be evaluated to a function reference, e.g. 
      ```
        fun fn(model: NdbTplData) = "foo"
        ::fn
      ```
    """.trimIndent()

    init {
        engine.eval("""println("init kotlin engine")""")
    }

    // see https://github.com/Kotlin/kotlin-script-examples/blob/master/jvm/jsr223/jsr223-simple/src/test/kotlin/org/jetbrains/kotlin/script/examples/jvm/jsr223/simple/test/simpleJsr223Test.kt
    fun process(template: String, model: Any): String {
        val tplWithImport = addDefaultImport(template, model)

        val res = try {
            engine.eval(tplWithImport)
        } catch (e: Exception) {
            throw ScriptEvalException(
                engineName = ENGINE_NAME,
                cause = e,
            )
        }

        val fn = res as? FunctionReference
            ?: throw ScriptEvalException(
                engineName = ENGINE_NAME,
                message = error_hint,
            )

        if (fn.returnType.jvmErasure != String::class) {
            throw ScriptEvalException(
                engineName = ENGINE_NAME,
                message = "Expect function to return a String, got ${fn.returnType.jvmErasure.qualifiedName}",
            )
        }
        val modelParam = fn.parameters.singleOrNull()
            ?: throw ScriptEvalException(
                engineName = ENGINE_NAME,
                message = "Require a function with single parameter",
            )

        if (modelParam.type.classifier != model::class) {
            throw ScriptEvalException(
                engineName = ENGINE_NAME,
                message = "function parameter type mismatch, expect '${(modelParam.type.classifier as? KClass<*>)?.qualifiedName}', got '${model::class.qualifiedName}'",
            )
        }

        val ret = try {
            fn.call(model)
        } catch (e: InvocationTargetException)  {
            throw ScriptRuntimeException(
                engineName = ENGINE_NAME,
                cause = e.targetException ?: e,
            )
        } catch (e: Exception) {
            throw ScriptRuntimeException(
                engineName = ENGINE_NAME,
                cause = e,
            )
        }

        return ret?.toString().orEmpty()
    }

    private fun addDefaultImport(script: String, model: Any): String {
        val importModelStmt = "import ${model::class.qualifiedName}"

        return if (importModelStmt in script) {
            script
        } else {
            """
            // the following import script is added programmatically by `com.cpvsn.core.svc.tpl.preprocess.Jsr223KtsTextEngineV2`
            import ${model::class.qualifiedName}


            $script
            """.trimIndent()
        }
    }

}
