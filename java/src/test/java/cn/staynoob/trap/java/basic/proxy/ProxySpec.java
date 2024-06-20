package cn.staynoob.trap.java.basic.proxy;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Proxy;
import java.util.Map;

import static org.assertj.core.api.AssertionsForClassTypes.assertThatThrownBy;

public class ProxySpec {

    @Test
    @DisplayName("basic case")
    void test100() {
        Map proxy = (Map) Proxy.newProxyInstance(
                this.getClass().getClassLoader(),
                // need to be interfaces
                new Class[]{Map.class},
                new DynamicInvocationHandler()
        );
        proxy.put("hello", "world");
    }

    static class Sample {

        public int foo() {
            return 42;
        }

    }

    @Test
    @DisplayName("can only proxy interface")
    void test200() {
        assertThatThrownBy(() -> {
            Sample proxy = (Sample) Proxy.newProxyInstance(
                    this.getClass().getClassLoader(),
                    // need to be interfaces
                    new Class[]{Sample.class},
                    new DynamicInvocationHandler()
            );
        }).hasMessageContaining("is not an interface");
    }

}
