import java.io.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.Stack;
import java.io.*;

public class marVM{

    public static void run(byte[] bytecodes) {
        Stack<Object> stack = new Stack<>();
        int idx = 0;
        while (idx < bytecodes.length) {
            switch (bytecodes[idx]) {
                case -1 -> { //CONST_S
                    idx++;
                    byte size = bytecodes[idx++];
                    byte[] bytes = new byte[size];
                    System.arraycopy(bytecodes, idx, bytes, 0, size);
                    String strValue = new String(bytes);
                    stack.push(strValue);
                    idx +=size;
                }
                case 0 -> { //CONST
                    idx++;
                    byte[] bytes = new byte[8];
                    System.arraycopy(bytecodes, idx, bytes, 0, 8);
                    Double getValue = ByteBuffer.wrap(bytes).getDouble();
                    stack.push(getValue);
                    idx +=8;
                }
                case 1 -> { //ADD
                    double v2 = (double)stack.pop();
                    double v1 = (double)stack.pop();
                    stack.push(v1 + v2);
                    idx++;
                }
                case 2 -> { //SUB
                    double v2 = (double)stack.pop();
                    double v1 = (double)stack.pop();
                    stack.push(v1 - v2);
                    idx++;
                }
                case 3 -> { //MUL
                    double v2 = (double)stack.pop();
                    double v1 = (double)stack.pop();
                    stack.push(v1 * v2);
                    idx++;
                }
                case 4 -> { //DIV
                    double v2 = (double)stack.pop();
                    double v1 = (double)stack.pop();
                    stack.push(v1 / v2);
                    idx++;
                }
                case 5 -> { //UMINUS
                    double v1 = (double)stack.pop();
                    stack.push(-v1);
                    idx++;
                }
                case 6 -> { //CONCAT
                    Object v2 = stack.pop();
                    Object v1 = stack.pop();
                    stack.push(String.valueOf(v1).concat(String.valueOf(v2)));
                    idx++;
                }
                case 7 -> { //HALT
                    return;
                }
                case 8 -> { // NIL
                    idx++;
                    byte[] bytes = new byte[3];
                    System.arraycopy(bytecodes, idx, bytes, 0, 3);
                    stack.push(null);
                }
                case 9 -> { // TRUE
                    stack.push(true);
                    idx++;
                }
                case 10 -> { // FALSE
                    stack.push(false);
                    idx++;
                }
                case 11 -> { // AND
                    boolean v2 = (boolean) stack.pop();
                    boolean v1 = (boolean) stack.pop();
                    stack.push(v1 && v2);
                    idx++;
                }
                case 12 -> { // OR
                    boolean v2 = (boolean) stack.pop();
                    boolean v1 = (boolean) stack.pop();
                    stack.push(v1 || v2);
                    idx++;
                }
                case 13 -> { // NOT
                    boolean v1 = (boolean) stack.pop();
                    stack.push(!v1);
                    idx++;
                }
                case 14 -> { // GT
                    double v2 = (double) stack.pop();
                    double v1 = (double) stack.pop();
                    if (v1 > v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 15 -> { // LT
                    double v2 = (double) stack.pop();
                    double v1 = (double) stack.pop();
                    if (v1 < v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 16 -> { // GEQ
                    double v2 = (double) stack.pop();
                    double v1 = (double) stack.pop();
                    if (v1 >= v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 17 -> { // LEQ
                    double v2 = (double) stack.pop();
                    double v1 = (double) stack.pop();
                    if (v1 <= v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 18 -> { // EQ_N
                    double v2 = (double)stack.pop();
                    double v1 = (double)stack.pop();
                    if (v1 == v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 19 -> { // EQ_B
                    boolean v2 = (boolean)stack.pop();
                    boolean v1 = (boolean)stack.pop();
                    if (v1 == v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 20 -> { // EQ_S
                    String v2 = (String)stack.pop();
                    String v1 = (String)stack.pop();
                    if (v1.equals(v2))
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 21 -> { // EQ_NIL
                    Object v2 = stack.pop();
                    Object v1 = stack.pop();
                    if (v1 == null && v2 == null)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 22 -> { // NEQ_N
                    double v2 = (double)stack.pop();
                    double v1 = (double)stack.pop();
                    if (v1 != v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 23 -> { // NEQ_B
                    boolean v2 = (boolean)stack.pop();
                    boolean v1 = (boolean)stack.pop();
                    if (v1 != v2)
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 24 -> { // NEQ_S
                    String v2 = (String)stack.pop();
                    String v1 = (String)stack.pop();
                    if (!v1.equals(v2))
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 25 -> { // NEQ_NIL
                    Object v2 = stack.pop();
                    Object v1 = stack.pop();
                    if ((v1 == null && v2 != null) || (v1 != null && !v1.equals(v2)))
                        stack.push(true);
                    else
                        stack.push(false);
                    idx++;
                }
                case 26 -> { // PRINT_N
                    Object n = stack.pop();
                    System.out.println(n);
                    idx++;
                }
                case 27 -> { // PRINT_B
                    System.out.println(stack.pop());
                    idx++;
                }
                case 28 -> { // PRINT_S
                    String s = String.valueOf(stack.pop());
                    System.out.println(s);
                    idx++;
                }
                case 29 -> { // PRINT_NIL
                    stack.pop();
                    System.out.println("nil");
                    idx++;
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