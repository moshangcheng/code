package me.shu.lang.java8.CountedCompleter;

import java.util.Arrays;
import java.util.Random;

public class ParallelSort {
public static void main(String[] args) {
    	
    	long startTime;
    	long endTime;
    	
    	int[] data = new int[1000 * 1000 * 30];
    	Random rand = new Random();
    	for(int i = 0; i < data.length; i++)
    	{
    		data[i] = rand.nextInt(Integer.MAX_VALUE);
    	}

    	int[] data1 = data.clone();
    	
    	{
    		startTime = System.currentTimeMillis();
    		Arrays.sort(data);
    		endTime = System.currentTimeMillis();
    		System.out.println("total time: " + (endTime - startTime));
    	}
        
        {
        	startTime = System.currentTimeMillis();
        	Arrays.parallelSort(data1);
        	endTime = System.currentTimeMillis();
    		System.out.println("total time: " + (endTime - startTime));
        }        
    }
}
