package me.shu.lang.java.boxing;

/**
 * http://docs.oracle.com/javase/tutorial/java/data/autoboxing.html
 * <br />
 * boolean -> Boolean
 * <br />
 * byte -> Byte
 * <br />
 * char -> Character
 * <br />
 * float -> Float
 * <br />
 * int -> Integer
 * <br />
 * long -> Long
 * <br />
 * short -> Short
 * <br />
 * double -> Double
 */

public class Example {
	public static void main(String[] args) {
		{
			System.out.println("--- autoboxing of Integer");
			
			Integer a = 1;
			Integer b = 2;
			Integer c = 3;
			Integer d = 3;
			Integer e = 128;
			Integer f = 128;
			Long g = 3l;
			
			System.out.println(c == d); // cache
			System.out.println(e == f); // no cache
			System.out.println(c == (a+b)); // unboxing
			System.out.println(c.equals(a+b)); // autoboxing
			System.out.println(g == (a+b)); // unboxing
			System.out.println(g.equals(a+b));
		}
		
		{
		}
		
	}
}
