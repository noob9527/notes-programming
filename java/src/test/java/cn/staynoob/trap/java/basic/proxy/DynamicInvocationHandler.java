package cn.staynoob.trap.java.basic.proxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;

public class DynamicInvocationHandler implements InvocationHandler {

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        System.out.println("Invoked method: " + method.getName());
        System.out.println("Arguments: ");
        for (Object arg : args) {
            System.out.println(arg);
        }

        return 42;
    }

}
