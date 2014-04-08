package me.shu.lang.java8.CountedCompleter;

import java.util.concurrent.CountedCompleter;
import java.util.concurrent.ForkJoinPool;
import java.util.function.Consumer;

class ForEach<E> extends CountedCompleter<Void> {
	private static final long serialVersionUID = 2812565779476185953L;

	public static <E> void forEach(E[] array, Consumer<? super E> op) {
		new ForEach<E>(null, array, op, 0, array.length).invoke();
	}

	final E[] array;
	final Consumer<? super E> op;
	final int lo, hi;

	ForEach(CountedCompleter<?> p, E[] array, Consumer<? super E> op, int lo, int hi) {
		super(p);
		this.array = array;
		this.op = op;
		this.lo = lo;
		this.hi = hi;
	}

	public void compute() { // version 1
		if (hi - lo >= 2) {
			int mid = (lo + hi) >>> 1;
			setPendingCount(2); // must set pending count before fork
			new ForEach<E>(this, array, op, mid, hi).fork(); // right child
			new ForEach<E>(this, array, op, lo, mid).fork(); // left child
		} else if (hi > lo)
			op.accept(array[lo]);
		tryComplete();
	}

	public static void main(String[] args) {
		Integer[] intArray = { 1, 2, 3, 4, 5, 6, 7, 8 };
		
		{
			System.out.println("--- use common pool to run");
			// use deafult pool
			ForEach.forEach(intArray, System.out::println);
			System.out.println();
		}
		
		{
			System.out.println("--- use custom pool to run");
			ForkJoinPool fjPool = new ForkJoinPool();
        	fjPool.invoke(new ForEach<Integer>(null, intArray, System.out::println, 0, intArray.length));
		}
	}
}