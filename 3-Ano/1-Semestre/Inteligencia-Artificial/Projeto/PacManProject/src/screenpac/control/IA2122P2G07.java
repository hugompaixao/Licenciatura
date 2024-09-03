package screenpac.controllers;

import screenpac.extract.Constants;
import screenpac.model.*;
import screenpac.features.NearestPillDistance;
import screenpac.features.Utilities;

import java.awt.*;
import java.util.ArrayList;
import java.util.Stack;

public class IA2122P2G07 implements AgentInterface, Constants {
    NearestPillDistance pill;
    final int max = Integer.MAX_VALUE;
    final int min = Integer.MIN_VALUE;
    public Stack<Node> positions;


    public IA2122P2G07() {
        positions = new Stack<>();
        pill = new NearestPillDistance();
    }

    public Node closestGhost(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (GhostState var : gs.getGhosts()) {
            if (!var.edible() && gs.getMaze().dist(var.current, node) < minDist) {
                minDist = gs.getMaze().dist(var.current, node);
                closest = var.current;
            }
        }

        if (closest != null) {
            closest.col = Color.red;
        }

        return closest;
    }

    public Node closestEdibleGhost(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (GhostState var : gs.getGhosts()) {
            if (gs.getMaze().dist(var.current, node) < minDist && var.edible()) {
                minDist = gs.getMaze().dist(var.current, node);
                closest = var.current;
            }
        }

        if (closest != null) {
            closest.col = Color.green;
        }

        return closest;
    }

    public Node closestNotEdibleGhost(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (GhostState var : gs.getGhosts()) {
            if (!var.edible() && gs.getMaze().dist(var.current, node) < minDist && !var.returning()) {
                minDist = gs.getMaze().dist(var.current, node);
                closest = var.current;
            }
        }

        if (closest != null) {
            closest.col = Color.red;
        }

        return closest;
    }

    public int cornered(GameStateInterface gs, Node node) {
        int count = 0;
        int minDist = 30;
        for (GhostState var : gs.getGhosts()) {
            if (!var.edible() && gs.getMaze().dist(var.current, node) < minDist && !var.returning()) {
                count++;
            }
        }

        return count;
    }

    public Node closestPower(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (Node var : gs.getMaze().getPowers()) {
            //if (gs.getPowers().get(var.powerIndex)) {
            if (gs.getMaze().dist(node, var) < minDist) {
                minDist = gs.getMaze().dist(node, var);
                closest = var;
                // }
            }
        }

        if (closest != null) {
            closest.col = Color.cyan;
        }

        return closest;
    }

    public Node closestEdiblePower(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (Node var : gs.getMaze().getPowers()) {
            if (gs.getPowers().get(var.powerIndex)) {
                if (gs.getMaze().dist(node, var) < minDist) {
                    minDist = gs.getMaze().dist(node, var);
                    closest = var;
                }
            }
        }

        if (closest != null) {
            closest.col = Color.cyan;
        }

        return closest;
    }

    public Node atePower(GameStateInterface gs, Node node) {
        Node closest = null;
        int minDist = Integer.MAX_VALUE;
        for (Node var : gs.getMaze().getPills()) {
            if (!gs.getPowers().get(var.powerIndex)) {
                if (gs.getMaze().dist(node, var) < minDist) {
                    minDist = gs.getMaze().dist(node, var);
                    closest = var;
                }
            }
        }

        if (closest != null) {
            closest.col = Color.yellow;
        }

        return closest;
    }

    public boolean powers(GameStateInterface gs) {
        return !(gs.getMaze().getPowers().isEmpty());
    }

    public boolean edibleGhosts(GameStateInterface gs) {
        boolean edible = false;
        for (GhostState var : gs.getGhosts())
            if (var.edible()) {
                edible = true;
                break;
            }
        return edible;
    }

    public Node closestAdj(GameStateInterface gs, Node pacman, Node ghost) {
        Node tmp = null;
        for (Node node : pacman.adj) {
            if (gs.getMaze().dist(node, ghost) > gs.getMaze().dist(pacman, node)) {
                tmp = node;
            }
        }
        return tmp;
    }

    public Node InterAllGhosts(GameStateInterface gs, Node pacman) {
        Node closest = null;
        int minDist = min;
        for (Node var : gs.getMaze().getMap()) {
            if (var.adj.size() >= 3) {
                for (GhostState ghost : gs.getGhosts()) {
                    if (gs.getMaze().dist(ghost.current, var) > gs.getMaze().dist(pacman, var) + 3 && pacman != var) {
                        if (gs.getMaze().dist(pacman, var) > minDist) {
                            minDist = gs.getMaze().dist(pacman, var);
                            closest = var;
                        }
                    }
                }
            }
        }

        if (closest != null) {
            closest.col = Color.pink;
        }

        return closest;
    }


    public Node furtherInter(GameStateInterface gs, Node pacman, Node ghost) {
        Node closest = null;
        int minDist = min;
        for (Node var : gs.getMaze().getMap()) {
            if (var.adj.size() >= 3) {
                if (gs.getMaze().dist(ghost, var) > gs.getMaze().dist(pacman, var) + 3 && pacman != var) {
                    if (gs.getMaze().dist(pacman, var) > minDist) {
                        minDist = gs.getMaze().dist(pacman, var);
                        closest = var;
                    }
                }
            }
        }

        if (closest != null) {
            closest.col = Color.pink;
        }

        return closest;
    }

    public Node closestInter(GameStateInterface gs, Node pacman) {
        Node closest = null;
        int minDist = max;
        for (Node var : gs.getMaze().getMap()) {
            if (var.adj.size() >= 3) {
                for (GhostState ghost : gs.getGhosts()) {
                    if (gs.getMaze().dist(ghost.current, var) > gs.getMaze().dist(pacman, var) + 10 && pacman != var) {
                        if (gs.getMaze().dist(pacman, var) < minDist) {
                            minDist = gs.getMaze().dist(pacman, var);
                            closest = var;
                        }
                    }
                }
            }
        }

        if (closest != null) {
            closest.col = Color.pink;
        }

        return closest;
    }

    public static boolean ghostInTheWay(GameStateInterface gs, ArrayList<Node> nodes, Node target) {

        double best = Double.MAX_VALUE;
        // selected current
        Node sel = null;
        for (Node n : nodes) {
            int d = gs.getMaze().dist(n, target);
            if (d < best) {
                best = d;
                sel = n;
            }
        }
        for (GhostState ghosts : gs.getGhosts()) {
            if (!ghosts.edible() && !ghosts.returning() && ghosts.current == sel)
                return true;
        }
        if (target == sel)
            return false;

        return ghostInTheWay(gs, sel.adj, target);
    }

    public Node score(GameStateInterface gs, Node node) {
        // most obvious way: iterate over the set of pills
        Node closest = null;
        int minDist = max;
        for (Node n : gs.getMaze().getMap()) {
            if (gs.getMaze().dist(n, node) > 15)
                if (!ghostInTheWay(gs, node.adj, n)) {
                    if (gs.getMaze().dist(node, n) < minDist) {
                        minDist = gs.getMaze().dist(node, n);
                        closest = n;
                    }
                }
        }
        if (closest != null) {
            closest.col = Color.green;
        }
        return closest;
    }


    public Node survive(GameStateInterface gs, Node pacman) {
        Node target = null;
        Node previews = positions.peek();
        Node ghost = closestGhost(gs, pacman);
        Node tmp = closestAdj(gs, pacman, ghost);
        /* */
        if (sharinganSolo(gs, pacman) != null) {
            target = sharinganSolo(gs, pacman);
            target.col = Color.ORANGE;
            return target;
        }
        else if (cornered(gs, pacman) > 1 && sharingan(gs, pacman) != null) {
            target = sharingan(gs, pacman);
            target.col = Color.ORANGE;
            return target;
        }
        else if (gs.getMaze().dist(ghost, previews) > gs.getMaze().dist(ghost, pacman))
            target = positions.pop();
        else if (gs.getMaze().dist(ghost, previews) > gs.getMaze().dist(ghost, pacman))
            target = sharingan(gs, pacman);
        else if(score(gs, pacman) != null){
            target = score(gs, pacman);
        }
        else {
            pill.score(gs, pacman);
            target = pill.closest;
            positions.push(pacman);
        }
        // target = sharinganSolo(gs, pacman);
        target.col = Color.ORANGE;
        return target;
    }

   /* public double score(GameStateInterface gs, Node node) {
        // most obvious way: iterate over the set of pills
        Node closest = null;
        int minDist = max;
        for (Node n : gs.getMaze().getPills()) {
            if (gs.getPills().get(n.pillIndex)) {
                if (gs.getMaze().dist(node, n) < minDist) {
                    minDist = gs.getMaze().dist(node, n);
                    closest = n;
                }
            }
        }
        if (closest != null) {
            closest.col = Color.green;
        }
        return minDist;
    }*/

    /*public static Node getClosest(ArrayList<Node> nodes, Node target, MazeInterface maze, GameStateInterface gs) {
        // if the target current is null then print a warning
        if (target == null) {
            System.out.println("Warning: null target in Utilities.getClosest()");
            return nodes.get(rand.nextInt(nodes.size()));
        }
        double best = Double.MAX_VALUE;
        // selected current
        Node sel = null;
        for (Node n : nodes) {
            int d = maze.dist(n, target);
            if (n.pillIndex != -1){
            if (d < best) {
                best = d;
                sel = n;
            }
            }
        }
        return sel;
    }*/

    public Node sharinganSolo(GameStateInterface gs, Node pacman) {
        Node closest = null;
        Node previews = positions.peek();
        Node ghost = closestGhost(gs, pacman);
        Node tmp = closestAdj(gs, pacman, ghost);
        int minDist = 0;
        for (Node var : gs.getMaze().getMap()) {
            if (/*var.adj.size() >= 3 &&*/ ghostInterClose(gs, var) && !ghostInTheWay(gs, pacman.adj, var)) {
                if (gs.getMaze().dist(var, pacman) < 50) {
                    var.col = Color.red;
                    //  for (GhostState ghosts : gs.getGhosts()) {
                    if (ghostInterClose(gs, var) && gs.getMaze().dist(ghost, var) > gs.getMaze().dist(pacman, var) + 10 && ghost != var && pacman != var) {
                        if (gs.getMaze().dist(pacman, var) > minDist) {

                            minDist = gs.getMaze().dist(pacman, var);
                            closest = var;
                        }
                    }
                }
                //  }
            }
        }
        return closest;
    }

    public Node sharingan(GameStateInterface gs, Node pacman) {
        Node closest = null;
        Node previews = positions.peek();
        Node ghost = closestGhost(gs, pacman);
        Node tmp = closestAdj(gs, pacman, ghost);
        int minDist = 0;
        for (Node var : gs.getMaze().getMap()) {
            if (pacman.adj.size() >= 3 && sharinganSolo(gs, pacman) != null)
                return sharinganSolo(gs, pacman);
            if (var.adj.size() >= 3 && ghostInterClose(gs, var) && !ghostInTheWay(gs, pacman.adj, var)) {
                if (gs.getMaze().dist(var, pacman) < 20) {
                    var.col = Color.red;
                    //  for (GhostState ghosts : gs.getGhosts()) {
                    if (ghostInterClose(gs, var) && gs.getMaze().dist(ghost, var) > gs.getMaze().dist(pacman, var) + 10 && ghost != var && pacman != var) {
                        if (gs.getMaze().dist(pacman, var) > minDist) {
                            minDist = gs.getMaze().dist(pacman, var);
                            closest = var;
                        }
                    }
                }
                //  }
            }
        }
        return closest;
    }

    private boolean ghostInterClose(GameStateInterface gs, Node var) {
        for (GhostState ghosts : gs.getGhosts()) {
            if (gs.getMaze().dist(var, ghosts.current) > 20)
                return true;
        }
        return false;
    }

    public int action(GameStateInterface gs) {
        gs = gs.copy();
        Node current = gs.getPacman().current;
        Node target = null;
        boolean edible = edibleGhosts(gs);
        boolean power = powers(gs);
        boolean powerClose = false;

        if (edible) {
            if (gs.getMaze().dist(closestEdibleGhost(gs, current), current) < 30) {
                target = closestEdibleGhost(gs, current);
                positions.push(current);
            } else if (closestNotEdibleGhost(gs, current) != null && gs.getMaze().dist(closestNotEdibleGhost(gs, current), current) < 20)
                target = survive(gs, current);

            else {
               /* Node closest = null;
                int minDist = min;
                pill.score(gs, atePower(gs, current));
                for (Node i:  current.adj) {
                    if (gs.getMaze().dist(atePower(gs, current), i) > minDist && gs.getMaze().dist(pill.closest, current) < 15) {
                        minDist = gs.getMaze().dist(current, i);
                        closest = i;
                    }
                }*/
                pill.score(gs, current);
                target = pill.closest;
                positions.push(current);
            }
        }

       /* else{
               /* pill.score(gs, current);
                target = pill.closest;

            if (gs.getMaze().dist(current, closestGhost(gs, current)) <= 20 || gs.getMaze().dist(target, closestGhost(gs, target)) <= 20){
                Node farthest = null;
                int maxDist = max;
                for (Node i: current.adj) {
                        if (gs.getMaze().dist(current, i) > maxDist) {
                            maxDist = gs.getMaze().dist(current, i);
                            farthest = i;
                        }
                }
                //target = survive(gs, current);//closestPower(gs, farthest);
            //}
        }*/

        else if (!gs.getPowers().isEmpty() && gs.getMaze().dist(current, closestEdiblePower(gs, current)) < 15 && gs.getMaze().dist(current, closestEdiblePower(gs, closestGhost(gs, current))) < 10) {
            target = closestEdiblePower(gs, current);
        } else if (gs.getMaze().dist(closestGhost(gs, current), current) < 25)
            target = survive(gs, current);
      /*else if(score(gs, current) != null){
            target = score(gs, current);
        }  */
        else {
            pill.score(gs, current);
            target = pill.closest;
            positions.push(current);
        }

        Node next = Utilities.getClosest(current.adj, target, gs.getMaze());
        int dir = Utilities.getWrappedDirection(current, next, gs.getMaze());
        if (ghostInTheWay(gs, current.adj, target))
            System.out.println(true);
        return dir;
    }
}
