package my.pkg;

import org.junit.Test;
import static org.junit.Assert.*;

import pkg.Counter;


public class OtherTest {
  
    @Test
    public void testGet() {
        System.out.println("get");
        final Counter c = new Counter();
        assertEquals(0, c.get());
        c.inc();
        assertEquals(1, c.get());
        c.inc().inc().inc();
        assertEquals(4, c.get());
    
    }
}


