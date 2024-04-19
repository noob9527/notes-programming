package cn.staynoob.trap.java.ui;

import javax.swing.*;
import java.awt.*;

public class JLabelDemo {

    public static void main(String[] args) {
        JFrame frame = new JFrame("JFrame Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(600, 600);

        Container container = frame.getContentPane();
        container.setBackground(Color.CYAN);

        JLabel label = new JLabel("Hello World", JLabel.RIGHT);
        label.setBackground(Color.YELLOW);
        label.setHorizontalAlignment(JLabel.CENTER);
        label.setVerticalAlignment(JLabel.BOTTOM);
        frame.getContentPane().add(label);

        frame.setVisible(true);
    }

}
