package cn.staynoob.trap.kotlin.scripting.jsr223

import jdk.nashorn.api.scripting.ScriptObjectMirror
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import javax.script.ScriptEngine
import javax.script.ScriptEngineManager


class JavascriptEngineSpec {
    // Create a ScriptEngineManager
    private val manager = ScriptEngineManager()

    // Get the JavaScript engine
    private lateinit var engine: ScriptEngine

    @BeforeEach
    fun setUp() {
        // Check if the engine is available
        engine = manager.getEngineByName("JavaScript")
            ?: error("JavaScript engine not found")
    }

    @Test
    fun test100() {
        // Evaluate a simple JavaScript expression
        val result = engine.eval("40 + 2")
        println("Result of 40 + 2: $result")

        // Set a variable in the engine scope
        engine.put("name", "Alice")

        // Evaluate a script that uses the variable and returns a string
        val greeting = engine.eval("'Hello, ' + name + '!'") as String
        println(greeting)

        // Get a value from the script and use it in Java
        engine.eval("var message = 'JSR 223 is cool!';")
        val message = engine["message"] as String
        println("Message from script: $message")
    }

    @Test
    fun test200() {
        val res = engine.eval("""
            function fn() {
                return "foo"
            }
        """.trimIndent())
        println(res)
        println(engine["fn"])
        val fn = engine["fn"]!! as ScriptObjectMirror
        println(fn.call(null))
    }
}
