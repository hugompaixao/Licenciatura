import Interpreter.marBaseListener;
import Interpreter.marLexer;
import Interpreter.marParser;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class marCompiler {

    public static class Evaluator extends marBaseListener {
        DataOutputStream dataOutputStream;
        String tmp;

        int line;

        public Evaluator() throws IOException {
            this.dataOutputStream = new DataOutputStream(new FileOutputStream("test.marbc"));
            this.tmp = "";
            this.line = 0;
        }

        public void exitDTYPE( marParser.DTYPEContext ctx ){
            try {
                double value = Double.parseDouble(ctx.getText());
                dataOutputStream.write(0);
                dataOutputStream.writeDouble(value);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": " + "DCONST" + ' ' +Double.parseDouble(ctx.getText()) + '\n';
            //System.out.println(line + ": " + "DCONST" + ' ' +Double.parseDouble(ctx.getText()));
            line++;
        }

        public void exitADD( marParser.ADDContext ctx ){
            try {
                dataOutputStream.write(1);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": "  + "ADD" + '\n';
            //System.out.println(line + ": "  + "ADD");
            line++;
        }
        public void exitSUB( marParser.SUBContext ctx ){
            try {
                dataOutputStream.write(2);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": "  + "SUB" + '\n';
            //System.out.println(line + ": "  + "SUB");
            line++;
        }

        public void exitMUL( marParser.MULContext ctx ) {
            try {
                dataOutputStream.write(3);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": "  + "MUL" + '\n';
            //System.out.println(line + ": "  + "MUL");
            line++;
        }

        public void exitDIV( marParser.DIVContext ctx ){
            try {
                dataOutputStream.write(4);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": "  + "DIV" + '\n';
            //System.out.println(line + ": "  + "DIV");
            line++;
        }

        public void exitUN( marParser.UNContext ctx ){
            try {
                dataOutputStream.write(5);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": "  + "UMINUS" + '\n';
            //System.out.println(line + ": "  + "UMINUS");
            line++;
        }

        public void exitPrint(marParser.PrintContext ctx){
            try {
                dataOutputStream.write(6);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": "  + "PRINT" + '\n';
            //System.out.println(line + ": "  + "PRINT");
            line++;
        }

        public void exitProg(marParser.ProgContext ctx){
            try {
                dataOutputStream.write(7);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tmp += line + ": "  + "HALT" + '\n';
            //System.out.println(line + ": "  + "PRINT");
            line++;
        }

        public String getTmp() {
            return tmp;
        }
    }

    public static void main( String[] args ) throws IOException {
        String code = Files.readString(Paths.get("test.mar"));
        marLexer lexer = new marLexer(CharStreams.fromString(code));
        CommonTokenStream token = new CommonTokenStream(lexer);
        marParser parser = new marParser(token);
        ParseTree tree = parser.prog();
        ParseTreeWalker walker = new ParseTreeWalker();
        Evaluator eval = new Evaluator();
        walker.walk(eval, tree);
        String vm = eval.getTmp();
        try {
            FileWriter writer = new FileWriter("vm.txt");
            writer.write(vm);
            writer.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
        }
        marVM.bytecodes("test.marbc");
    }
}