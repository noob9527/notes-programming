package cn.staynoob.trap.kotlin.scripting.jsr223

import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Disabled
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test
import javax.script.ScriptEngineManager


class KotlinEngineSpec {

    // Create a ScriptEngineManager
    val manager = ScriptEngineManager()

    // Get the JavaScript engine
    val engine = manager.getEngineByExtension("kts")

    @BeforeEach
    fun setUp() {
        // Check if the engine is available
        if (engine == null) {
            error("kts engine not found")
        }
    }

    @Test
    @DisplayName("eval a simple kotlin expression")
    fun test100() {
        // Evaluate a simple kotlin expression
        val result = engine.eval("40 + 2")
        println("Result of 40 + 2: $result")
    }

    @Test
    @DisplayName("set/use variable")
    fun test200() {
        // Set a variable in the engine scope
        engine.put("name", "Alice")

        // Evaluate a script that uses the variable and returns a string
        val greeting = engine.eval(
            """
            "Hello, " + name + "!"
            """.trimIndent()
        ) as String
        println(greeting)
    }

    @Test
    @Disabled
    @DisplayName("get a value from the script and use it in jvm, it works in js engine")
    fun test300() {
        // somehow the following doesn't work
        // Get a value from the script and use it in Java
        engine.eval(
            """var message = "JSR 223 is cool!"; """.trimIndent()
        )
        val message = engine["message"] as String
        println("Message from script: $message")
    }
}
