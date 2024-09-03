package screenpac.controllers;

import screenpac.extract.Constants;
import screenpac.model.*;
import screenpac.features.Utilities;
import java.util.*;

public class IA2122P2G07 implements AgentInterface, Constants {
    public Stack<Node> positions;


    public IA2122P2G07() {
        positions = new Stack<>();
    }

    /**
     * Method returns the closest Pill to a given Node
     * if closest is null return null
     *
     * @param gs - GameStateInterface
     * @param node - Node
     * @return closest - Node
     */
    public Node closestPill(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (Node n : gs.getMaze().getPills())
            if (gs.getPills().get(n.pillIndex))
                if (gs.getMaze().dist(node, n) < minDist) {
                    minDist = gs.getMaze().dist(node, n);
                    closest = n;
                }

        return closest;
    }

    /**
     * Method returns the closest Power to Ms.pacman position
     * if closest is null return null
     *
     * @param gs - GameStateInterface
     * @return closest - Node
     */
    public Node closestPower(GameStateInterface gs) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (Node var : gs.getMaze().getPowers())
            if (gs.getPowers().get(var.powerIndex))
                if (gs.getMaze().dist(gs.getPacman().current, var) < minDist) {
                    minDist = gs.getMaze().dist(gs.getPacman().current, var);
                    closest = var;
                }

        return closest;
    }


    /**
     * Method returns the closest ghost to Ms.pacman in an edible state
     * if closest is null returns null
     *
     * @param gs - GameStateInterface
     * @return closest - Node
     */
    public Node closestEdibleGhost(GameStateInterface gs) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (GhostState var : gs.getGhosts())
            if (gs.getMaze().dist(var.current, gs.getPacman().current) < minDist && var.edible()) {
                minDist = gs.getMaze().dist(var.current, gs.getPacman().current);
                closest = var.current;
            }

        return closest;
    }

    /**
     * Method returns the closest ghost to Ms.pacman that's not in an
     * edible or returning state
     *
     * @param gs - GameStateInterface
     * @return closest - Node
     */
    public Node closestKillerGhost(GameStateInterface gs) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (GhostState var : gs.getGhosts())
            if (!var.edible() && !var.returning() && gs.getMaze().dist(var.current, gs.getPacman().current) < minDist) {
                minDist = gs.getMaze().dist(var.current, gs.getPacman().current);
                closest = var.current;
            }

        return closest;
    }

    /**
     * Method returns true if at least 1 ghost is in a edible state
     * else returns false
     *
     * @param gs - GameStateInterface
     * @return true/false - boolean
     */
    public boolean edibleGhosts(GameStateInterface gs) {
        for (GhostState var : gs.getGhosts())
            if (var.edible())
                return true;
        return false;
    }

    /**
     * Method returns the closest Power to Ms.pacman that was already ate
     * if closest is null returns null
     *
     * @param gs - GameStateInterface
     * @return closest - Node
     */
    public Node atePower(GameStateInterface gs) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (Node var : gs.getMaze().getPowers())
            if (!gs.getPowers().get(var.powerIndex))
                if (gs.getMaze().dist(gs.getPacman().current, var) < minDist) {
                    minDist = gs.getMaze().dist(gs.getPacman().current, var);
                    closest = var;
                }

        if(closest == null)
            return closestPower(gs);

        return closest;
    }

    /**
     * Method returns the Pill that is in better position in relation to the closest ate Power and to Ms.pacman
     * if closest is null returns null
     *
     * @param gs - GameStateInterface
     * @return closest - Node
     */
    public Node pillsNearPower(GameStateInterface gs) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        int minDistPac = Integer.MAX_VALUE;
        for (Node powers : gs.getMaze().getPowers())
            if (!gs.getPowers().get(powers.powerIndex) && gs.getMaze().dist(powers, gs.getPacman().current) < minDist)
                for (Node pills : gs.getMaze().getPills())
                    if (gs.getPills().get(pills.pillIndex) && gs.getMaze().dist(pills, atePower(gs)) < minDistPac)
                        if (gs.getMaze().dist(gs.getPacman().current, pills) < minDist) {
                            minDist = gs.getMaze().dist(gs.getPacman().current, pills);
                            minDistPac = gs.getMaze().dist(pills, atePower(gs));
                            closest = pills;
                        }

        return closest;
    }

    /**
     * Method returns the closest adjacent node to the target
     *
     * @param gs - GameStateInterface
     * @param nodes - ArrayList<Node>
     * @param node - Node
     * @return closest - Node
     */
    public Node bestAdj(GameStateInterface gs, ArrayList<Node> nodes, Node node) {
        double minDist = Double.MAX_VALUE;
        Node closest = null;
        for (Node var : nodes)
            if (gs.getMaze().dist(var, node) < minDist) {
                minDist = gs.getMaze().dist(var, node);
                closest = var;
            }

        return closest;
    }

    /**
     * Method returns true if at least 1 ghost is in the way of Ms.pacman to reach the target
     * else returns false
     *
     * @param gs - GameStateInterface
     * @param nodes - ArrayList<Node>
     * @param target - Node 
     * @return true/false - boolean
     */
    public boolean ghostInTheWay(GameStateInterface gs, ArrayList<Node> nodes, Node target) {
        Node closest = bestAdj(gs, nodes, target);
        for (GhostState ghosts : gs.getGhosts()) {
            if ((!ghosts.edible() && !ghosts.returning()) && (ghosts.current == closest || gs.getMaze().dist(ghosts.current, closest) < 8))
                return true;
        }
        if (target == closest)
            return false;

        return ghostInTheWay(gs, closest.adj, target);
    }

    /**
     * Method returns the closest node, that doesn't have a ghost in the way, that is at least 20 nodes far way from Ms.pacman and is closer to Ms.pacman than to a ghost
     * that node can't be the same that Ms.pacman or ghosts are at that moment
     * else returns null
     *
     * @param gs - GameStateInterface
     * @return closest - Node
     */
    public Node seeAround(GameStateInterface gs) {
        Node closest = null;
        Node ghost = closestKillerGhost(gs);
        int minDist = 0;
        for (Node var : gs.getMaze().getMap()) {
            if (ghostInterClose(gs, var) && !ghostInTheWay(gs, gs.getPacman().current.adj, var)) {
                if (gs.getMaze().dist(var, gs.getPacman().current) > 20) {
                    if (ghostInterClose(gs, var) && gs.getMaze().dist(ghost, var) > gs.getMaze().dist(gs.getPacman().current, var) + 10 && ghost != var && gs.getPacman().current != var) {
                        if (gs.getMaze().dist(gs.getPacman().current, var) > minDist) {
                            minDist = gs.getMaze().dist(gs.getPacman().current, var);
                            closest = var;
                        }
                    }
                }
            }
        }
        return closest;
    }

    /**
     * Method returns the closest node, that doesn't have a ghost in the way, that is at least 20 nodes intersection (with 3 or 4 adjacent nodes) 
     * far way from Ms.pacman and is closer to Ms.pacman than to a ghost
     * that node can't be the same that Ms.pacman or ghosts are at that moment
     * else returns seeAround
     *
     * @param gs - GameStateInterface
     * @return closest - Node
     */
    public Node seeAroundInter(GameStateInterface gs) {
        Node closest = null;
        Node ghost = closestKillerGhost(gs);
        int minDist = 0;
        for (Node var : gs.getMaze().getMap()) {
            if (gs.getPacman().current.adj.size() >= 3 && seeAround(gs) != null) return seeAround(gs);
            if (var.adj.size() >= 3 && ghostInterClose(gs, var) && !ghostInTheWay(gs, gs.getPacman().current.adj, var))
                if (gs.getMaze().dist(var, gs.getPacman().current) > 20)
                    if (ghostInterClose(gs, var) && gs.getMaze().dist(ghost, var) > gs.getMaze().dist(gs.getPacman().current, var) + 10 && ghost != var && gs.getPacman().current != var)
                        if (gs.getMaze().dist(gs.getPacman().current, var) > minDist) {
                            minDist = gs.getMaze().dist(gs.getPacman().current, var);
                            closest = var;
                        }
        }

        return closest;
    }

    /**
     * Method returns how many ghosts are less than 30 nodes of distance
     *
     * @param gs - GameStateInterface
     * @param node - Node
     * @return count - int 
     */
    public int cornered(GameStateInterface gs, Node node) {
        int count = 0;
        for (GhostState var : gs.getGhosts())
            if (!var.edible() && gs.getMaze().dist(var.current, node) < 30 && !var.returning())
                count++;

        return count;
    }

    /**
     * Method analysis the the map and returns the best Node
     * where ms.pacman showed run to
     *
     * @param gs - GameStateInterface
     * @return target - Node
     */
    public Node survive(GameStateInterface gs) {
        Node target;
        Node ghost = closestKillerGhost(gs);

        if (seeAround(gs) != null)
            target = seeAround(gs);
        else if (cornered(gs, gs.getPacman().current) > 1 && seeAroundInter(gs) != null)
            target = seeAroundInter(gs);
        else if (gs.getMaze().dist(ghost, positions.peek()) > gs.getMaze().dist(ghost, gs.getPacman().current))
            target = positions.pop();
        else if (gs.getMaze().dist(ghost, positions.peek()) > gs.getMaze().dist(ghost, gs.getPacman().current))
            target = seeAroundInter(gs);
        else {
            target = closestPill(gs, gs.getPacman().current);
            positions.push(gs.getPacman().current);
        }
        return target;
    }

    /**
     * Method returns false if at least 1 ghost as an edible time less that 8
     * else returns true
     *
     * @param gs - GameStateInterface
     * @return true/false - boolena
     */
    public boolean lastSecond(GameStateInterface gs) {
        for (GhostState var : gs.getGhosts())
            if (var.edible() && var.edibleTime < 8)
                return false;
        return true;
    }

    /**
     * Method returns if a ghost is a 20 nodes close to Ms.pacman
     * else return false
     *
     * @param gs - GameStateInterface
     * @param var - Node
     * @return true/false - boolean 
     */
    public boolean ghostInterClose(GameStateInterface gs, Node var) {
        for (GhostState ghosts : gs.getGhosts())
            if (gs.getMaze().dist(var, ghosts.current) > 20)
                return true;
        return false;
    }

    /**
     * Method analysis the map state and returns the best direction to
     * ms.pacman go to
     * 
     * @param gs - GameStateInterface
     * @return dir - int
     */
    public int action(GameStateInterface gs) {
        gs = gs.copy();
        Node current = gs.getPacman().current;
        Node target;

        if (edibleGhosts(gs) && lastSecond(gs)) {
            if (gs.getMaze().dist(closestEdibleGhost(gs), current) < 20) {
                target = closestEdibleGhost(gs);
                positions.push(current);
            } else if (closestKillerGhost(gs) != null && gs.getMaze().dist(closestKillerGhost(gs), current) < 20)
                target = survive(gs);

            else {
                target = pillsNearPower(gs);
                positions.push(current);
            }
        } else if (closestKillerGhost(gs) != null && !gs.getPowers().isEmpty() && gs.getMaze().dist(current, closestPower(gs)) < 15 && gs.getMaze().dist(current, closestPower(gs)) < gs.getMaze().dist(closestKillerGhost(gs), closestPower(gs))) {
            target = closestPower(gs);
        } else if (closestKillerGhost(gs) != null && gs.getMaze().dist(closestKillerGhost(gs), current) < 25) {
            target = survive(gs);
        } else {
            target = closestPill(gs, current);
            positions.push(current);
        }

        Node next = Utilities.getClosest(current.adj, target, gs.getMaze());
        return Utilities.getWrappedDirection(current, next, gs.getMaze());
    }
}