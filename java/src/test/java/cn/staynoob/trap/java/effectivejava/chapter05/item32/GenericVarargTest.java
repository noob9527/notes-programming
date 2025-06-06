package cn.staynoob.trap.java.effectivejava.chapter05.item32;

import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

/**
 * Varargs methods (Item 53) and generics were both added to the platform in Java 5,
 * so you might expect them to interact gracefully; sadly, they do not. The purpose of
 * varargs is to allow clients to pass a variable number of arguments to a method, but
 * it is a leaky abstraction: when you invoke a varargs method, an array is created to
 * hold the varargs parameters; that array, which should be an implementation detail,
 * is visible. As a consequence, you get confusing compiler warnings when varargs
 * parameters have generic or parameterized types.
 */
public class GenericVarargTest {

    /**
     * This method has no visible casts yet throws a ClassCastException when invoked
     * with one or more arguments. Its last line has an invisible cast that is generated by
     * the compiler. This cast fails, demonstrating that type safety has been compromised,
     * and it is unsafe to store a value in a generic varargs array parameter.
     * @param stringLists
     */
    // Mixing generics and varargs can violate type safety!
    static void dangerous(List<String>... stringLists) {
        List<Integer> intList = Arrays.asList(42);
        Object[] objects = stringLists;
        objects[0] = intList; // Heap pollution
        String s = stringLists[0].get(0); // ClassCastException
    }

    @Test
    void test100() {
        List<String> list = new ArrayList<>();
        list.add("Hello");
        Assertions.assertThatThrownBy(() -> {
            dangerous(list);
        }).isInstanceOf(ClassCastException.class);
    }

    // UNSAFE - Exposes a reference to its generic parameter array!
    static <T> T[] toArray(T... args) {
        return args;
    }

    /**
     * This method is not, in and of itself, dangerous and would not generate a warning
     * except that it invokes the toArray method, which has a generic varargs parameter.
     * When compiling this method, the compiler generates code to create a varargs
     * parameter array in which to pass two T instances to toArray. This code allocates
     * an array of type Object[], which is the most specific type that is guaranteed to
     * hold these instances, no matter what types of objects are passed to pickTwo at the
     * call site. The toArray method simply returns this array to pickTwo, which in turn
     * returns it to its caller, so pickTwo will always return an array of type Object[].
     */
    static <T> T[] pickTwo(T a, T b, T c) {
        switch(ThreadLocalRandom.current().nextInt(3)) {
            case 0: return toArray(a, b);
            case 1: return toArray(a, c);
            case 2: return toArray(b, c);
        }
        throw new AssertionError(); // Can't get here
    }

    @Test
    void test200() {
        Assertions.assertThatThrownBy(() -> {
            String[] attributes = pickTwo("Good", "Fast", "Cheap");
        }).isInstanceOf(ClassCastException.class);
    }

}
