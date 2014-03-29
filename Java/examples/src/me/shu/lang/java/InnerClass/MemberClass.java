package me.shu.lang.java.InnerClass;

/**
 * @author moshangcheng
 * @date 2011-3-17 下午02:37:00
 * @version 1.0
 * @description http://www.blogjava.net/RogerTwain/archive/2007/05/23/119456.html</br>
 * 1. 类似于外部类的实例函数，成员类有public/private/default权限修饰符。</br>
 * 2. <b>一个成员类实例必然所属一个外部类实例，成员类可访问外部类的任一个实例字段和实例函数。</b></br>
 * 3. <b>不能在成员类中定义static字段、方法和类（static final形式的常量定义除外）。</b>因为一个成员类实例必然与一个外部类实例关联，这个static定义完全可以移到其外部类中去。</br>
 * 4. <strong>成员类不能是接口（interface）。</strong>因为成员类必须能被某个外部类实例实例化，而接口是不能实例化的。</br>
 * 事实上，如示例代码所示，如果你以成员类的形式定义一个接口，该接口实际上是一个静态成员类，static关键字对inner interface是内含（implicit）的。</br>
 * 5. 一个成员类实例必然所属于其外部类的一个实例，那么如何在成员类内部获得其所属外部类实例呢？如示例代码所示，采用“OuterClass.this”的形式。</br>
 * 如果内部类中没有与外部类中同名的变量，可以直接用变量名访问。</br>
 * 外部类的静态方法访问内部类与在外部类外部访问成员类的方法一样，必须先建立外部类的实例。</br>
 * 6. 内部类实例可在其外部类的实例方法中创建，此新创建内部类实例所属的外部类实例自然就是创建它的外部类实例方法对应的外部类实例。</br>
 * 7. 另外，如示例代码所示，对于给定的一个外部类实例outerClass，可以直接创建其内部类实例，语法形式为：
 * <pre>OuterClass.InnerClass innerClass = outerClass.new InnerClass();</pre>
 * 8.<b> 成员类的显著特性就是成员类能访问它的外部类实例的任意字段与方法。</b>方便一个类对外提供一个公共接口的实现是成员类的典型应用。</br>
 *  以JDK Collection类库为例，每种Collection类必须提供一个与其对应的Iterator实现以便客户端能以统一的方式遍历任一Collection实例。每种Collection类的Iterator实现就被定义为该Collection类的成员类。</br>
 *  例如JDK中AbstractList类的代码片断：
 *  <pre>
 *  public abstract class AbstractList<E> extends AbstractCollection<E> implements List<E> {
 *  	private class Itr implements Iterator<E> {
 *  		………;
 *  	}
 *  	public Iterator<E> iterator() {
 *  		return new Itr();
 *  	}
 *  }
 *  </pre>
 *  9. 内部类也会产生这么一个.class文件，但是它的名称却不是内部类的类名，而是有着严格的限制：外围类的名字，加上$,再加上内部类名字。</br>
 *  方法内的内部类，不是在调用方法时生成，而是与外部类一同编译，就可以通过查看.class文件的方式来证明。</br>
 *  10. 每个内部类都能独立地继承一个接口，而无论外围类是否已经继承了某个接口。   因此，内部类使多重继承的解决方案变得更加完整。 </br>
 *   在项目中，需要多重继承，如果是两个接口，那么好办，接口支持多重继承。   如果是两个类呢？这时只有使用内部类了。</br>  
 * 
 */
public class MemberClass {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//cannot create member class instance directly in class other than outer class
		//Outer.Inner2 inner2 = new Outer.Inner2();

		//create a member class instance outside it's outer class
		MemberClass outer = new MemberClass();
		MemberClass.Inner1 inner1 = outer.new Inner1();

	}

	//just like instance method, member class has public/private/default access privilege levels
	private int data;
	private int sTest;

	//access privilege level: public 
	public class Inner1 {
		private int data;
		private int data1;

		public Inner1() {
			//member class can access its outer class' instance field directly
			data1 = 1;
			//itself data field
			data = 1;
			//its outer class instance field
			MemberClass.this.data = 1;
			//如果内部类中没有与外部类中同名的变量，可以直接用变量名访问
			sTest = 1;
		}
	}

	//access privilege level: default
	class Inner2 {
		//can not define static filed, method, class in member class
		//static int j = 1;

		//but, "static final" compound is allowed 
		static final int CONSTANT = 1;
	}

	//access privilege level: private 
	private class Inner3 {
		public class Inner4 {

		}
	}

	//in fact, Inner5 is not a member class but a static member class
	interface Inner5 {
	}

	private static void staticMethod() {
		//can not create a member class instance directly in outer class' static method
		//Inner1 inner1 = new Inner1();
	}

	private void instanceMethod() {
		//can create a member class instance in outer class' instance method
		Inner1 inner1 = new Inner1();
	}
}
