package me.shu.lang.java.InnerClass;

/**
 * @author moshangcheng
 * @date 2011-3-17 下午08:42:03
 * @version version
 * @description http://www.blogjava.net/RogerTwain/archive/2007/05/23/119456.html</br>
 * 1. 匿名类是一种特殊的局部类。局部类的特性与约束都适用与它。</br>
 * 2. <b>继承自某个基类的匿名类</b>
 * <pre>new class-name ( [ argument-list ] ) { class-body }</pre>
 * 创建匿名类实例时，“argument-list”将被传入其基类（即class-name）对应的构造函数。</br>
 * 3.<b> 实现某个接口的匿名类</b>
 * <pre>new interface-name () { class-body }</pre>
 * 4. 什么时候使用匿名类?该类定义代码段很短;只需要创建该类的一个实例;类的定义代码与类的使用代码紧邻;使用匿名不影响代码的易读性。</br>
 *<b> 譬如，如下实现类似与c的callback功能的代码就是匿名类的典型应用：</b>
 * <pre>
 * File f = new File("/src");      // The directory to list
 * // Now call the list() method with a single FilenameFilter argument
 * // Define and instantiate an anonymous implementation of FilenameFilter
 * // as part of the method invocation expression. 
 * String[] filelist = f.list(new FilenameFilter() {
 * 	public boolean accept(File f, String s) { 
 * 		return s.endsWith(".java"); 
 * }
 * }); // Don't forget the parenthesis and semicolon that end the method call!
 * </pre>
 */

public class AnonymousClass {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		AnonymousClass main = new AnonymousClass();
		main.instanceMethod();
	}

	public void instanceMethod() {
		//define a nonymous class which implements Action interface and creat an instance of it
		Action action = new Action() {
			public void doAction() {
				System.out.println("a simple anonymous class demo");
			}
		};
		action.doAction();

		//define a nonoymous class which extends BaseClass and create an instance of it
		new BaseClass(5) {
			public void printData() {
				System.out.println("data = " + getData());
			}
		}.printData(); //"data = 5" will be outputed
	}
}

interface Action {
	void doAction();
}

class BaseClass {
	int packageTest;
	private int data;

	public BaseClass(int data) {
		this.data = data;
	}

	public int getData() {
		return data;
	}

}
