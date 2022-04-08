package sprintAgent;

import java.util.Random;

import jade.core.AID;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



class OperatorGui extends JFrame {	
	private OperatorAgent myAgent;
	
	public JTextField operation, time, stat;
	
	//Setting up GUI
	OperatorGui(OperatorAgent a) {
		super(a.getLocalName());
		myAgent = a;
		
		JPanel p = new JPanel();
		p.setLayout(new GridLayout(3, 2));
		p.add(new JLabel("Operation type:"));
		operation = new JTextField(13);
		p.add(operation);
		operation.setEditable(false);
		
		p.add(new JLabel("Time for completion (s) :"));
		time = new JTextField(13);
		p.add(time);
		time.setEditable(false);
		
		p.add(new JLabel("Status:"));
		stat = new JTextField(13);
		stat.setBackground(new Color(204, 255, 153));
		p.add(stat);
		stat.setEditable(false);
		
		getContentPane().add(p, BorderLayout.CENTER);
		operation.setText("                     " + String.valueOf(myAgent.chain));
		time.setText("                     " + String.valueOf(myAgent.time));
		stat.setText("                   Free");
		
		// Make the agent terminate when the user closes 
		// the GUI using the button on the upper right corner	
		addWindowListener(new	WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				myAgent.doDelete();
			}
		} );
		
		setResizable(false);
	}
	
	public void showGui() {
		pack();
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		int centerX = (int)screenSize.getWidth() / 2;
		int centerY = (int)screenSize.getHeight() / 2;
		setLocation(centerX - getWidth() / 2, centerY - getHeight() / 2);
		super.setVisible(true);
	}	
}
