@file:Suppress("UNUSED_VARIABLE")

package cn.staynoob.trap.kotlin.basic.operator

import cn.staynoob.trap.kotlin.basic.operator.Fixture.Operand
import org.assertj.core.api.Assertions.assertThat
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test

@DisplayName("操作符")
class OperatorSpec {

    @Test
    @DisplayName("生成range")
    fun range() {
        val list: MutableList<Int> = ArrayList()

        list += 1..10
        assertThat(list).isEqualTo(mutableListOf(1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
        list.clear()

        list += 1 until 10
        assertThat(list).isEqualTo(mutableListOf(1, 2, 3, 4, 5, 6, 7, 8, 9))
        list.clear()

        list += 10 downTo 1
        assertThat(list).isEqualTo(mutableListOf(10, 9, 8, 7, 6, 5, 4, 3, 2, 1))
        list.clear()

        list += 10 downTo 1 step 2
        assertThat(list).isEqualTo(mutableListOf(10, 8, 6, 4, 2))
    }

    @Test
    @DisplayName("in操作符")
    fun inOperator() {
        assertThat(10 in 1..10).isTrue()
        assertThat(11 !in 1..10).isTrue()
    }

    @Test
    @DisplayName("对于位运算，没有特殊字符来表示，而只可用中缀方式调用命名函数")
    internal fun test300() {
        assertThat(2 shl 1).isEqualTo(4)
        assertThat(2 shr 1).isEqualTo(1)
        assertThat((-1).inv()).isEqualTo(0)
    }
}
