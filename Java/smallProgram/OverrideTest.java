package smallProgram;

/**
 * @author moshangcheng
 * @date 2011-3-16 下午11:05:34
 *
 * 类名的修饰符对其作用域的影响</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 * &nbsp;&nbsp    <b>Private     空       Protected   Public</b></br>
 * 同一类中的成员          <b>是                   是               是                   是</b></br>
 * 同一包中的成员          <b>否                   是               是                   是</b></br>
 * 不同包中的子类          <b>否                   否               是                   是</b></br>
 * 不同包的非子类          <b>否                   否               否                   是</b></br>
 */
class Parent {

	public static String say() {
		return "parent static say";
	}

	public String say2() {
		return "parent say";
	}
}

class Child extends Parent {
	public static String say() {
		return "child static say";
	}

	public String say2() {
		return "child say";
	}
}

/**
 * @author 子弹哥
 * 
 */
public class OverrideTest {

	public static void main(String[] args) {
		Parent p = new Child();
		System.out.println(p.say());
		System.out.println(p.say2());

	}

}
