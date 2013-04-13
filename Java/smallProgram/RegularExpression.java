/**
 * 
 */
package smallProgram;

import java.util.Scanner;
import java.util.regex.Pattern;

/**
 * @author moshangcheng
 * @version 1.0
 */
public class RegularExpression {
	static {
		System.out.println("loaded");
	}
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.println("Please input the regular expression");
		while (in.hasNext()) {
			int testNumber;
			String regString = in.next();
			Pattern regPattern = Pattern.compile(regString);
			System.out.println("Please input the nubmer of test String");
			testNumber = in.nextInt();
			System.out.println("Please input test strings");
			for (int i = 0; i < testNumber; i++) {
				while (in.hasNext()) {
					String testString = in.next();
					if (regPattern.matcher(testString).find()) {
						System.out
								.println(testString + " matches " + regString);
					} else {
						System.out.println(testString + " doesn't match "
								+ regString);
					}
				}
			}
		}
	}
}
