package cn.staynoob.trap.kotlin.designpattern.producer

/**
 * recursive generic pattern
 * https://stackoverflow.com/questions/29565043/how-to-specify-own-type-as-return-type-in-kotlin
 */
interface Producer<T: Producer<T>> {
    fun produce(): T
}

class ProducerImpl: Producer<ProducerImpl> {
    override fun produce(): ProducerImpl {
        TODO("not implemented")
    }
}
