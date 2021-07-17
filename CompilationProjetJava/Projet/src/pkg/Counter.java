package pkg;

public class Counter {
    int n = 0;

    public int get() {
        return n;
    }

    public Counter inc() {
        n += 1;
        return this;
    }
}