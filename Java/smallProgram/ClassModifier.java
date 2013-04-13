package smallProgram;

/**
 * @author 子弹哥
 * 属性名的修饰符对其作用域的影响
 * <pre>
 *            	Private	 空   Protected Public
 * 同一类中的成员          是      是       是       是
 * 同一包中的成员          否      是       是       是
 * 不同包中的子类          否      否       是       是
 * 不同包的非子类          否      否       否       是
 * </pre>
 * 外部类只能用Public和Default修饰，内部类可以用static、pravite、public、protected、default等修饰。</br>
 */
public class ClassModifier {

    public static void main(String[] args) {
    }

}
