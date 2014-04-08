package me.shu.lang.java.boxing;

public class Performance {

	public static void main(String[] args) {
		
		long startTime = 0;
		long endTime = 0;
		
		{
			System.out.println("--- no autoboxing");
			startTime = System.currentTimeMillis();
			char v;
			for(int i = 0; i < 1000 * 1000 * 1000; i++)
			{
				v = (char)(i% 10 + 48);
			}
			endTime = System.currentTimeMillis();
			System.out.println("Total time: " + (endTime - startTime) * 1.0 / 1000);
		}
		
		{
			System.out.println("--- autoboxing");
			startTime = System.currentTimeMillis();
			Character v;
			for(int i = 0; i < 1000 * 1000 * 1000; i++)
			{
				v = (char)(i% 10 + 48);
			}
			endTime = System.currentTimeMillis();
			System.out.println("Total time: " + (endTime - startTime) * 1.0 / 1000);
		}

		{
			System.out.println("--- no autoboxing, char to float");
			startTime = System.currentTimeMillis();
			float v;
			for(int i = 0; i < 1000 * 1000 * 1000; i++)
			{
				v = (char)(i% 10 + 48);
			}
			endTime = System.currentTimeMillis();
			System.out.println("Total time: " + (endTime - startTime) * 1.0 / 1000);
		}
	}

}
