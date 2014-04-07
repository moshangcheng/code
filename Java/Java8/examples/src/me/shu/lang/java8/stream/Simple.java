/**
 * 
 */
package me.shu.lang.java8.stream;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.*;
import java.util.stream.IntStream.Builder;

/**
 * @author moshangcheng
 *
 */
public class Simple {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		{
			System.out.println("--- use List to make stream");
			Integer[] intArray = {1, 2, 3, 4, 5, 6, 7, 8 };
			Arrays.asList(intArray).stream().forEach(e -> System.out.print(e + " "));
			System.out.println();
		}
		
		{
			System.out.println("--- use Array to make stream");
			int[] intArray = {1, 2, 3, 4, 5, 6, 7, 8 };
			IntStream.of(intArray).forEach(e -> System.out.print(e + " "));
			System.out.println();
		}
		
		{
			System.out.println("--- another way to use Array to make stream");
			int[] intArray = {1, 2, 3, 4, 5, 6, 7, 8 };
			Arrays.stream(intArray).forEach(e -> System.out.print(e + " "));
			System.out.println();
		}
		
		{
			System.out.println("--- use String to make stream");
			String str = "abcdefghijklmnop";
			str.chars().forEach(e -> System.out.print((char)e + " "));
			System.out.println();
		}
		
		{
			System.out.println("--- use range() to make stream");
			IntStream.range(0, 10).forEach(e -> System.out.print(e + " "));
			System.out.println();
		}
		
		{
			System.out.println("--- use iterate() to make stream");
			IntStream.iterate(1, i -> i+2).limit(10).forEach(e -> System.out.print(e + " "));
			System.out.println();
		}
		
		{
			System.out.println("--- use generate() to make stream");
			Stream.generate(Math::random).limit(4).forEach(e -> System.out.print(e + " "));
			System.out.println();
		}
		
		{
			System.out.println("--- use Builder to make stream");
			Builder isBuilder = IntStream.builder();
			for(int i = 0; i < 10; i++)
			{
				isBuilder.add(i);
			}
			//isBuilder.build().forEach(System.out::println);
			isBuilder.build().parallel().forEach(e -> System.out.print(e + " "));
			System.out.println();
		}
		
//		{
//		IntStream ints = IntStream.range(0, 1000 * 1);
//		Stream<Integer> boxedInts = ints.boxed();
//		Stream<Double> doubles = boxedInts.map(e -> Double.valueOf(e.doubleValue()));
//		doubles.forEach(e -> System.out.print(e + " "));
//	}
	}

}
