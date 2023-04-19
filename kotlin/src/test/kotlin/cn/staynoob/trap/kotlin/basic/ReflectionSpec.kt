package cn.staynoob.trap.kotlin.basic

import org.assertj.core.api.Assertions.assertThat
import org.assertj.core.api.Assertions.assertThatThrownBy
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import kotlin.reflect.KClass
import kotlin.reflect.KTypeProjection
import kotlin.reflect.full.createType
import kotlin.reflect.full.isSubtypeOf
import kotlin.reflect.full.starProjectedType
import kotlin.reflect.full.withNullability
import kotlin.reflect.jvm.jvmErasure

@DisplayName("反射")
class ReflectionSpec {
    @Test
    @DisplayName("获取kotlin类引用")
    internal fun test100() {
        val clazz1: Any = Int::class
        val clazz2: Any = (1).javaClass.kotlin
        assertThat(clazz1 is KClass<*>).isTrue()
        assertThat(clazz2 is KClass<*>).isTrue()
    }

    @Test
    @DisplayName("获取java类引用")
    internal fun test200() {
        val clazz1: Any = Int::class.java
        val clazz2: Any = (1).javaClass
        assertThat(clazz1 is Class<*>).isTrue()
        assertThat(clazz2 is Class<*>).isTrue()
    }

    @Nested
    @DisplayName("函数和属性是一等公民")
    inner class FirstClassSpec {
        @Test
        @DisplayName("引用函数")
        internal fun test100() {
            fun isOdd(x: Int) = x % 2 != 0
            class Foo(val foo: String = "foo") {
                fun isFoo(input: String) = input == foo
            }
            assertThat(::isOdd.invoke(1)).isTrue()
            assertThat((::isOdd)(2)).isFalse() //KFunction可以直接调用
            assertThat(Foo()::isFoo.invoke("foo")).isTrue()
            assertThat(Foo("bar")::isFoo.invoke("foo")).isFalse()
        }

        @Test
        @DisplayName("引用构造函数")
        internal fun test200() {
            class Foo
            assertThat(::Foo.invoke())
                    .isInstanceOf(Foo::class.java)
        }

        @Test
        @DisplayName("引用属性")
        internal fun test300() {
            assertThat(listOf("a", "ab", "abc").map(String::length))
                    .containsExactly(1, 2, 3)
        }

        @Test
        @DisplayName("绑定this的属性引用")
        internal fun test400() {
            val prop = "abc"::length
            assertThat(prop.get()).isEqualTo(3)
        }

        fun test500Fn(foo: String = "foo") = foo

        @Test
        @DisplayName("使用callBy应用默认参数")
        internal fun test500() {
            assertThat(this::test500Fn.callBy(mapOf()))
                    .isEqualTo("foo")
            assertThat(this::test500Fn.callBy(mapOf((this::test500Fn.parameters[0] to "bar"))))
                    .isEqualTo("bar")
        }

        @Test
        @DisplayName("截至kotlin1.15，反射local表达式并没有完全支持")
        internal fun test600() {
            fun fn() = Unit
            assertThatThrownBy { ::fn.annotations }
        }
    }

    @Nested
    @DisplayName("反射参数")
    inner class KParameterSpec {

        private fun test100Fn1(foo: String) = foo
        private fun test100Fn2(foo: String?) = foo
        private fun test100Fn3(foo: String = "foo") = foo
        @Test
        @DisplayName("isOptional")
        fun test100() {
            assertThat(::test100Fn1.parameters[0].isOptional).isFalse()
            assertThat(::test100Fn2.parameters[0].isOptional).isFalse()
            assertThat(::test100Fn3.parameters[0].isOptional).isTrue()
        }
    }

    /**
     * https://stackoverflow.com/questions/44203297/kotlins-reflection-unknown-type-parameter/44203910#44203910
     */
    @Nested
    @DisplayName("反射类型")
    inner class KTypeSpec {
        @Test
        @DisplayName("get type argument")
        fun test100() {
            val anyCollection = Collection::class.createType(listOf(
                KTypeProjection.invariant(Any::class.starProjectedType.withNullability(true))
            ))
            assertThat(anyCollection.arguments).hasSize(1)
            assertThat(anyCollection.arguments.singleOrNull()?.type?.jvmErasure).isEqualTo(Any::class)
        }

        @Test
        @DisplayName("get type argument, nested case")
        fun test120() {
            class Sample(
                val prop: List<List<Any>>
            )
            assertThat(Sample::prop.returnType.arguments).hasSize(1)
        }

        @Test
        @DisplayName("List<Int> should be sub type of List<Number>")
        fun test200() {
            val numberList = List::class.createType(listOf(
                KTypeProjection.invariant(Number::class.starProjectedType)
            ))
            val intList = List::class.createType(listOf(
                KTypeProjection.invariant(Int::class.starProjectedType)
            ))
            assertThat(intList.isSubtypeOf(numberList)).isTrue()
        }

        @Test
        @DisplayName("List<Int> should be sub type of Collection<Any?>")
        fun test300() {
            val anyCollection = Collection::class.createType(listOf(
                KTypeProjection.invariant(Any::class.starProjectedType.withNullability(true))
            ))
            val intList = List::class.createType(listOf(
                KTypeProjection.invariant(Int::class.starProjectedType)
            ))
            assertThat(intList.isSubtypeOf(anyCollection)).isTrue()
        }
    }

}
