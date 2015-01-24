package me.shu.exercise.java.gc;

import java.lang.management.ManagementFactory;
import java.lang.management.RuntimeMXBean;
import java.util.List;

import org.junit.Test;

/**
 * 
 * @author moshangcheng
 *
 */
public class GCTest {

	@Test
	public void printVMFlagsTest() {
		RuntimeMXBean runtimeMxBean = ManagementFactory.getRuntimeMXBean();
		List<String> arguments = runtimeMxBean.getInputArguments();
		System.out.println(arguments);
	}

	@Test
	public void gcTest() throws InterruptedException {
		
		final int COUNT = 1000 * 1000;
		
		while(true) {

			int[] intArray = new int[1000 * 1000];
			
			Thread.sleep(10);
		}
			
	}
}
