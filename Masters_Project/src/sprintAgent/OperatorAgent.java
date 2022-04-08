package sprintAgent;

import jade.core.Agent;
import jade.core.behaviours.*;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import javax.swing.Timer;



public class OperatorAgent extends Agent {
	
	public int time;   
	public boolean status;
	public int chain;
	public double forceClose;
	private String[] target;
	
	private OperatorGui myGui;

	
	protected void setup() {
		
		Object[] args = getArguments();
		if (args != null && args.length > 0) {
			target = ((String) args[0]).split(":");		
			time = Integer.parseInt(target[1]);
			chain = Integer.parseInt(target[0]);
			status = false;
			
			if(target.length == 3) {
				forceClose = Double.parseDouble(target[2]);
			} else {
				forceClose = 0.05;
			}
		}
		
		// Create and show the GUI 
		myGui = new OperatorGui(this);
		myGui.showGui();

		// Register the book-selling service in the yellow pages
		DFAgentDescription dfd = new DFAgentDescription();
		dfd.setName(getAID());
		ServiceDescription sd = new ServiceDescription();
		switch (chain) {	
		case 1:
			sd.setType("operator-1");
			break;
			
		case 2:
			sd.setType("operator-2");
			break;
			
		case 3: 
			sd.setType("operator-3");
			break;
			
		case 4:
			sd.setType("operator-4");
			break;
		}
		sd.setName("JADE-operator");
		dfd.addServices(sd);
		try {
			DFService.register(this, dfd);
		}
		catch (FIPAException fe) {
			fe.printStackTrace();
		}

		// Add the behaviour serving queries from detailAgent
		addBehaviour(new OfferRequestsServer());

		// Add the behaviour serving orders
		addBehaviour(new PurchaseOrdersServer());
		
		//behaviour for repairs
		Behaviour loop = new TickerBehaviour( this, 1000 )
	      {
	         protected void onTick() {
	        		double randomnum = 0 + Math.random() * 100;
	    			if((status == false) && (randomnum <= forceClose)) {
	    				status = true;
	    				System.out.println(myAgent.getName()+" is currently being repaired. ");
	    				status = true;
	    				myGui.stat.setText("                   Repairing");
	    				myGui.stat.setBackground(new Color(249, 115, 0));
	    				int repairTime = (int) (10 + Math.random() * 20);
	    				addBehaviour( 
	    		                  new DelayBehaviour(myAgent, 1000*repairTime)
	    		                  {
	    		                     public void handleElapsedTimeout() { 
	    		                    	myGui.stat.setText("                   Free");
	    		                    	myGui.stat.setBackground(new Color(204, 255, 153));
	    		         				status = false;
	    		         				System.out.println(myAgent.getName()+" is now fixed.");
	    		         				}
	    		                  });
	    			}
	         }
	      };     
	   addBehaviour( loop );
	}

	// Put agent clean-up operations here
	protected void takeDown() {
		// Deregister from the yellow pages
		try {
			DFService.deregister(this);
		}
		catch (FIPAException fe) {
			fe.printStackTrace();
		}
		// Close the GUI
		myGui.dispose();
		// Printout a dismissal message
		System.out.println("Operator "+getAID().getName()+" terminating.");
	}

	/**
	   Inner class OfferRequestsServer.
	 */
	private class OfferRequestsServer extends CyclicBehaviour {
		public void action() {
			MessageTemplate mt = MessageTemplate.MatchPerformative(ACLMessage.CFP);
			
			ACLMessage msg = myAgent.receive(mt);
			if (msg != null) {
				// CFP Message received. Process it
				Scanner s = new Scanner(msg.getContent());
				String priorityDeal = s.next();
				ACLMessage reply = msg.createReply();
				if (status == false) {
					// The requested agent is available for work. Reply with time
					reply.setPerformative(ACLMessage.PROPOSE);
					reply.setContent(String.valueOf(time));
				}
				else {
					reply.setPerformative(ACLMessage.REFUSE);
					reply.setContent("not-available");
				}
				myAgent.send(reply);
			}
			else {
				block();
			}
			
		}
	}  // End of inner class OfferRequestsServer

	/**
	   Inner class PurchaseOrdersServer.
	 */
	public class PurchaseOrdersServer extends CyclicBehaviour {
		public void action() {
			MessageTemplate mt = MessageTemplate.MatchPerformative(ACLMessage.ACCEPT_PROPOSAL);
			ACLMessage msg = myAgent.receive(mt);
			if (msg != null) {
				// ACCEPT_PROPOSAL Message received. Process it
				String title = msg.getContent();
				ACLMessage reply = msg.createReply();

				reply.setPerformative(ACLMessage.INFORM);
				System.out.println(myAgent.getName()+" is working on "+msg.getSender().getName());
				status = true;
				myGui.stat.setText("                   Busy");
				myGui.stat.setBackground(new Color(255, 153, 153));
				addBehaviour( 
		                  new DelayBehaviour(myAgent, 1000*time)
		                  {
		                     public void handleElapsedTimeout() { 
		                    	myGui.stat.setText("                   Free");
		                    	myGui.stat.setBackground(new Color(204, 255, 153));
		         				status = false;
		         				System.out.println(myAgent.getName()+" finished "+msg.getSender().getName()+ ". Operation ¹"+ chain+".");
		         				}
		                  });
				myAgent.send(reply);
			}
			else {
				block();
			}
		}
	}  // End of inner class OfferRequestsServer
}
