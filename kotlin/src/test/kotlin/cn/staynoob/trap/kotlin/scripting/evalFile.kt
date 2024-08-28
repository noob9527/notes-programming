package cn.staynoob.trap.kotlin.scripting

import java.io.File
import kotlin.script.experimental.host.toScriptSource
import kotlin.script.experimental.jvm.dependenciesFromCurrentContext
import kotlin.script.experimental.jvm.jvm
import kotlin.script.experimental.jvmhost.BasicJvmScriptingHost
import kotlin.script.experimental.jvmhost.createJvmCompilationConfigurationFromTemplate

//fun evalFile(scriptFile: File) {
//    val compilationConfiguration = createJvmCompilationConfigurationFromTemplate<SimpleScript> {
//        jvm {
//            // configure dependencies for compilation, they should contain at least the script base class and
//            // its dependencies
//            // variant 1: try to extract current classpath and take only a path to the specified "script.jar"
//            dependenciesFromCurrentContext(
//                "script" /* script library jar name (exact or without a version) */
//            )
//            // variant 2: try to extract current classpath and use it for the compilation without filtering
////            dependenciesFromCurrentContext(wholeClasspath = true)
//            // variant 3: try to extract a classpath from a particular classloader (or Thread.contextClassLoader by default)
//            // filtering as in the variant 1 is supported too
////            dependenciesFromClassloader(classLoader = SimpleScript::class.java.classLoader, wholeClasspath = true)
//            // variant 4: explicit classpath
////            updateClasspath(listOf(File("/path/to/jar")))
//        }
//    }
//    return BasicJvmScriptingHost().eval(
//        scriptFile.toScriptSource(),
//        compilationConfiguration,
//        null,
//    )
//}
