package cn.staynoob.trap.java.ui;

import javax.swing.*;
import java.awt.*;

public class JComboBoxDemo {

    public static void main(String[] args) {
        JFrame frame = new JFrame("JComboBox Demo");
        Container container = frame.getContentPane();

        String[] items = {
                "foo",
                "bar",
                "baz",
                "qux"
        };
        JComboBox<String> jComboBox = new JComboBox<>(items);
        container.add(jComboBox);

        frame.setSize(600, 600);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

}
