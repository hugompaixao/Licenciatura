package Lab3_GenericJugs;

import org.junit.Assert;
import org.junit.Test;

import java.util.Iterator;

public class ATests {
    @Test
    public void testSolve1() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("8 0 0"), new GenericJugs("0 5 3"));
        assert it != null;
        compareItSize(it, 2);
    }

    @Test
    public void testSolve2() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("8 0 0"), new GenericJugs("4 1 3"));
        assert it != null;
        compareItSize(it, 7);
    }

    private void compareItSize(Iterator<AStar.State> it, int expectedSize) {
        AStar.State last=it.next();
        GenericJugs.setMax("8 5 3");
        while (it.hasNext())
            last = it.next();
        Assert.assertEquals(expectedSize,last.getG(),0);
    }

    @Test
    public void testSolve3() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("4 1 3"), new GenericJugs("8 0 0"));
        assert it != null;
        compareItSize(it, 2);
    }

    @Test
    public void testSolve4() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("0 0 3"), new GenericJugs("0 3 0"));
        assert it != null;
        compareItSize(it, 1);
    }

    @Test
    public void testSolve5() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("0 5 3"), new GenericJugs("4 4 0"));
        assert it != null;
        compareItSize(it, 7);
    }

    @Test
    public void testSolve6() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("4 4 0"), new GenericJugs("0 5 3"));
        assert it != null;
        compareItSize(it, 2);
    }

    @Test
    public void testSolve7() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("0 0 0"), new GenericJugs("0 0 0"));
        assert it != null;
        compareItSize(it, 0);
    }

    @Test
    public void testSolve8() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("8 5 3"), new GenericJugs("8 5 3"));
        assert it != null;
        compareItSize(it, 0);
    }

    @Test
    public void testSolve9() {
        AStar actual = new AStar();
        GenericJugs.setMax("8 7 6 5 4 3 2 1");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("0 0 0 0 4 3 2 1"),
                new GenericJugs("1 1 1 1 1 3 1 1"));
        assert it != null;
        compareItSize(it, 8);
    }

    @Test
    public void testSolve10() {
        AStar actual = new AStar();
        GenericJugs.setMax("21 13 8 5 3");
        Iterator<AStar.State> it = actual.solve(new GenericJugs("21 0 0 0 0"),
                new GenericJugs("6 4 4 4 3"));
        assert it != null;
        compareItSize(it, 13);
    }
}