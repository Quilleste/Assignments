package sprintAgent;

import java.util.Random;

import jade.core.AID;
import sprintAgent.DetailAgent.RequestPerformer;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



class DetailGui extends JFrame {	
	private DetailAgent myAgent;
	
	public JTextField operation, status;
	private JCheckBox check;
	
	DetailGui(DetailAgent bookBuyerAgent) {
		super(bookBuyerAgent.getLocalName());
		final Random random = new Random();
		myAgent = bookBuyerAgent;
		
		JPanel p = new JPanel();
		p.setLayout(new GridLayout(3, 2));
		p.add(new JLabel("Finished operation:"));
		operation = new JTextField(13);
		p.add(operation);
		operation.setEditable(false);
		
		p.add(new JLabel("Status:"));
		status = new JTextField(13);
		p.add(status);
		status.setEditable(false);
		
		p.add(new JLabel("Check for priority:"));
		check = new JCheckBox();
		p.add(check);
		
		
		getContentPane().add(p, BorderLayout.CENTER);
		
		JButton addButton = new JButton("Send Request");
		addButton.addActionListener( new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				try {
					myAgent.sentRequest(check.isSelected());
					addButton.setEnabled(false);
				}
				catch (Exception e) {
					JOptionPane.showMessageDialog(DetailGui.this, "Invalid values. "+e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE); 
				}
			}
		} );
		p = new JPanel();
		p.add(addButton);
		getContentPane().add(p, BorderLayout.SOUTH);
		
		
		operation.setText("                      0");
		status.setText("              Not started.");
		
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
