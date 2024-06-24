package cn.staynoob.trap.kotlin.basic

import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test

/**
 * https://kotlinlang.org/docs/using-builders-with-builder-inference.html
 */
@DisplayName("Builder type inference")
class BuilderTypeInferenceSpec {
    @Test
    @DisplayName("build map example")
    fun test100() {
        val x = mapOf('b' to 2, 'c' to 3)

        val y = buildMap {
            put('a', 1)
            put('c', 0)
            putAll(x)
            put('d', 4)
        }

        println(y) // {a=1, c=3, b=2, d=4}
    }

    class ItemHolder<T> {
        private val items = mutableListOf<T>()

        fun addItem(x: T) {
            items.add(x)
        }

        fun getLastItem(): T? = items.lastOrNull()
    }

    fun <T> ItemHolder<T>.addAllItems(xs: List<T>) {
        xs.forEach { addItem(it) }
    }

    fun <T> itemHolderBuilder(builder: ItemHolder<T>.() -> Unit): ItemHolder<T> =
        ItemHolder<T>().apply(builder)

    @Test
    fun test200() {
        fun test(s: String) {
            val itemHolder1 = itemHolderBuilder { // Type of itemHolder1 is ItemHolder<String>
                addItem(s)
            }
            val itemHolder2 = itemHolderBuilder { // Type of itemHolder2 is ItemHolder<String>
                addAllItems(listOf(s))
            }
            val itemHolder3 = itemHolderBuilder { // Type of itemHolder3 is ItemHolder<String?>
                val lastItem: String? = getLastItem()
                // ...
            }
        }
    }
}
