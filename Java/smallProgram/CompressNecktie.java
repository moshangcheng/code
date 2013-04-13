package smallProgram;

import java.io.IOException;

import net.coobird.thumbnailator.Thumbnails;



public class CompressNecktie {
	public static void main(String[] args) throws IOException {
		Thumbnails.of("0.png").scale(0.5).toFile("0-small.png");	
	}
}
