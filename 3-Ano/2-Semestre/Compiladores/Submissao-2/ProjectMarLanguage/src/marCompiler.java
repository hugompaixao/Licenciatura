import Interpreter.marBaseListener;
import Interpreter.marLexer;
import Interpreter.marParser;

import com.company.DefPhase;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeProperty;
import org.antlr.v4.runtime.tree.ParseTreeWalker;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import SymbolTable.Symbol;
import java.util.Stack;


import Interpreter.marBaseListener;
import Interpreter.marParser;

import java.util.HashMap;

/*class Evaluator extends marBaseListener {
    HashMap<Integer, String> label = new HashMap<>();
    public static enum Type {Number, Boolean, String, Nil}
    String errors = "";
    String assembly;


    public void exitNUMBER( marParser.NUMBERContext ctx ) {
        label.put(ctx.getStart().getStartIndex(), "Number");
    }

    public void exitBOOL( marParser.BOOLContext ctx ) {
        label.put(ctx.getStart().getStartIndex(), "Boolean");
    }

    public void exitSTRING( marParser.STRINGContext ctx ) {
        label.put(ctx.getStart().getStartIndex(), "String");
    }

    public void exitNIL( marParser.NILContext ctx ) {
        label.put(ctx.getStart().getStartIndex(), "Nil");
    }

    public void exitUN(marParser.UNContext ctx) {
        String type = label.get(ctx.getStop().getStartIndex());
        if (!type.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "unary operator - is invalid for " + type + "\n";

        label.put(ctx.getStop().getStopIndex(), "Number");
    }

    //TODO: not bool = ctx.getStop().getStartIndex() / not (exp) = ctx.getStop().getStartIndex()-1
   /* public void exitNOT(marParser.NOTContext ctx) {
        String type = label.get(ctx.getStop().getStartIndex());
        if (!type.equals("Boolean"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator \"not\" is invalid for " + type + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitADD(marParser.ADDContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator + is invalid between " + type1 + " and " + type1 + "\n";
        else if ((!type1.equals("Number")) && (!type1.equals("String")))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator + is invalid for " + type1 + "and" + type2 + "\n";

        if (type1.equals("Number"))
            label.put(ctx.getStop().getStopIndex(), "Number");
        else
            label.put(ctx.getStop().getStopIndex(), "String");
    }

    public void exitSUB(marParser.SUBContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator - is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator - is invalid for " + type1 + "and" + type2 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Number");
    }

    public void exitMUL(marParser.MULContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator * is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator * is invalid for " + type1 + "and" + type2 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Number");
    }

    public void exitDIV(marParser.DIVContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator / is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator / is invalid for " + type1 + "and" + type2 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Number");
    }

    public void exitGT(marParser.GTContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator > is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator > is invalid for " + type1 + "and" + type2 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitLT(marParser.LTContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator < is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator < is invalid for " + type1 + "and" + type2 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitGEQ(marParser.GEQContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator >= is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator >= is invalid for " + type1 + "and" + type2 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitLEQ(marParser.LEQContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator <= is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Number"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator <= is invalid for " + type1 + "and" + type2 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitEQ(marParser.EQContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator > is invalid between " + type1 + " and " + type1 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitDIF(marParser.DIFContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator > is invalid between " + type1 + " and " + type1 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitAND(marParser.ANDContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator \"and\" is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Boolean"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator \"and\" is invalid between " + type1 + " and " + type1 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public void exitOR(marParser.ORContext ctx) {
        String type1 = label.get(ctx.getStart().getStartIndex());
        String type2 = label.get(ctx.getStop().getStartIndex());
        if (!type1.equals(type2))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator \"or\" is invalid between " + type1 + " and " + type1 + "\n";
        else if (!type1.equals("Boolean"))
            errors += "line " + ctx.stop.getLine() + ":" + ctx.stop.getCharPositionInLine() + " error" + ": " + "operator \"or\" is invalid between " + type1 + " and " + type1 + "\n";

        label.put(ctx.getStop().getStopIndex(), "Boolean");
    }

    public String getErrors() {
        return this.errors;
    }
}*/


class Compiler extends marBaseListener {
    DataOutputStream dataOutputStream;
    String assembly;
    String constant;
    ParseTreeProperty<Symbol.Type> exprType;
    int line;
    int constNum;
    int var;

    public Compiler(ParseTreeProperty<Symbol.Type> exprtype) throws IOException {
        this.dataOutputStream = new DataOutputStream(new FileOutputStream("test.marbc"));
        this.constant = "Constant pool:\n";
        this.assembly = "Generated assembly code:\n";
        this.exprType = exprtype;
        this.line = 0;
        this.constNum = 0;
        this.var = 0;
    }

    public void exitNUMBER( marParser.NUMBERContext ctx ){
        try {
            double value = Double.parseDouble(ctx.getText());
            dataOutputStream.write(0);
            dataOutputStream.writeDouble(value);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        this.constant += "<" + this.constNum + ": " + "NUMBER" + ' ' + Double.parseDouble(ctx.getText()) + ">" + '\n';
        this.constNum++;
        this.assembly += line + ": " + "CONST" + ' ' + this.var + '\n';
        this.var++;
        this.line++;
    }

    public void exitBOOL(marParser.BOOLContext ctx) {
        try {
            boolean value = Boolean.parseBoolean(ctx.getText());
            if (value) {
                dataOutputStream.write(9);
            } else {
                dataOutputStream.write(10);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        this.constant += "<" + this.constNum + ": " + "BOOL" + ' ' + (Boolean.parseBoolean(ctx.getText()) ? "True" : "False") + ">" + '\n';
        this.constNum++;
        this.assembly += line + ": " + this.var + '\n';
        this.var++;
        this.line++;
    }

    public void exitSTRING(marParser.STRINGContext ctx ){
        String value = ctx.STRING().getText();
        try {
            value = value.substring(1, value.length() - 1);
            dataOutputStream.write(-1);
            dataOutputStream.write(value.length());
            dataOutputStream.writeBytes(value);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        this.constant += "<" + this.constNum + ": " + "STRING" + ' ' + ctx.STRING().getText() + ">" + '\n';
        this.constNum++;
        this.assembly += line + ": " + "CONST" + ' ' + this.var + '\n';
        this.var++;
        this.line++;
    }

    public void exitNIL(marParser.NILContext ctx) {
        try {
            dataOutputStream.write(8);
            dataOutputStream.writeChars("nil");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        this.constant += "<" + this.constNum + ": " + "CONST" + ' ' + "Nil" + ">" + '\n';
        this.constNum++;
        this.assembly += line + ": "  + "NIL" + '\n';
        this.line++;
        this.var++;
    }

    public void exitADDSUB(marParser.ADDSUBContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        try {
            if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER)) {
                String op = String.valueOf(ctx.getChild(1));
                if (op.equals("+")) {
                    dataOutputStream.write(1);
                    assembly += line + ": " + "ADD" + '\n';
                } else {
                    dataOutputStream.write(2);
                    assembly += line + ": " + "SUB" + '\n';
                }
            }
            else if ((type1 == Symbol.Type.STRING) && (type2 == Symbol.Type.STRING)){
                dataOutputStream.write(6);
                assembly += line + ": "  + "CONCAT" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        line++;
    }

    public void exitMULDIV( marParser.MULDIVContext ctx ) {
        try {
            String op = String.valueOf(ctx.getChild(1));
            if (op.equals("*")) {
                dataOutputStream.write(3);
                assembly += line + ": " + "MUL" + '\n';
            }
            else {
                dataOutputStream.write(4);
                assembly += line + ": "  + "DIV" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        line++;
    }

    public void exitUNNOT( marParser.UNNOTContext ctx ){
        try {
            String op = String.valueOf(ctx.getChild(0));
            if (op.equals("-")) {
                dataOutputStream.write(5);
                assembly += line + ": "  + "UMINUS" + '\n';
            } else {
                dataOutputStream.write(13);
                assembly += line + ": "  + "NOT" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        line++;
    }

    public void exitAND(marParser.ANDContext ctx) {
        try {
            dataOutputStream.write(11);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        assembly += line + ": "  + "OR" + '\n';
    }

    public void exitOR(marParser.ORContext ctx) {
        try {
            dataOutputStream.write(12);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        assembly += line + ": "  + "OR" + '\n';
    }

    public void exitREL(marParser.RELContext ctx) {
        try {
            String op = String.valueOf(ctx.getChild(1));
            if (op.equals(">")) {
                dataOutputStream.write(14);
                assembly += line + ": "  + "GT" + '\n';
            } else if (op.equals("<")) {
                dataOutputStream.write(15);
                assembly += line + ": "  + "LT" + '\n';
            }else if (op.equals(">=")) {
                dataOutputStream.write(16);
                assembly += line + ": "  + "GEQ" + '\n';
            } else {
                dataOutputStream.write(17);
                assembly += line + ": "  + "LEQ" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        line++;
    }

    public void exitEQDIF(marParser.EQDIFContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression(0));
        try {
            String op = String.valueOf(ctx.getChild(1));
            if (op.equals("==")) {
                if (type == Symbol.Type.NUMBER){
                    dataOutputStream.write(18);
                    assembly += line + ": "  + "EQ_N" + '\n';
                }
                else if (type == Symbol.Type.BOOLEAN){
                    dataOutputStream.write(19);
                    assembly += line + ": "  + "EQ_B" + '\n';
                }
                else if (type == Symbol.Type.STRING){
                    dataOutputStream.write(20);
                    assembly += line + ": "  + "EQ_S" + '\n';
                }
                else{
                    dataOutputStream.write(21);
                    assembly += line + ": "  + "EQ_NIL" + '\n';
                }
            } else {
                if (type == Symbol.Type.NUMBER){
                    dataOutputStream.write(22);
                    assembly += line + ": "  + "DIF_N" + '\n';
                }
                else if (type == Symbol.Type.BOOLEAN){
                    dataOutputStream.write(23);
                    assembly += line + ": "  + "DIF_B" + '\n';
                }
                else if (type == Symbol.Type.STRING){
                    dataOutputStream.write(24);
                    assembly += line + ": "  + "DIF_S" + '\n';
                }
                else{
                    dataOutputStream.write(25);
                    assembly += line + ": "  + "DIF_NIL" + '\n';
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        line++;
    }

    public void exitPrint(marParser.PrintContext ctx){
        Symbol.Type type = exprType.get(ctx.expression());
        try {
            if (type == Symbol.Type.NUMBER){
                dataOutputStream.write(26);
                assembly += line + ": "  + "PRINT_N" + '\n';
            }
            else if (type == Symbol.Type.BOOLEAN){
                dataOutputStream.write(27);
                assembly += line + ": "  + "PRINT_B" + '\n';
            }
            else if (type == Symbol.Type.STRING){
                dataOutputStream.write(28);
                assembly += line + ": "  + "PRINT_S" + '\n';
            }
            else{
                dataOutputStream.write(29);
                assembly += line + ": "  + "PRINT_NIL" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        line++;
    }

    public String getConstant() {
        return this.constant;
    }

    public String getassembly() {
        return assembly;
    }
}

public class marCompiler {

    public static Symbol.Type getType(int tokenType) {
        switch ( tokenType ) {
            case marParser.NUMBER:  return Symbol.Type.NUMBER;
            case marParser.STRING: return Symbol.Type.STRING;
            case marParser.NIL: return Symbol.Type.NIL;
        }
        return Symbol.Type.NIL;
    }

    public static void error(Token t, String msg) {
        System.err.printf("line %d:%d %s\n", t.getLine(),
                t.getCharPositionInLine(), msg);
    }

    public static void main( String[] args ) throws IOException {
        String code = Files.readString(Paths.get("test.mar"));
        marLexer lexer = new marLexer(CharStreams.fromString(code));
        CommonTokenStream token = new CommonTokenStream(lexer);
        marParser parser = new marParser(token);
        parser.setBuildParseTree(true);
        ParseTree tree = parser.prog();
        ParseTreeWalker walker = new ParseTreeWalker();
        DefPhase def = new DefPhase();
        walker.walk(def, tree);
        Compiler comp = new Compiler(def.getExprType());
        walker.walk(comp, tree);
        // create next phase and feed symbol table info from def to ref phase
        String vm = comp.getConstant();
        vm += comp.getassembly();
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
