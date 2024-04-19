package cn.staynoob.trap.java.ui.layout;

import javax.swing.*;
import java.awt.*;

public class GridLayoutDemo {

    public static void main(String[] args) {
        JFrame frame = new JFrame("GridLayout Demo");
        Container container = frame.getContentPane();
        container.setLayout(new GridLayout(2, 3));

        JButton button1 = new JButton("1");
        JButton button2 = new JButton("2");
        JButton button3 = new JButton("3");
        JButton button4 = new JButton("4");
        JButton button5 = new JButton("5");
        JButton button6 = new JButton("6");

        container.add(button1);
        container.add(button2);
        container.add(button3);
        container.add(button4);
        container.add(button5);
        container.add(button6);

        frame.setSize(600, 600);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

}
