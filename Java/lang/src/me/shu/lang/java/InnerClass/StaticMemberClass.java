package me.shu.lang.java.InnerClass;

/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-17 下午02:14:53
 * @description http://www.blogjava.net/RogerTwain/archive/2007/05/23/119456.html</br>
 * 1. 静态成员类可访问外部类的任一静态字段或静态方法</br>
 * 2. 像静态方法或静态字段一样，静态成员类有public/private/default权限修饰符</br>
 * 3. 像外部类的静态方法一样，不能直接访问外部类的实例字段和实例方法</br>
 * 4. <b>静态成员类只能定义于外部类的顶层代码或外部类其它静态成员类的顶层代码中（嵌套定义）；不能定义于外部类的某个函数中。</b></br>
 * 5. 如示例代码所示，可以以“OuterClass.InnerClass”的方式来引用某个内部类。</br>
 * 6. B为A的辅助类，且只为A所用时，可将B定义为A的静态成员类。例如JDK中的LinkedList类就有Entry静态成员类:
 * <pre>
 * public class LinkedList<E> extends AbstractSequentialList<E> {
 * 	…;
 * 	private static class Entry<E> {
 * 		E element;
 * 		Entry<E> next;
 * 		Entry<E> previous;
 * 
 * 		Entry(E element, Entry<E> next, Entry<E> previous) {
 * 			this.element = element;
 * 			this.next = next;
 * 			this.previous = previous;
 * 		}
 * 	}
 * 	…;
 * }</pre>
 *
 */
public class StaticMemberClass {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		StaticMemberClass.Inner1 inner1 = new StaticMemberClass.Inner1();
		StaticMemberClass.Inner2 inner2 = new StaticMemberClass.Inner2();
	}

	//just like static method, static member class has public/private/default access privilege levels

	//access privilege level: public 
	public static class Inner1 {
		public Inner1() {
			//Static member inner class can access static method of outer class
			staticMethod();
		}
	}

	//access privilege level: default 
	static class Inner2 {

	}

	//access privilege level: private 
	private static class Inner3 {
		//define a nested inner class in another inner class 
		public static class Inner4 {
		}
	}

	private static void staticMethod() {
		//cannot define an inner class in a method
//		public static class Inner4() {
//		}
	}

	private void instanceMethod() {
		//private static member class can be accessed only in its outer class definition scope
		Inner3 inner3 = new Inner3();
		//how to use nested inner class
		Inner3.Inner4 inner4 = new Inner3.Inner4();
	}

}
