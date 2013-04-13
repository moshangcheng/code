package smallProgram.InnerClass;

/**
 * 
 * @author moshangcheng
 * @date 2011-3-17 下午08:03:40
 * @version 1.0
 * @description http://www.blogjava.net/RogerTwain/archive/2007/05/23/119456.html</br>
 * 1. 对一个静态成员类，去掉其声明中的“static”关键字，将其定义移入其外部类的静态方法或静态初始化代码段中就成为了局部静态成员类。</br>
 * 对一个成员类，将其定义移入其外部类的实例方法或实例初始化代码中就成为了局部成员类。</br>
 * 2. 局部静态成员类与静态成员类的基本特性相同。例如，都只能访问外部类的静态字段或方法，但不能访问外部类的实例字段和实例方法等。</br>
 * 3. 局部成员类与成员类的基本特性相同。例如，局部成员类实例必属于其外部类的一个实例，可通过OuterClass.this引用其外部类实例等。</br>
 * 4. 如示例代码所示，<b>局部类能且只能访问其所属代码段中的声明为final的局部变量。</b>为什么只能访问声明为final的局部变量呢？</br>
 * 我们知道，局部变量在其所属的代码段（譬如某个函数）执行完毕后就会被回收，而一个局部类的实例却可以在其类定义所属代码段执行完毕后依然存在，如果它可操控非final的局部变量，用户就可以通过该实例修改已不存在的局部变量，无意义。</br>
 * 5. 如示例代码所示，<b>内部类只在定义它的代码段中可见</b>，不能在它所属代码段之外的代码中使用；因此也就没有public/private/default权限修饰符（无意义）。</br>
 * 6. <b>不能以局部类形式定义一个接口。</b>局部类只在其所属代码段中可见，定义这样的接口无意义</br>
 * 7. 局部类大部分以匿名类的形式使用。</br> 
 *
 */
public class LocalClass {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

	private int instanceField;
	private static int staticField;

	//define a local member class in instance code block
	{
		int localVirable1 = 0;
		final int localVirable2 = 1;
		class Inner1 {			
			public Inner1() {
				//can access its outer class' field and method directly
				instanceField = 1;
				//use OuterClass.this to get its corresponding outer class instance
				LocalClass.this.instanceField = 1;

				//can not access the not final local virable in its containing code block
				//System.out.print(localVirable1);

				//can access the final local virable in its containing code block
				System.out.print(localVirable2);
			}
		}

		//local class can not have privilege modifier 
		/*public class inner2 {            
		}*/
	}

	// define a local static member class in static code block
	static {
		class Inner2 {
			public Inner2() {
				staticField = 1;
				//can not access instance field and method in a local static member class 
				//intanceField = 2;
			}
		}
	}

	public void intanceMethod() {
		//define a local class in its out class' instance method
		class Inner3 {
		}

		//local class is visible only in its containning code block
		//Outer.Inner2 inner2;
	}

	private static void staticMethod() {
		//define a local static member class in its out class' static method
		class Inner4 {
			public Inner4() {
				staticField = 2;
			}
		}

		//can not define a interface as a local class
		/*interface I {
		}*/
	}

}
