package TOJ;

import java.math.BigInteger;
import java.util.Scanner;

public class P2795 {
	public static int gcd(int a, int b) {
		int c = 0;
		if (a < b) {
			c = a;
			a = b;
			b = c;
		}
		while (b != 0) {
			c = a % b;
			a = b;
			b = c;
		}
		return a;
	}

	public static void main(String args[]) {
		BigInteger[] fac = new BigInteger[1001];
		int[] col = new int[1001];
		int n;
		Scanner cin = new Scanner(System.in);

		int t = cin.nextInt();
		BigInteger sum = new BigInteger("0");
		fac[1] = new BigInteger("1");
		for (int i = 2; i < 1001; i++)
			fac[i] = new BigInteger(fac[i - 1].multiply(BigInteger.valueOf(i))
					.toString());
		while (t-- != 0) {
			n = cin.nextInt();
			int nSum = 0;
			int totleGcd = 1;
			for (int i = 0; i < n; i++) {
				col[i] = cin.nextInt();
				totleGcd = gcd(col[i], totleGcd);
				nSum += col[i];
			}
			sum = BigInteger.ZERO;
			for (int i = totleGcd; i <= nSum; i += totleGcd) {
				BigInteger unit = new BigInteger("1");
				int sumHelp = 0;
				int g = gcd(i, nSum);
				g = nSum / g;
				for (int j = 0; j < n; j++)
					if (col[j] % g != 0) {
						unit = BigInteger.ZERO;
						break;
					} else {
						sumHelp += col[j] / g;
						unit = unit.multiply(fac[col[j] / g]);
					}
				if (unit.compareTo(BigInteger.ZERO) != 0)
					sum = sum.add(fac[sumHelp].divide(unit));
			}

			System.out.println(sum.divide(BigInteger.valueOf(nSum)));
		}

	}
}
