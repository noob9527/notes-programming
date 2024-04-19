package cn.staynoob.trap.java.ui;

import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.event.*;

public class JButtonDemo extends WindowAdapter {

    public static void main(String[] args) {
        JButtonDemo demo = new JButtonDemo();
        demo.go();
    }

    public void go() {
        JFrame frame = new JFrame("JButton Demo");

        JCheckBox checkBox1 = new JCheckBox("check box1");
        JCheckBox checkBox2 = new JCheckBox("check box2");
        JCheckBox checkBox3 = new JCheckBox("check box3");

        JCheckBox checkBox4 = new JCheckBox("check box1");
        JCheckBox checkBox5 = new JCheckBox("check box2");
        JCheckBox checkBox6 = new JCheckBox("check box3");

        ItemListener itemListener = new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                JCheckBox cb = (JCheckBox) e.getSource();
                System.out.println(cb.getText() + cb.isSelected() + e.getStateChange());
            }
        };
        checkBox1.addItemListener(itemListener);
        checkBox2.addItemListener(itemListener);
        checkBox3.addItemListener(itemListener);

        ButtonGroup group1 = new ButtonGroup();
        group1.add(checkBox1);
        group1.add(checkBox2);
        group1.add(checkBox3);

        JRadioButton radioButton1 = new JRadioButton("radio 1");
        JRadioButton radioButton2 = new JRadioButton("radio 2");
        JRadioButton radioButton3 = new JRadioButton("radio 3");

        ActionListener actionListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JRadioButton cb = (JRadioButton) e.getSource();
                System.out.println(cb.getText() + cb.isSelected() + e.getActionCommand());
            }
        };
        radioButton1.addActionListener(actionListener);
        radioButton2.addActionListener(actionListener);
        radioButton3.addActionListener(actionListener);

        ButtonGroup group2 = new ButtonGroup();
        group2.add(radioButton1);
        group2.add(radioButton2);
        group2.add(radioButton3);

        JToggleButton toggleButton1 = new JToggleButton("toggle 1");
        JToggleButton toggleButton2 = new JToggleButton("toggle 2");
        JToggleButton toggleButton3 = new JToggleButton("toggle 3");
        ButtonGroup group3 = new ButtonGroup();
        group3.add(toggleButton1);
        group3.add(toggleButton2);
        group3.add(toggleButton3);

        JPanel panel1 = new JPanel();
        JPanel panel2 = new JPanel();
        JPanel panel3 = new JPanel();
        JPanel panel4 = new JPanel();

        panel1.add(checkBox1);
        panel1.add(checkBox2);
        panel1.add(checkBox3);
        panel2.add(checkBox4);
        panel2.add(checkBox5);
        panel2.add(checkBox6);
        Border etchedBorder = BorderFactory.createEtchedBorder();
        panel1.setBorder(BorderFactory.createTitledBorder(
                etchedBorder, "check box with group"
        ));
        panel2.setBorder(BorderFactory.createTitledBorder(
                etchedBorder, "check box without group"
        ));

        panel3.add(radioButton1);
        panel3.add(radioButton2);
        panel3.add(radioButton3);
        panel3.setBorder(BorderFactory.createTitledBorder(
                etchedBorder, "radio"
        ));

        panel4.add(toggleButton1);
        panel4.add(toggleButton2);
        panel4.add(toggleButton3);
        panel4.setBorder(BorderFactory.createTitledBorder(
                etchedBorder, "toggle"
        ));

        frame.getContentPane().setLayout(new GridLayout(0, 1));
        frame.getContentPane().add(panel1);
        frame.getContentPane().add(panel2);
        frame.getContentPane().add(panel3);
        frame.getContentPane().add(panel4);

        frame.pack();
        frame.setVisible(true);
        frame.addWindowListener(this);
    }

    @Override
    public void windowClosing(WindowEvent e) {
        System.exit(0);
    }

}
