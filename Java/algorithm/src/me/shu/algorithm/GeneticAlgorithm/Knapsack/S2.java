package me.shu.algorithm.GeneticAlgorithm.Knapsack;

//http://www.cnblogs.com/BreezeDust/p/3352090.html

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

class Chromosome {
	String key;
	double f;
	double p;

	public Chromosome(String key, double f, double p) {
		this.key = key;
		this.f = f;
		this.p = p;
	}

	public Chromosome(Chromosome o) {
		this.key = o.key;
		this.f = o.f;
		this.p = o.p;
	}
}

public class S2 {
	public Map<String, Chromosome> SAVE = new HashMap<String, Chromosome>();
	public List<Chromosome> list;
	public double[][] B = { { 77, 92 }, { 22, 22 }, { 29, 87 }, { 50, 46 },
			{ 99, 90 } };
	private double M = 100;
	private int N = 5;

	public double toPhenotype(String key) { // 解码成表现型

		double count = 0;
		for (int i = 0; i < key.length(); i++) {
			double tmp = 0;
			if (key.charAt(i) == '1') {
				tmp += B[i][1];
			}
			count += tmp;
		}
		return count;
	}

	public void init(int n) { // 这里的初始化种族应该是随机的，这里为了简单起见，我随便给了一组
		SAVE.put("10000", new Chromosome("10000", 0, 0));
		SAVE.put("01100", new Chromosome("01100", 0, 0));
		SAVE.put("00001", new Chromosome("00001", 0, 0));
		SAVE.put("01010", new Chromosome("01010", 0, 0));

	}

	public String lunpandu() { // 轮盘赌
		double nowP = Math.random();
		Set<String> keySet = SAVE.keySet();
		Iterator it = keySet.iterator();
		double m = 0;
		while (it.hasNext()) {
			String key = (String) it.next();
			Chromosome o = SAVE.get(key);
			m += o.p;
			if (nowP <= m)
				return key;
		}
		return "";
	}

	public Chromosome selected() { // 选择
		Set<String> keySet = SAVE.keySet();
		Iterator it = keySet.iterator();
		double count = 0;
		Chromosome max = new Chromosome("-1", 0, 0);
		while (it.hasNext()) {
			String key = (String) it.next();
			Chromosome o = SAVE.get(key);
			count += o.f = toPhenotype(key);
			if (o.f > max.f)
				max = o;
		}
		it = keySet.iterator();
		while (it.hasNext()) {
			String key = (String) it.next();
			Chromosome o = SAVE.get(key);
			o.p = o.f / count;

			System.out.println(o.key + "    " + o.f + "   " + o.p);
		}
		list = new LinkedList<Chromosome>();
		for (int i = 0; i < 2; i++) {
			String seleKey = lunpandu();
			list.add(new Chromosome(SAVE.get(seleKey)));
			System.out.println("--->" + seleKey);
		}
		return max;
	}

	public void crossover() { // 交叉
		for (int i = 0; i < list.size() / 2; i++) {
			Chromosome o1 = list.get(i * 2);
			Chromosome o2 = list.get(i * 2 + 1);
			int index = (int) Math.round(1 + Math.random() * 2);
			String o11 = o1.key.substring(0, index);
			String o12 = o1.key.substring(index, o1.key.length());
			String o21 = o2.key.substring(0, index);
			String o22 = o2.key.substring(index, o1.key.length());
			System.out.println("|||| " + o11 + " | " + o12);
			System.out.println("|||| " + o21 + " | " + o22);
			o1.key = o11 + o22;
			o2.key = o21 + o12;
			System.out.println("|||| " + o1.key);
			System.out.println("|||| " + o2.key);
			long bianyi = Math.round(Math.random() * 10000);
			if (bianyi < 100)
				;

			if (hefa(o1.key) && SAVE.get(o1.key) == null)
				SAVE.put(o1.key, o1);
			if (hefa(o2.key) && SAVE.get(o2.key) == null)
				SAVE.put(o2.key, o2);
		}
	}

	public boolean hefa(String key) { // 是否满足h(x)
		double m = 0;
		for (int i = 0; i < N; i++) {
			if (key.charAt(i) == '1') {
				m += B[i][0];
			}
		}
		if (m <= M)
			return true;
		return false;
	}

	public void iteration(int n) { // 种群迭代
		for (int i = 0; i < n; i++) {
			System.out.println("=========" + (i + 1));
			Chromosome max = selected();
			if (max.f >= 133) {
				System.out.println("                [----" + max.key + "  "
						+ max.f + "  " + max.p + "-----]");
				break;
			}
			crossover();
		}

	}

	public static void main(String[] args) {
		S2 ts = new S2();
		ts.init(6);
		ts.iteration(510);

	}

}