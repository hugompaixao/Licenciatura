package Lab3_GenericJugs;

import java.util.List;

public interface Ilayout {
    /**
     *
     * @return the children of the receiver.
     */
    List<Ilayout> children();

    /**
     *
     * @param l
     * @return true if the receiver equals the argument l.
     */
    boolean isGoal(Ilayout l);

    /**
     *
     * @return the cost for moving from the input config to the receiver.
     */
    double getG();

    /**
     *
     * @return the number of liters misplaced.
     */
    double getHeuristic(Ilayout goal);
}
