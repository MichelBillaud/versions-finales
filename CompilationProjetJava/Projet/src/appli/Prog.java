package appli;

import pkg.Counter;
public class Prog {


    public static void main(final String[] args) {
        Aux.hello("guys");
        final Counter c = new Counter();
        c.inc();
        System.out.println("compteur = " + c.get());
    }
    
}
