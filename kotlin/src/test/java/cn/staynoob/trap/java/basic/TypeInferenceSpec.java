package cn.staynoob.trap.java.basic;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

public class TypeInferenceSpec {

    static abstract class AbstractBase<T> {

        AbstractBase(T value) {
        }

    }

    // correct
    // AbstractBase<Integer> 中的 <Integer> 不能省略
    static class Sample1 extends AbstractBase<Integer> {

        Sample1() {
            super(10);
        }

    }

    // incorrect
//    static class Sample2 extends AbstractBase<>{
//        Sample2() {
//            super(10);
//        }
//    }
    static class Sample3<T> {

        Sample3(T value) {
        }

    }

    @Test
    @DisplayName("继承的 Constructor 不会推断类型")
    void test300() {
        AbstractBase<Integer> sample1 = new Sample1();
        // correct
        Sample3<Integer> sample3 = new Sample3<>(10);
    }

}
