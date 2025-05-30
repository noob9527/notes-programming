package cn.staynoob.trap.java.effectivejava.chapter05.item28;

import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.List;

/**
 * In summary, arrays and generics have very different type rules.
 * Arrays are covariant and reified; generics are invariant and erased.
 * As a consequence, arrays provide runtime type safety but not compile-time
 * type safety and vice versa for generics. Generally speaking,
 * arrays and generics don't mix well. If you find yourself mixing them and
 * getting compile-time errors or warnings, your first impulse should be to
 * place the arrays with lists.
 *
 * Intuitively speaking, a non-reifiable type is one whose
 * runtime representation contains less information than its compile-time representation. Because of erasure, the only parameterized types that are reifiable are
 * unbounded wildcard types such as List<?> and Map<?,?> (Item 26). It is legal,
 * though rarely useful, to create arrays of unbounded wildcard types.
 *
 * The prohibition on generic array creation can be annoying. It means, for example, that it’s not generally possible for a generic collection to return an array of its
 * element type (but see Item 33 for a partial solution). It also means that you get
 * confusing warnings when using varargs methods (Item 53) in combination with
 * generic types. This is because every time you invoke a varargs method, an array is
 * created to hold the varargs parameters. If the element type of this array is not reifiable, you get a warning.
 */
public class GenericArrayTest {
    @SuppressWarnings({"unused", "UnusedAssignment"})
    @Test
    @DisplayName("arrays are covariant")
    void test100() {
        Number[] arr1;
        Integer[] arr2 = new Integer[1];
        arr1 = arr2;
    }

    @Test
    void test200() {
        // Fails at runtime!
        Object[] objectArray = new Long[1];
        Assertions.assertThatThrownBy(() -> {
            objectArray[0] = "I don't fit in"; // Throws ArrayStoreException
        }).isInstanceOf(ArrayStoreException.class);
    }

    /**
     * Because of these fundamental differences, arrays and generics do not mix
     * well. For example, it is illegal to create an array of a generic type, a parameterized
     * type, or a type parameter. Therefore, none of these array creation expressions are
     * legal: new List<E>[], new List<String>[], new E[]. All will result in generic
     * array creation errors at compile time.
     */
    @Test
    void test300() {
//        new List<E>[];
//        new List<String>[];
//        new E[];
    }

    /**
     * Let’s pretend that line 1, which creates a generic array, is legal. Line 2 creates and
     * initializes a List<Integer> containing a single element. Line 3 stores the
     * List<String> array into an Object array variable, which is legal because arrays
     * are covariant. Line 4 stores the List<Integer> into the sole element of the
     * Object array, which succeeds because generics are implemented by erasure: the
     * runtime type of a List<Integer> instance is simply List, and the runtime type of
     * a List<String>[] instance is List[], so this assignment doesn’t generate an
     * ArrayStoreException. Now we’re in trouble. We’ve stored a List<Integer>
     * instance into an array that is declared to hold only List<String> instances. In
     * line 5, we retrieve the sole element from the sole list in this array. The compiler
     * automatically casts the retrieved element to String, but it’s an Integer, so we get
     * a ClassCastException at runtime. In order to prevent this from happening, line 1
     * (which creates a generic array) must generate a compile-time error.
     */
    @Test
    void test400() {
        // Why generic array creation is illegal - won't compile!
//        List<String>[] stringLists = new List<String>[1]; // (1)
//        List<Integer> intList = List.of(42); // (2)
//        Object[] objects = stringLists; // (3)
//        objects[0] = intList; // (4)
//        String s = stringLists[0].get(0); // (5)
    }

}
