package me.shu.exercise.drools.basic.join;

import java.util.Random;

import org.junit.Test;
import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;
import org.kie.api.runtime.rule.QueryResults;
import org.kie.api.runtime.rule.Variable;

public class JoinTest {

	@Test
	public void basicTest() {

		KieServices kieService = KieServices.Factory.get();
		KieContainer kieContainer = kieService.getKieClasspathContainer();
		KieSession kieSession = kieContainer
		        .newKieSession("basic-join-ksession");

		final int ITEM_COUNT = 10 * 1000;

		Random rand = new Random();
		for (int i = 0; i < ITEM_COUNT; i++) {
			kieSession.insert(new Item(rand.nextDouble() * 5,
			        rand.nextDouble() * 100));
		}

		{
			long start = System.currentTimeMillis();
			QueryResults queryResults = kieSession.getQueryResults("score",
			        new Object[] { 3.0, Variable.v });
			long end = System.currentTimeMillis();

			System.out.println("used time is " + (end - start)
			        + ", result size is " + queryResults.size());
		}

		{
			long start = System.currentTimeMillis();
			QueryResults queryResults = kieSession.getQueryResults("price",
			        new Object[] { 50.0, Variable.v });
			long end = System.currentTimeMillis();

			System.out.println("used time is " + (end - start)
			        + ", result size is " + queryResults.size());
		}

		{
			long start = System.currentTimeMillis();
			QueryResults queryResults = kieSession.getQueryResults(
			        "score and price", new Object[] { 3.0, 50.0 });
			long end = System.currentTimeMillis();

			System.out.println("used time is " + (end - start)
			        + ", result size is " + queryResults.size());
		}
	}

}
