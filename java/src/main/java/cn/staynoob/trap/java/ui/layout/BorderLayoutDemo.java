package cn.staynoob.trap.java.ui.layout;

import javax.swing.*;
import java.awt.*;

public class BorderLayoutDemo {

    public static void main(String[] args) {
        JFrame frame = new JFrame("BorderLayout Demo");
        Container container = frame.getContentPane();

        JButton button1 = new JButton("north");
        JButton button2 = new JButton("south");
        JButton button3 = new JButton("west");
        JButton button4 = new JButton("east");
        JButton button5 = new JButton("center");

        container.add(button1, BorderLayout.NORTH);
        container.add(button2, BorderLayout.SOUTH);
        container.add(button3, BorderLayout.WEST);
        container.add(button4, BorderLayout.EAST);
        container.add(button5, BorderLayout.CENTER);

        frame.setSize(600, 600);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

}
