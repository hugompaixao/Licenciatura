package screenpac.controllers;

import screenpac.extract.Constants;
import screenpac.model.*;
import screenpac.features.NearestPillDistance;
import screenpac.features.Utilities;
import java.awt.*;
import java.util.ArrayList;
import java.util.Stack;

/**
 * @author Hugo Paixão
 * tentativa de criar um perimetro a volta do power e o pacman comer as pill nesse perimetro
 */
public class IA2122P2G07 implements AgentInterface, Constants {
    NearestPillDistance pill;
    ArrayList<Node> powers;
    Node powerEaten;

    public IA2122P2G07(GameStateInterface gs) {
        pill = new NearestPillDistance();
        powers = gs.getMaze().getPowers();
        powerEaten = null;
    }

    /**
     * Method returns the Node of the closest ghost in a killer state
     * from the Node given
     * also sets ghost Node with the color red
     * 
     * @param gs - GameStateInterface
     * @param node - Node
     * @return closest - Node
     */
    public Node closestKillerGhost(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (GhostState var : gs.getGhosts())
            if (!var.edible() && !var.returning() && gs.getMaze().dist(var.current, node) < minDist) {
                minDist = gs.getMaze().dist(var.current, node);
                closest = var.current;
            }

        if(closest != null)
            closest.col = Color.red;

        return closest;
    }


    /**
     * Method returns the Node of the closest ghost in a edible state
     * from the Node given
     * also sets ghost Node with the color cyan
     * 
     * @param gs - GameStateInterface
     * @param node - Node
     * @return closest - Node
     */
    public Node closestEdibleGhost(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (GhostState var : gs.getGhosts())
            if (var.edible() && gs.getMaze().dist(var.current, node) < minDist) {
                minDist = gs.getMaze().dist(var.current, node);
                closest = var.current;
            }

        if(closest != null)
            closest.col = Color.cyan;
        return closest;
    }

    /**
     * Method returns the Node of the closest power
     * from the Node given
     * also sets power Node with the color cyan
     * 
     * @param gs - GameStateInterface
     * @param node - Node
     * @return closest - Node
     */
    public Node closestPower(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (Node var : gs.getMaze().getPowers()) {
            if (gs.getMaze().dist(node, var) < minDist) {
                minDist = gs.getMaze().dist(node, var);
                closest = var;
            }
        }

        if(closest != null)
            closest.col = Color.cyan;
        return closest;
    }

    public boolean allGhostsEdible(GameStateInterface gs) {
        for (GhostState var : gs.getGhosts())
            if (!var.edible())
                return false;
        return true;
    }

    /**
     *
     * @param gs
     * @return
     */
    public boolean ghostsEdible(GameStateInterface gs) {
        for (GhostState var : gs.getGhosts())
            if (var.edible())
                return true;
        return false;
    }

    /**
     *
     * @param gs
     */
    public void getPowerEaten(GameStateInterface gs) {
        for(Node var : powers)
            if(!gs.getMaze().getPowers().contains(var)) {
                powerEaten = var;
                powers.remove(var);
            }
    }

    /**
     *
     * @param gs
     * @param edible
     * @return
     */
    public boolean controlEdibleTime(GameStateInterface gs, Node edible) {
        return (gs.getGhosts()[edible.nodeIndex].edibleTime < 10);
    }

    /**
     *
     * @param gs
     * @return
     */
    private ArrayList<Node> arroundPower(GameStateInterface gs) {
        ArrayList<Node> closests = new ArrayList<Node>();
        for (Node var : gs.getMaze().getPills())
            if(gs.getMaze().dist(var, powerEaten) < 25)
                closests.add(var);

        return closests;
    }

    /**
     *
     * @param gs
     * @param node
     * @return
     */
    public Node closestArroundPowerEaten(GameStateInterface gs, Node node) {
        ArrayList<Node> closests = arroundPower(gs);
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for(Node var : closests)
            if(!closests.isEmpty())
                if(gs.getMaze().dist(var, node) < minDist) {
                    minDist = gs.getMaze().dist(var, node);
                    closest = var;
                }

        if(closest != null)
            closest.col = Color.pink;

        return closest;
    }

    public Node fledTo(GameStateInterface gs, Node pacman) {
        return null;
    }


    @Override
    public int action(GameStateInterface gs) {
        gs.copy();
        Node current = gs.getPacman().current;
        Node target = null, killer = null, edible = null, power = null;

        if(!allGhostsEdible(gs))
            killer = closestKillerGhost(gs, pacman);

        if(ghostsEdible(gs))
            edible = closestEdibleGhost(gs, pacman);

        if(!gs.getMaze().getPowers().isEmpty())
            power = closestPower(gs, pacman);

        if (allGhostsEdible(gs))
            getPowerEaten(gs);

        if (ghostsEdible(gs)) {
            if (killer != null && gs.getMaze().dist(current, killer) < 8)
                target = fledTo(gs, current);
            else if (closestArroundPowerEaten(gs, current) == null || gs.getGhosts()[edible.nodeIndex].edibleTime < 10) {
                pill.score(gs, current);
                target = pill.closest;
            } else if (gs.getMaze().dist(powerEaten, edible) < 20)
                target = edible;
            else if (gs.getMaze().dist(current, edible) < 10)
                target = edible;
            else
                target = closestArroundPowerEaten(gs, current);
        } else {
            if (killer != null && gs.getMaze().dist(current, killer) < 8) {
                if(!gs.getMaze().getPowers().isEmpty() && gs.getMaze().dist(current, power) < gs.getMaze().dist(killer, power))
                    target = power;
                else
                    target = fledTo(gs, current);
            } else {
                pill.score(gs, current);
                target = pill.closest;
            }
        }

        Node next = Utilities.getClosest(current.adj, target, gs.getMaze());
        return Utilities.getWrappedDirection(current, next, gs.getMaze());
    }

}
