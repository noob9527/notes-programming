package cn.staynoob.trap.java.ui;

import javax.swing.*;
import java.awt.*;

public class JPanelDemo {

    public static void main(String[] args) {
        JFrame frame = new JFrame("JFrame Demo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(600, 600);
        frame.setVisible(true);

        Container container = frame.getContentPane();
        container.setBackground(Color.CYAN);

        JPanel panel = new JPanel();
        panel.setSize(300, 300);
        panel.setBackground(Color.YELLOW);

        container.add(panel, BorderLayout.SOUTH);
    }

}
