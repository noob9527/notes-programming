package cn.staynoob.trap.kotlin.scripting.engine

class ScriptRuntimeException(
    engineName: String,
    cause: Throwable? = null,
    message: String? = "[$engineName]: ${cause?.message ?: "script runtime exception"}",
) : RuntimeException(
    message,
    cause,
)
