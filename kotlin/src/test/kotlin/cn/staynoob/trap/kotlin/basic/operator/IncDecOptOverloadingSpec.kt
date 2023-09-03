package cn.staynoob.trap.kotlin.basic.operator

import org.assertj.core.api.Assertions
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Test

/**
 * https://kotlinlang.org/docs/operator-overloading.html#increments-and-decrements
 */
@DisplayName("自增自减运算符重载")
class IncDecOptOverloadingSpec {

    /**
     * immutable
     */
    private data class Operand(val value: Int) {
        /**
         * Unlike C++, Kotlin inc operator doesn't mutate the object.
         * Instead, it mutates the reference which refer the the object.
         *
         * As the Document says:
         * "The inc() and dec() functions must return a value,
         * which will be assigned to the variable on which the ++ or -- operation was used.
         * They shouldn't mutate the object on which the inc or dec was invoked."
         */
        operator fun inc() = Operand(value + 1)
    }

    @Test
    @DisplayName("postfix form")
    fun test100() {
        var a = Operand(0)
        val refOfA = a

        // postfix form, the effect is:
        // - Store the initial value of a to a temporary storage a0.
        // - Assign the result of a0.inc() to a.
        // - Return a0 as the result of the expression.
        val res = a++
        Assertions.assertThat(a.value).isEqualTo(1)        // 'a' now refer to another increased operand
        Assertions.assertThat(a !== refOfA).isTrue()
        Assertions.assertThat(res.value).isEqualTo(0)

        Assertions.assertThat(res === a).isFalse()
        Assertions.assertThat(res === refOfA).isTrue()
    }

    @Test
    @DisplayName("prefix form")
    fun test200() {
        var a = Operand(0)
        val refOfA = a

        // prefix form, the effect is:
        // - Assign the result of a.inc() to a.
        // - Return the new value of a as a result of the expression.
        val res = ++a

        Assertions.assertThat(a.value).isEqualTo(1)        // 'a' now refer to another increased operand
        Assertions.assertThat(a !== refOfA).isTrue()
        Assertions.assertThat(res.value).isEqualTo(1)

        Assertions.assertThat(res === a).isTrue()
        Assertions.assertThat(res === refOfA).isFalse()
    }
}
