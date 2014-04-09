/**
 * 
 */
package me.shu.lang.java8.stream;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.stream.*;
import java.util.stream.IntStream.Builder;

/**
 * @author moshangcheng
 *
 */
public class ConsumeStream {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		{
			System.out.println("--- use iterator to consume stream");
			int[] intArray = { 1, 2, 3, 4, 5, 6, 7, 8 };
			Iterator<Integer> iter = IntStream.of(intArray).iterator();
			while(iter.hasNext()) {
				System.out.print(iter.next() + " ");
			}
			System.out.println();
		}
		
		{
			System.out.println("--- use iterator to consume stream");
			int[] intArray = { 1, 2, 3, 4, 5, 6, 7, 8 };
			Iterator<Integer> iter = IntStream.of(intArray).iterator();
			while(iter.hasNext()) {
				System.out.print(iter.next() + " ");
			}
			System.out.println();
		}
	}

}
