@file:Suppress("UNUSED_VARIABLE")

package cn.staynoob.trap.kotlin.basic.operator

import org.assertj.core.api.Assertions.assertThat
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test

/**
 * @see <a href="https://kotlinlang.org/docs/reference/operator-overloading.html">Operator Overloading</a>
 */
@DisplayName("操作符")
class OperatorOverloadingSpec {

    @Test
    @DisplayName("basic usage")
    internal fun test100() {
        data class Operand(val value: Int) {
            operator fun plus(other: Operand) = Operand(value + other.value)
        }

        operator fun Operand.minus(other: Operand) = Operand(value - other.value)
        assertThat(Operand(1) + Operand(1))
            .isEqualTo(Operand(2))
        assertThat(Operand(1) - Operand(1))
            .isEqualTo(Operand(0))
    }

    @Test
    @DisplayName("复合赋值运算符")
    internal fun test200() {
        /**
         * += 调用 plus 方法
         *
         * Operand1 是不可变对象
         */
        data class Operand1(val value: Int) {
            operator fun plus(other: Operand1) = Operand1(value + other.value)
        }

        // 可变引用
        var operand1 = Operand1(0)
        operand1 += Operand1(1)  // 修改引用
        assertThat(operand1).isEqualTo(Operand1(1))


        /**
         * += 调用 plusAssign 方法
         *
         * Operand2 是可变对象
         */
        data class Operand2(var value: Int) {
            operator fun plusAssign(other: Operand2) {
                value += other.value
            }
        }

        // 不可变引用
        val operand2 = Operand2(0)
        operand2 += Operand2(1) // 没有修改引用
        assertThat(operand2).isEqualTo(Operand2(1))

        /**
         * 不要同时声明plus与plusAssign方法
         */
        class Operand3(var value: Int) {
            operator fun plus(other: Operand3) = Operand3(value + other.value)
            operator fun plusAssign(other: Operand3) {
                value += other.value
            }
        }

        var op1 = Operand3(1)
        val op2 = Operand3(1)
        // correct
        op2 += Operand3(1)
        // incorrect: Assignment operators ambiguity. All these functions(plus, plusAssign) match.
//            op1 += Operand3(1)
    }

    @Test
    @DisplayName("Operator关键字会被继承")
    internal fun test300() {
        open class Parent(val value: Int) {
            open operator fun inc(): Parent = Parent(value + 1)
        }

        class Child(value: Int) : Parent(value) {
            // 该方法会作为 operator方法
            override fun inc(): Child {
                return Child(value + 2)
            }
        }

        var child = Child(0)
        assertThat((++child).value).isEqualTo(2)
    }


    @Nested
    @DisplayName("java compatible")
    inner class OperatorOverloadingSpec {
        /**
         * 由于java没有operator关键字，因此只要方法签名匹配约定就可以直接调用
         */
        @Test
        @DisplayName("调用java代码中的重载运算符")
        internal fun test1000() {
            operator fun Fixture.Operand.minus(other: Fixture.Operand) = subtract(other)
            assertThat(Fixture.Operand(1) + Fixture.Operand(1))
                .isEqualTo(2)
            assertThat(Fixture.Operand(1) - Fixture.Operand(1))
                .isEqualTo(0)
        }
    }
}
