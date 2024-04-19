package cn.staynoob.trap.java.ui.layout;

import javax.swing.*;
import java.awt.*;

public class FlowLayoutDemo {

    public static void main(String[] args) {
        JFrame frame = new JFrame("FlowLayout Demo");
        Container container = frame.getContentPane();

        JButton button1 = new JButton("OK");
        JButton button2 = new JButton("Open");
        JButton button3 = new JButton("Close");

        container.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));
        container.add(button1);
        container.add(button2);
        container.add(button3);

        frame.setSize(600, 600);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

}
