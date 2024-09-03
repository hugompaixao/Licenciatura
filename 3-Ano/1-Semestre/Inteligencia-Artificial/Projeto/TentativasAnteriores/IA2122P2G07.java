package screenpac.controllers;

import screenpac.controllers.AgentInterface;
import screenpac.extract.Constants;
import screenpac.model.*;
import screenpac.features.NearestPillDistance;
import screenpac.features.Utilities;

import java.awt.*;
import java.util.ArrayList;
import java.util.Stack;

/**
 * Primeira tentativa na resolução do pacmana
 */
public class IA2122P2G07 implements AgentInterface, Constants {
    NearestPillDistance pill;

    public IA2122P2G07() {
        pill = new NearestPillDistance();
    }


    public Node closestKillerGhost(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;

        for (GhostState var : gs.getGhosts())
            if (!var.edible() && !var.returning() && gs.getMaze().dist(var.current, node) < minDist) {
                minDist = gs.getMaze().dist(var.current, node);
                closest = var.current;
            }
        if (closest != null)
            closest.col = Color.red;

        return closest;
    }
    
    public Node closestEdibleGhost(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        
        for (GhostState var : gs.getGhosts()) {
            if (var.edible() && gs.getMaze().dist(var.current, node) < minDist) {
                minDist = gs.getMaze().dist(var.current, node);
                closest = var.current;
            }
        }

        closest.col = Color.cyan;
     
        return closest;
    }

  
    public Node closestPower(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        
        for (Node var : gs.getMaze().getPowers()) 
            if (gs.getMaze().dist(node, var) < minDist) {
                minDist = gs.getMaze().dist(node, var);
                closest = var;
            }
        
        closest.col = Color.cyan;
        
        return closest;
    }

  
    public boolean areEdible(GameStateInterface gs) {
        boolean edible = false;
        
        for (GhostState var : gs.getGhosts())
            if (var.edible()) {
                edible = true;
                break;
            }
        
        return edible;
    }

   
    public boolean areAllEdible(GameStateInterface gs ) {
    	boolean all = true;
    	
    	for (GhostState var : gs.getGhosts())
    		if (!var.edible()) {
    			all = false;
    			break;
    		}
    	
    	return all;
    }
    

    public Node adjFarthestFromKiller(GameStateInterface gs, Node n, Node k) {
    	Node farthest = null;
    	int maxDist = Integer.MIN_VALUE;
    	
    	for (Node var : n.adj) {
    		if (gs.getMaze().dist(var, k) > maxDist) {
    			maxDist = gs.getMaze().dist(var, k);
    			farthest = var;
    		} else if (gs.getMaze().dist(var, k) == maxDist) {
    			if (gs.getMaze().getPowers().contains(var))
    				farthest = var;
    			else if (gs.getMaze().getPills().contains(var)) 
    				farthest = var;
    		}
    	}
    	
    	farthest.col = Color.white;
    	
    	return farthest;
    }
    
    
    public int action(GameStateInterface gs) {
        gs = gs.copy();
        Node current = gs.getPacman().current;
        Node target = null;
        Node killer = null;
        if(!areAllEdible(gs))
        	killer = closestKillerGhost(gs, current);
        Node edible = null;
        if(areEdible(gs))
        	edible = closestEdibleGhost(gs, current);
        Node power = closestPower(gs, current);
        
        if (areAllEdible(gs)) {
        	if (gs.getMaze().dist(edible, current) < 15)
        		target = edible;
        	else {
        		pill.score(gs, current);
        		target = pill.closest;
        	}
        } else if (areEdible(gs)) {
        	if ((killer != null && gs.getMaze().dist(edible, current) < 15 && gs.getMaze().dist(edible, current) < gs.getMaze().dist(killer, current)))
        		target = edible;
        	else if (killer != null && gs.getMaze().dist(killer, current) < 30)
        		target = adjFarthestFromKiller(gs, current, killer);
        	else {
        		pill.score(gs, current);
        		target = pill.closest;
        	}
        } else {
        	if (gs.getMaze().dist(killer, current) < 30)
        		target = adjFarthestFromKiller(gs, current, killer); 
        	 else {
        		 pill.score(gs, current);
         		target = pill.closest;
        	}
        }
        
        Node next = Utilities.getClosest(current.adj, target, gs.getMaze());
        return Utilities.getWrappedDirection(current, next, gs.getMaze());
    }
}
