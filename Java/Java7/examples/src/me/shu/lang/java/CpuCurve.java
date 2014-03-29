package me.shu.lang.java;


/**
 *
 * @author Wang7x
 */
public class CpuCurve {

    public static final double TIME = 1000;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException {
        double x = 0;
        double y = 0;

        while (true) {
            y = (Math.sin(x) + 1) * TIME / 2;
            doSomeSimpleWork(y);
            x += 0.1;
            Thread.sleep((long) (TIME - y));
        }
    }

    private static void doSomeSimpleWork(double y) {
        long startTime = System.currentTimeMillis();
        while ((System.currentTimeMillis() - startTime) < y) {
        }
    }
}