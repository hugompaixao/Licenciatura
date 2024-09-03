import java.io.*;
import java.nio.ByteBuffer;
import java.util.Stack;

public class marVM {

    public static void run(byte[] bytecodes) {
        Stack<Double> stack = new Stack<>();
        int idx = 0;
        double v1, v2;
        while (idx < bytecodes.length) {
            switch (bytecodes[idx]) {
                // DCONST
                case 0 -> {
                    idx++;
                    byte[] bytes = new byte[8];
                    System.arraycopy(bytecodes, idx, bytes, 0, 8);
                    double getValue = ByteBuffer.wrap(bytes).getDouble();
                    stack.push(getValue);
                    idx +=8;
                }
                // ADD
                case 1 -> {
                    v1 = stack.pop();
                    v2 = stack.pop();
                    stack.push(v1 + v2);
                    idx++;
                }
                // SUB
                case 2 -> {
                    v1 = stack.pop();
                    v2 = stack.pop();
                    stack.push(v2 - v1);
                    idx++;
                }
                // MUL
                case 3 -> {
                    v1 = stack.pop();
                    v2 = stack.pop();
                    stack.push(v1 * v2);
                    idx++;
                }
                // DIV
                case 4 -> {
                    v1 = stack.pop();
                    v2 = stack.pop();
                    stack.push(v1 / v2);
                    idx++;
                }
                // UMINUS
                case 5 -> {
                    v1 = stack.pop();
                    stack.push(-v1);
                    idx++;
                }
                // PRINT
                case 6 -> {
                    System.out.println(stack.pop());
                    idx++;
                }
                // HALT
                case 7 -> {
                    return;
                }
                default -> throw new RuntimeException("Invalid opcode: " + bytecodes[idx]);
            }
        }
    }

    public static void bytecodes(String fileName) throws IOException {
        FileInputStream file = new FileInputStream(fileName);
        DataInputStream dataInputStream = new DataInputStream(file);
        byte[] bytecodes = dataInputStream.readAllBytes();
        run(bytecodes);
    }
}