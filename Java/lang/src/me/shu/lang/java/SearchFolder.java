package me.shu.lang.java;

import java.io.File;

public class SearchFolder {
	public static void main(String[] args) {
		File path = new File("E:\\巴贝\\图片");
		String[] subFolders = path.list();
		for (String str : subFolders) {
			File subFolder = new File(path.getAbsolutePath() + '\\' + str);
			if(subFolder.isFile()) {
				continue;
			}
			String[] imageList = subFolder.list();
			for (String imageName : imageList) {
				File image = new File(subFolder.getAbsolutePath() + '\\' + imageName);
				if(!image.getName().endsWith("php4")) {
					continue;
				}
				String originName = image.getName();
				int originId = 0;
				for (int i = 17; originName.charAt(i) <= '9'
						&& originName.charAt(i) >= '0'; i++) {
					originId = originId * 10 + originName.charAt(i) - '0';
				}
				int newId = originId + 250 * (Integer.valueOf(str) - 1) + 1;
				File newFile = new File(subFolder.getAbsolutePath() + '\\' + newId + ".png");
				image.renameTo(newFile);
			}
		}
	}
}
