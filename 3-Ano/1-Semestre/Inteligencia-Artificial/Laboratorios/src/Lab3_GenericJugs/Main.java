package Lab3_GenericJugs;

import java.util.Iterator;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        GenericJugs.setMax(sc.nextLine());

        AStar s = new AStar();
        Iterator<AStar.State> it = s.solve(new GenericJugs(sc.nextLine()), new GenericJugs(sc.nextLine()));

        if(it == null)
            System.out.println("no solution was found");

        else {
            while(it.hasNext()) {
                AStar.State i = it.next();
                //System.out.println(i);

                if(!it.hasNext())
                    System.out.println((int) i.getG());
            }
        }
        sc.close();
    }
}
