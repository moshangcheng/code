package me.shu.lang.java.forkjoin;

import java.util.Arrays;
import java.util.Random;

public class QuickSort {

	final int threshold = 32;
    
    final int[] data;
    final int lo;
    final int hi;
    
    public QuickSort(int n)
    {
    	this.data = new int[n];
    	this.lo = 0;
    	this.hi = n;
    	
    	Random rand = new Random();
    	for(int i = 0; i < n; i++)
    	{
    		this.data[i] = rand.nextInt(Integer.MAX_VALUE);
    	}
    }

    public QuickSort(QuickSort o) {
        this.data = o.data.clone();
        this.lo = 0;
        this.hi = this.data.length;
    }
    
    public QuickSort(int[] array, int lo, int hi) {
    	this.data = array;
        this.lo = lo;
        this.hi = hi;
    }
    
    void swap(int i, int j)
    {
    	int temp = data[i];
    	data[i] = data[j];
    	data[j] = temp;
    }
    
    // my partition
    int mypartition()
    {
    	int v = data[hi - 1];
    	int i = lo;
    	for(int j = hi - 1; j > i;)
    	{
    		if(data[j] <= v)
    		{
    			swap(i, j);
    			i++;
    		}
    		else
    		{
    			j--;
    		}
    	}
    	if(data[i] < v)
    	{
    		i++;
    	}
    	return i;
    }
    
    // standard partition
    int partition()
    {
    	int v = data[hi - 1];
    	int i = lo;
    	for(int j = lo; j < hi - 1; )
    	{
    		if(data[j] <= v)
    		{
    			swap(i, j);
    			i++;
    		}
    		j++;
    	}
    	swap(i, hi - 1);
    	return i;
    }
    
    public void sort()
    {
    	Arrays.sort(data, lo, hi);
    }
    
    public boolean sorted()
    {
    	for(int i = lo; i + 1 < hi; i++)
    	{
    		if(data[i] > data[i+1])
    		{
    			return false;
    		}
    	}
    	return true;
    }

    protected void compute() {
        if (hi - lo < threshold)
            sort();
        else {
            int midpoint = mypartition();
            FJSort left = new FJSort(data, lo, midpoint);
            FJSort right = new FJSort(data, midpoint, hi);
            left.sort();
            right.sort();
        }
    }

    public static void main(String[] args) {
    	
    	long startTime;
    	long endTime;
    	
    	FJSort p = new FJSort(1000 * 1000 * 30);
    	FJSort p1 =  new FJSort(p);
    	
    	{
    		startTime = System.currentTimeMillis();
    		p.sort();
    		endTime = System.currentTimeMillis();
    		System.out.println("sorted: " + p.sorted());
    		System.out.println("total time: " + (endTime - startTime));
    	}
        
        {
        	startTime = System.currentTimeMillis();
        	p1.sort();
        	endTime = System.currentTimeMillis();
            System.out.println("sorted: " + p1.sorted());
    		System.out.println("total time: " + (endTime - startTime));
        }        
    }
}
