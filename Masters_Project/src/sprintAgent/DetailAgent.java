package sprintAgent;

import jade.core.Agent;

import java.awt.Color;

import jade.core.AID;
import jade.core.behaviours.*;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;

public class DetailAgent extends Agent {
	// The list of known operators
	private AID[] operatorAgents;
	
	private DetailGui myGui;
	public boolean priority;
	public boolean done_status;
	private int status;
	
	public boolean[] reqst = new boolean[2];

	// agent initializations here
	protected void setup() {
		
		myGui = new DetailGui(this);
		myGui.showGui();
		status = 0;
		done_status = false;
		
		reqst[0] = false;
			// Add a TickerBehaviour that schedules a request to operators every 0.5 s
		addBehaviour(new TickerBehaviour(this, 500) {
				protected void onTick() {
					if(reqst[0]) {
					DFAgentDescription template = new DFAgentDescription();
					ServiceDescription sd = new ServiceDescription();
					switch(status) {
					case 0:
						sd.setType("operator-1");
						template.addServices(sd);
						try {
							DFAgentDescription[] result = DFService.search(myAgent, template); 
							operatorAgents = new AID[result.length];
							for (int i = 0; i < result.length; ++i) {
								operatorAgents[i] = result[i].getName();
							}
						}
						catch (FIPAException fe) {
							fe.printStackTrace();
						}
						break;
					case 1: 
						sd.setType("operator-2");
						template.addServices(sd);
						try {
							DFAgentDescription[] result = DFService.search(myAgent, template); 
							operatorAgents = new AID[result.length];
							for (int i = 0; i < result.length; ++i) {
								operatorAgents[i] = result[i].getName();
							}
						}
						catch (FIPAException fe) {
							fe.printStackTrace();
						}
						break;
					case 2:
						sd.setType("operator-3");
						template.addServices(sd);
						try {
							DFAgentDescription[] result = DFService.search(myAgent, template); 
							operatorAgents = new AID[result.length];
							for (int i = 0; i < result.length; ++i) {
								operatorAgents[i] = result[i].getName();
							}
						}
						catch (FIPAException fe) {
							fe.printStackTrace();
						}
						break;
					case 3:
						sd.setType("operator-4");
						template.addServices(sd);
						try {
							DFAgentDescription[] result = DFService.search(myAgent, template); 
							operatorAgents = new AID[result.length];
							for (int i = 0; i < result.length; ++i) {
								operatorAgents[i] = result[i].getName();
							}
						}
						catch (FIPAException fe) {
							fe.printStackTrace();
						}
						break;
					}
					// Perform the request
					myAgent.addBehaviour(new RequestPerformer());
					}
				}
			} );
	}

	//agent clean-up operations
	protected void takeDown() {
		// Printout a dismissal message
		System.out.println("Detail "+getAID().getName()+" is done.");
		myGui.dispose();
	}
	
	/**
	   Inner class RequestPerformer.
	 */
	public class RequestPerformer extends Behaviour {
		private AID bestOffer; // The agent who provides the best offer 
		private int bestTime = 0;  // The best offered price
		private int repliesCnt = 0; // The counter of replies from seller agents
		private MessageTemplate mt; // The template to receive replies
		private int step = 0;

		public void action() {
			switch (step) {
			case 0:
				// Send the cfp to all operators
				ACLMessage cfp = new ACLMessage(ACLMessage.CFP);
				for (int i = 0; i < operatorAgents.length; ++i) {
					cfp.addReceiver(operatorAgents[i]);
				} 
				cfp.setContent(String.valueOf(reqst[1]));
				cfp.setConversationId("operation");
				cfp.setReplyWith("cfp"+System.currentTimeMillis()); // Unique value
				myAgent.send(cfp);
				// Prepare the template to get proposals
				mt = MessageTemplate.and(MessageTemplate.MatchConversationId("operation"),
						MessageTemplate.MatchInReplyTo(cfp.getReplyWith()));
				step = 1;
				break;
			case 1:
				// Receive all proposals/refusals from agents
				ACLMessage reply = myAgent.receive(mt);
				if (reply != null) {
					// Reply received
					if (reply.getPerformative() == ACLMessage.PROPOSE) {
						// This is an offer 
						int time = Integer.parseInt(reply.getContent());
						if (bestOffer == null || time < bestTime) {
							// This is the best offer at present
							bestTime = time;
							bestOffer = reply.getSender();
						}
					}
					repliesCnt++;
					if (repliesCnt >= operatorAgents.length) {
						// We received all replies
						step = 2; 
					}
				} else {
					block();
				}
				break;
			case 2:
				// Send the request to the operator that provided the best offer
				ACLMessage order = new ACLMessage(ACLMessage.ACCEPT_PROPOSAL);
				order.addReceiver(bestOffer);
				order.setContent(String.valueOf(reqst[1]));
				order.setConversationId("operation");
				order.setReplyWith("order"+System.currentTimeMillis());
				myAgent.send(order);
				// Prepare the template
				mt = MessageTemplate.and(MessageTemplate.MatchConversationId("operation"),
						MessageTemplate.MatchInReplyTo(order.getReplyWith()));
				step = 3;
				break;
			case 3:      
				// Receive the request reply
				reply = myAgent.receive(mt);
				if (reply != null) {
					//reply received
					if (reply.getPerformative() == ACLMessage.INFORM) {
						// Found agent to work on detail
						System.out.println("Successfully found agent for work: "+reply.getSender().getName());
					}
					reqst[0] = false;
					myGui.status.setText("              In progress.");
            		myGui.status.setBackground(new Color(255, 255, 102));
					
					addBehaviour( 
			                  new DelayBehaviour(myAgent, bestTime*1000)
			                  {
			                     public void handleElapsedTimeout() { 
			         				System.out.println(myAgent.getName()+" was finished by "+reply.getSender().getName()+ ". Operation ¹"+ (status+1) +".");
			         				status++;
			         				myGui.operation.setText("                      " + String.valueOf(status));
			         				myGui.status.setText("              Waiting.");
			         				myGui.status.setBackground(new Color(204, 255, 153));
			         				reqst[0] = true;
			         				if(status == 4) {
			    						myAgent.doDelete();
			    						reqst[0] = false;	
			    					}
			                     }
			                  });
					step = 4;
					
				}
				else {
					block();
				}
				break;
			}        
		}

		public boolean done() {
			if (step == 2 && bestOffer == null) {
			}
			return ((step == 2 && bestOffer == null) || step == 4);
		}
	}  // End of inner class RequestPerformer


public void sentRequest(boolean check) {
	addBehaviour(new OneShotBehaviour() {
		public void action() {
			reqst[0] = true;
			reqst[1] = check;
		}
	} );
}
}
