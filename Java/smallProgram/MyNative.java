package smallProgram;

public class MyNative {
	public void showInfo() {
		dynamicInfo();
	}

	private native void dynamicInfo();

	static {
		System.loadLibrary("dynamicLib");
	}
}
