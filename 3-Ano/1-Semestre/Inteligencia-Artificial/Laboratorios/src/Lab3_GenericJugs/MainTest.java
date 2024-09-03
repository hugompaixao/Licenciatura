package Lab3_GenericJugs;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.Test;
import org.junit.jupiter.api.Timeout;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.concurrent.TimeUnit;

public class MainTest {
	private static final String[][] STDIO_TESTS = {
//			Sample 0:
			{ "023145678\r\n123405678\r\n", " 23\r\n145\r\n678\r\n\r\n123\r\n 45\r\n678\r\n\r\n123\r\n4 5\r\n678\r\n\r\n2\r\n" },
//			Sample 1:
			{ "023147685\r\n023147685\r\n", " 23\r\n147\r\n685\r\n\r\n0\r\n" },
//			Sample 2:
			{ "123046758\r\n123456780\r\n", "123\r\n 46\r\n758\r\n\r\n123\r\n4 6\r\n758\r\n\r\n123\r\n456\r\n7 8\r\n\r\n123\r\n456\r\n78 \r\n\r\n3\r\n" },
//			Sample 3:
			{ "123456708\r\n123456780\r\n", "123\r\n456\r\n7 8\r\n\r\n123\r\n456\r\n78 \r\n\r\n1\r\n" },
//			Sample 4:
			{ "123456078\r\n123456780\r\n", "123\r\n456\r\n 78\r\n\r\n123\r\n456\r\n7 8\r\n\r\n123\r\n456\r\n78 \r\n\r\n2\r\n" }, };

	private static final String[][] STDIO_TESTS2 = {
//			Sample 0:
//			{ "8 5 3\r\n8 0 0\r\n0 5 3\r\n", "2\r\n" },
//			Sample 1:
			{ "8 7 6 5 4 3 2 1\r\n0 0 0 0 4 3 2 1\r\n1 1 1 1 1 3 1 1\r\n", "8\r\n" },
//			Sample 2:
//			{ "21 13 8 5 3\r\n21 0 0 0 0\r\n6 4 4 4 3\r\n", "13\r\n" },
//			Sample 3:
//			{ "21 13 8 3\r\n21 0 0 0\r\n10 4 4 3\r\n", "12\r\n"}
	};

	@Test
	@Timeout(value = 50, unit = TimeUnit.MILLISECONDS)
	public void testMain0() {
		for (String[] test : STDIO_TESTS) {
			String input = test[0];
			String expected = test[1];
			ByteArrayOutputStream outputStream = setIOStreams(input);
			Main.main(null);
			assertEquals(expected, outputStream.toString());
		}
	}

	@Test
//	@Timeout(value = 150, unit = TimeUnit.MILLISECONDS)
	public void testMain1() {
		for (String[] test : STDIO_TESTS2) {
			String input = test[0];
			String expected = test[1];
			ByteArrayOutputStream outputStream = setIOStreams(input);
			Main.main(null);
			assertEquals(expected, outputStream.toString());
		}
	}


	private static ByteArrayOutputStream setIOStreams(String input) {
		System.setIn(new ByteArrayInputStream(input.getBytes()));
		ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
		PrintStream printStream = new PrintStream(outputStream);
		System.setOut(printStream);
		return outputStream;
	}
}