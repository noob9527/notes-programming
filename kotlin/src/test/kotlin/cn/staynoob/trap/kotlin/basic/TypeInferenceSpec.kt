package cn.staynoob.trap.kotlin.basic

import org.assertj.core.api.Assertions.assertThat
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test
import kotlin.reflect.full.createInstance

class TypeInferenceSpec {

    interface Producer<T> {
        fun produce(): T
    }

    class StringProducer : Producer<String> {
        override fun produce(): String {
            return "42"
        }
    }

    inline fun <reified S : Producer<T>, T> underscoreTypeArgExample(): T {
        return S::class.createInstance().produce()
    }

    @Test
    @DisplayName("underscore type argument")
    fun test100() {
        val a = underscoreTypeArgExample<StringProducer, _>()
        assertThat(a).isEqualTo("42")
    }

    @Test
    @DisplayName("继承调用父类构造函数时，即使可以推断类型，也需要显式声名")
    fun test1000() {
        abstract class Base<T>(value: T)

        // correct
        class Sample1 : Base<Int>(10)

        // incorrect
//        class Sample2: Base(10)
//        class Sample2: Base<>(10)
//        class Sample2: Base<_>(10)
        // correct
        // 直接调用父类构造函数，可以省略类型参数
        class Sample3<T>(value: T)

        val sample3 = Sample3(10)
    }

}
