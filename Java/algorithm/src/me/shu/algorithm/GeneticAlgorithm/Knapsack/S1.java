package me.shu.algorithm.GeneticAlgorithm.Knapsack;

//http://blog.csdn.net/wangqiuyun/article/details/8847307

import java.io.IOException;
import java.util.Random;

public class S1 {

	private int[] v = { 220, 208, 198, 192, 180, 180, 165, 162, 160, 158, 155,
			130, 125, 122, 120, 118, 115, 110, 105, 101, 100, 100, 98, 96, 95,
			90, 88, 82, 80, 77, 75, 73, 72, 70, 69, 66, 65, 63, 60, 58, 56, 50,
			30, 20, 15, 10, 8, 5, 3, 1 };// 物品价值
	private int[] b = { 80, 82, 85, 70, 72, 70, 66, 50, 55, 25, 50, 55, 40, 48,
			50, 32, 22, 60, 30, 32, 40, 38, 35, 32, 25, 28, 30, 22, 50, 30, 45,
			30, 60, 50, 20, 65, 20, 25, 30, 10, 20, 25, 15, 10, 10, 10, 4, 4,
			2, 1 };// 物品体积
	private int pb = 1000;// 背包容积

	private int LL; // 染色体长度
	private int scale;// 种群规模
	private int MAX_GEN; // 运行代数

	private int bestT;// 最佳出现代数
	private int bestLength; // 最佳编码价值
	private int[] bestTour; // 最佳编码

	// 初始种群，父代种群，行数表示种群规模，一行代表一个个体，即染色体，列表示染色体基因片段
	private int[][] oldPopulation;
	private int[][] newPopulation;// 新的种群，子代种群
	private int[] fitness;// 种群适应度，表示种群中各个个体的适应度

	private float[] Pi;// 种群中各个个体的累计概率
	private float Pc;// 交叉概率
	private float Pm;// 变异概率
	private int t;// 当前代数
	private Random random;

	// 种群规模，染色体长度,最大代数，交叉率，变异率
	public S1(int s, int l, int g, float c, float m) {
		scale = s;
		LL = l;
		MAX_GEN = g;
		Pc = c;
		Pm = m;
	}

	private void init() throws IOException {
		bestLength = 0;
		bestTour = new int[LL];
		bestT = 0;
		t = 0;

		newPopulation = new int[scale][LL];
		oldPopulation = new int[scale][LL];
		fitness = new int[scale];
		Pi = new float[scale];

		random = new Random(System.currentTimeMillis());
	}

	// 初始化种群
	void initGroup() {
		int k, i;
		for (k = 0; k < scale; k++)// 种群数
		{
			// 01编码
			for (i = 0; i < LL; i++) {
				oldPopulation[k][i] = random.nextInt(65535) % 2;
			}
		}
	}

	public int evaluate(int[] chromosome) {
		// 010110
		int vv = 0;
		int bb = 0;
		// 染色体，起始城市,城市1,城市2...城市n
		for (int i = 0; i < LL; i++) {
			if (chromosome[i] == 1) {
				vv += v[i];
				bb += b[i];
			}
		}
		if (bb > pb) {
			// 超出背包体积
			return 0;
		} else {
			return vv;
		}
	}

	// 计算种群中各个个体的累积概率，前提是已经计算出各个个体的适应度fitness[max]，作为赌轮选择策略一部分，Pi[max]
	void countRate() {
		int k;
		double sumFitness = 0;// 适应度总和

		int[] tempf = new int[scale];

		for (k = 0; k < scale; k++) {
			tempf[k] = fitness[k];
			sumFitness += tempf[k];
		}

		Pi[0] = (float) (tempf[0] / sumFitness);
		for (k = 1; k < scale; k++) {
			Pi[k] = (float) (tempf[k] / sumFitness + Pi[k - 1]);
		}
	}

	// 挑选某代种群中适应度最高的个体，直接复制到子代中
	// 前提是已经计算出各个个体的适应度Fitness[max]
	public void selectBestGh() {
		int k, i, maxid;
		int maxevaluation;

		maxid = 0;
		maxevaluation = fitness[0];
		for (k = 1; k < scale; k++) {
			if (maxevaluation < fitness[k]) {
				maxevaluation = fitness[k];
				maxid = k;
			}
		}

		if (bestLength < maxevaluation) {
			bestLength = maxevaluation;
			bestT = t;// 最好的染色体出现的代数;
			for (i = 0; i < LL; i++) {
				bestTour[i] = oldPopulation[maxid][i];
			}
		}

		// 复制染色体，k表示新染色体在种群中的位置，kk表示旧的染色体在种群中的位置
		copyGh(0, maxid);// 将当代种群中适应度最高的染色体k复制到新种群中，排在第一位0
	}

	// 复制染色体，k表示新染色体在种群中的位置，kk表示旧的染色体在种群中的位置
	public void copyGh(int k, int kk) {
		int i;
		for (i = 0; i < LL; i++) {
			newPopulation[k][i] = oldPopulation[kk][i];
		}
	}

	// 赌轮选择策略挑选
	public void select() {
		int k, i, selectId;
		float ran1;
		for (k = 1; k < scale; k++) {
			ran1 = (float) (random.nextInt(65535) % 1000 / 1000.0);
			// System.out.println("概率"+ran1);
			// 产生方式
			for (i = 0; i < scale; i++) {
				if (ran1 <= Pi[i]) {
					break;
				}
			}
			selectId = i;
			copyGh(k, selectId);
		}
	}

	public void evolution() {
		int k;
		// 挑选某代种群中适应度最高的个体
		selectBestGh();
		// 赌轮选择策略挑选scale-1个下一代个体
		select();
		float r;

		// 交叉方法
		for (k = 0; k < scale; k = k + 2) {
			r = random.nextFloat();// /产生概率
			// System.out.println("交叉率..." + r);
			if (r < Pc) {
				// System.out.println(k + "与" + k + 1 + "进行交叉...");
				OXCross(k, k + 1);// 进行交叉
			} else {
				r = random.nextFloat();// /产生概率
				// System.out.println("变异率1..." + r);
				// 变异
				if (r < Pm) {
					// System.out.println(k + "变异...");
					OnCVariation(k);
				}
				r = random.nextFloat();// /产生概率
				// System.out.println("变异率2..." + r);
				// 变异
				if (r < Pm) {
					// System.out.println(k + 1 + "变异...");
					OnCVariation(k + 1);
				}
			}

		}

	}

	// 两点交叉算子
	void OXCross(int k1, int k2) {
		int i, j, flag;
		int ran1, ran2, temp = 0;

		ran1 = random.nextInt(65535) % LL;
		ran2 = random.nextInt(65535) % LL;

		while (ran1 == ran2) {
			ran2 = random.nextInt(65535) % LL;
		}
		if (ran1 > ran2)// 确保ran1<ran2
		{
			temp = ran1;
			ran1 = ran2;
			ran2 = temp;
		}
		flag = ran2 - ran1 + 1;// 个数
		for (i = 0, j = ran1; i < flag; i++, j++) {
			temp = newPopulation[k1][j];
			newPopulation[k1][j] = newPopulation[k2][j];
			newPopulation[k2][j] = temp;
		}

	}

	// 多次对换变异算子
	public void OnCVariation(int k) {
		int ran1, ran2, temp;
		int count;// 对换次数
		count = random.nextInt(65535) % LL;

		for (int i = 0; i < count; i++) {

			ran1 = random.nextInt(65535) % LL;
			ran2 = random.nextInt(65535) % LL;
			while (ran1 == ran2) {
				ran2 = random.nextInt(65535) % LL;
			}
			temp = newPopulation[k][ran1];
			newPopulation[k][ran1] = newPopulation[k][ran2];
			newPopulation[k][ran2] = temp;
		}
	}

	public void solve() {
		int i;
		int k;

		// 初始化种群
		initGroup();
		// 计算初始化种群适应度，Fitness[max]
		for (k = 0; k < scale; k++) {
			fitness[k] = evaluate(oldPopulation[k]);
			// System.out.println(fitness[k]);
		}

		// 计算初始化种群中各个个体的累积概率，Pi[max]
		countRate();
		System.out.println("初始种群...");
		for (k = 0; k < scale; k++) {
			for (i = 0; i < LL; i++) {
				System.out.print(oldPopulation[k][i] + ",");
			}
			System.out.println();
			System.out.println("----" + fitness[k] + " " + Pi[k]);
		}
		// evolution();

		for (t = 0; t < MAX_GEN; t++) {
			evolution();
			// 将新种群newGroup复制到旧种群oldGroup中，准备下一代进化
			for (k = 0; k < scale; k++) {
				for (i = 0; i < LL; i++) {
					oldPopulation[k][i] = newPopulation[k][i];
				}
			}
			// 计算种群适应度
			for (k = 0; k < scale; k++) {
				fitness[k] = evaluate(oldPopulation[k]);
			}
			// 计算种群中各个个体的累积概率
			countRate();
		}

		System.out.println("最后种群...");
		for (k = 0; k < scale; k++) {
			for (i = 0; i < LL; i++) {
				System.out.print(oldPopulation[k][i] + ",");
			}
			System.out.println();
			System.out.println("---" + fitness[k] + " " + Pi[k]);
		}

		System.out.println("最佳编码出现代数：");
		System.out.println(bestT);
		System.out.println("最佳编码价值");
		System.out.println(bestLength);
		System.out.println("最佳编码：");
		for (i = 0; i < LL; i++) {
			System.out.print(bestTour[i] + ",");
		}

	}

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {
		System.out.println("Start....");
		S1 ga = new S1(20, 50, 500, 0.8f, 0.9f);
		ga.init();
		ga.solve();
	}
}
