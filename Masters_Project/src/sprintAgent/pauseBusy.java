package sprintAgent;

import jade.core.behaviours.SimpleBehaviour;

public class pauseBusy extends SimpleBehaviour
{   
    int blockT = 0;
    int state = 0;
    
    public pauseBusy( int _blockT) {
		this.blockT = _blockT;
	}
    
    public void action() 
    {
        block(blockT);
        state++;
    }
    
    public  boolean done() {  return state > 1;  }
}