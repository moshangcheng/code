package smallProgram;

/**
 * @author moshangcheng
 * @date 2011-3-16 下午11:10:14
 * @version 1.0
 * @description http://www.javaeye.com/topic/943647
**/

public class fallibleKnowledge {

	public static void main(String[] args) {

	}

	/**
	 * @author moshangcheng
	 * @date 2011-3-16 下午11:14:16
	 * @version version
	 * @description
	 * 1.String.equals()方法比较的是字符串的内容,所以(x + y).equals(z)为true.</br>
	 * 2.“==”比较的是 String 实例的引用,很明显 a 和z 并不是同一个 String 实例,所以(a == z)为false.</br>
	 * 3.根据常量池的知识，容易得知(x == "hello")和(a == "hello" + "world")都为true.(常量池指的是在编译期被确定并被保存在已编译的.class 文件中的一些数据。它包含了关于方法、类、接口等，当然还有字符串常量的信息。也就是所谓的持久代。)</br>
	 * 4.x+y使用StringBuffer作为结果容器，所以a与StringBuffer不相等。
	 **/
	void testString() {
		String x = "hello";
		String y = "world";
		String z = new String("helloworld");
		String a = "helloworld";
		System.out.println("x+y equals z:" + (x + y).equals(z));
		System.out.println("a == z:" + (a == z));
		System.out.println("x == hello:" + (x == "hello"));
		System.out.println("a == helloworld:" + (a == "hello" + "world"));
		System.out.println("a == x+y:" + (a == (x + y)));
	}
	
	void testOvveride() {
		
	}
}
