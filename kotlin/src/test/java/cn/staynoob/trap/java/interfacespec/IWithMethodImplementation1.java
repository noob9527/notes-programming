package cn.staynoob.trap.java.interfacespec;

public interface IWithMethodImplementation1 {
    default String foo() {
        return "foo1";
    }
}
