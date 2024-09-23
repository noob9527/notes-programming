package cn.staynoob.trap.kotlin.scripting.engine


class ScriptEvalException(
    engineName: String,
    cause: Throwable? = null,
    message: String? = "[$engineName]: ${cause?.message ?: "script eval exception"}",
) : RuntimeException(
    message, cause,
)
