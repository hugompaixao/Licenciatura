package com.company;

import Interpreter.marBaseListener;
import Interpreter.marLexer;
import Interpreter.marParser;
import SymbolTable.Scope;
import SymbolTable.Symbol;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeProperty;
import org.antlr.v4.runtime.tree.ParseTreeWalker;

import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Queue;
import java.util.Stack;

class Compiler extends marBaseListener {
    String assemblyCode, constantPool;
    DataOutputStream dataOutputStream;
    HashMap<String, Integer> variables = new HashMap<>();
    HashMap<String, Integer> methods = new HashMap<>();
    ParseTreeProperty<Symbol.Type> exprType;
    HashMap< Integer, Queue<Integer>> jumpaddr = new HashMap<>();
    Stack<Integer> locals = new Stack<>();
    int lineNum, constNum;
    boolean return_3 = false, first = true;
    int tmp, local = 0, arg = 0, return_, return_2;


    public Compiler(ParseTreeProperty<Symbol.Type> exprtype, HashMap< Integer, Queue<Integer>> jumpaddr ) throws IOException {
        this.dataOutputStream = new DataOutputStream(new FileOutputStream("test.marbc"));
        this.constantPool = "Constant pool:\n";
        this.assemblyCode = "Generated assembly code:\n";
        this.exprType = exprtype;
        this.lineNum = 0;
        this.constNum = 0;
        this.jumpaddr = jumpaddr;
    }

    @Override
    public void enterProg(marParser.ProgContext ctx) {
        //int globals = ctx.variable().size();
        try {
            dataOutputStream.write(30);
            int count = 0;
            for (int i = 0; i<ctx.variable().size(); i++){
                if (ctx.variable(i).type() != null){
                    variables.put(ctx.variable(i).ID().toString(), count++);
                }
            }
            for (int j = 0; j<ctx.instructions().variable().size(); j++){
                if (ctx.instructions().variable(j).type() != null){
                    variables.put(ctx.instructions().variable(j).ID().toString(), count++);
                }            }
            dataOutputStream.writeInt(count);
            assemblyCode += lineNum + ": "  + "Global" +  ' ' + count + '\n';
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void exitProg( marParser.ProgContext ctx ) {
        assemblyCode += lineNum + ":" + " " + "HALT";
    }

    /*TODO ----------------------------------------------------------------*/
    @Override
    public void enterMethod(marParser.MethodContext ctx) {
        if (first){
            first = false;
            assemblyCode += lineNum + ":" + " " + "JUMP" + "\n";
        }
        try {
            return_2 = ctx.argument().size();
            local++;
            dataOutputStream.write(33);
            dataOutputStream.writeInt(jumpaddr.get(ctx.depth()).poll()+1);
            dataOutputStream.write(35);
            dataOutputStream.writeInt(ctx.bloc().instructions().variable().size());//fim do metodo
            methods.put(ctx.ID().toString(), dataOutputStream.size());
            for (int i = 0, j = -ctx.argument().size(); i < ctx.argument().size(); i++, j++){
                variables.put(ctx.argument(i).ID().toString() + "l", j);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void exitMethod(marParser.MethodContext ctx) {
        try {
            local--;
            if (!return_3){
                int local = locals.pop();
                /*dataOutputStream.write(36);
                dataOutputStream.writeInt(local-1);*/
                int count = 0;
                for (int i = 0; i < ctx.bloc().instructions().variable().size(); i++){
                    if (ctx.bloc().instructions().variable(i).type() != null)
                        count++;
                }
                dataOutputStream.write(8);
                dataOutputStream.write(42);
                dataOutputStream.writeInt(count);
                dataOutputStream.writeInt(return_2);
            }
            return_3 = false;

            /*else {
                local = 0;
            }*/
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void enterBloc(marParser.BlocContext ctx) {
        //System.out.println(ctx.parent.parent.getRuleIndex());
        try {
            if (ctx.parent.getRuleIndex() == 1) {
                for (int i = 0; i < ctx.instructions().variable().size(); i++){
                    if (ctx.instructions().variable(i).type() !=null){
                        variables.put(ctx.instructions().variable(i).ID().toString() + "l", local++ + 1);
                        //dataOutputStream.writeInt(local++);
                    }
                }
            }
            else{
                for (int i = 0; i < ctx.instructions().variable().size(); i++){
                    if (ctx.instructions().variable(i).type() !=null){
                        variables.put(ctx.instructions().variable(i).ID().toString() + "l", local++);
                        //dataOutputStream.writeInt(local++);
                    }

                }
            }
            /*if (ctx.parent.parent.getRuleIndex() != 3){
                local = 0;
            }*/
            //System.out.println(ctx.parent.getRuleIndex());
            if (ctx.parent.getRuleIndex() == 8) {
                dataOutputStream.write(34);
                dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()));
            }
            else if (ctx.parent.getRuleIndex() == 7) {
                dataOutputStream.write(34);
                dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()) + 1);
            }
            int count = 0;
            for (int i = 0; i < ctx.instructions().variable().size(); i++){
                if (ctx.instructions().variable(i).type() != null){
                    count++;
                }
            }
            locals.push(count);
            dataOutputStream.write(35);
            dataOutputStream.writeInt(count);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


    @Override
    public void exitBloc(marParser.BlocContext ctx) {
        try {
            for (int i = 0; i < ctx.instructions().variable().size(); i++){
                if (ctx.instructions().variable(i).type() !=null){
                    local--;
                    //dataOutputStream.writeInt(local++);
                }

            }
            //System.out.println(ctx.parent.getRuleIndex());
            if (ctx.parent.getRuleIndex() != 1 && ctx.parent.getRuleIndex() != 8 && ctx.parent.getRuleIndex() != 9){
                dataOutputStream.write(36);
                dataOutputStream.writeInt(locals.pop());
            }
            // }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /*TODO ----------------------------------------------------------------*/
    @Override
    public void enterInstructions(marParser.InstructionsContext ctx) {}

    @Override
    public void exitInstructions(marParser.InstructionsContext ctx) {}

    @Override
    public void exitMethod_call(marParser.Method_callContext ctx) {
        try {
            //local++;
            dataOutputStream.write(41);
            dataOutputStream.writeInt(ctx.expression().size());
            //dataOutputStream.writeInt(dataOutputStream.size());
            dataOutputStream.writeInt(methods.get(ctx.ID().toString()));
            arg = 0;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

  /*@Override
    public void exitMethod_call(marParser.Method_callContext ctx) {

  }*/

    @Override
    public void enterMETHCALL( marParser.METHCALLContext ctx ) {
        assemblyCode += lineNum++ + ":" + " " + "CALL" + "\n";
    }

    @Override
    public void enterArgument(marParser.ArgumentContext ctx) {
        /*try {
            dataOutputStream.write(33);
            dataOutputStream.writeInt(jumpaddr.get(ctx.depth()).poll());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }*/
    }

    @Override
    public void enterReturn(marParser.ReturnContext ctx) {
            try {
                if (ctx.parent.getRuleIndex() == 8) {
                    dataOutputStream.write(34);
                    dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()));
                }
                else if (ctx.parent.getRuleIndex() == 7) {
                    dataOutputStream.write(34);
                    dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()) + 1);
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
    }

    @Override
    public void exitReturn(marParser.ReturnContext ctx) {
        try {
            dataOutputStream.write(42);
            if (locals.size() != 0) {
                return_ = locals.pop();//começo do metodo
            }
            dataOutputStream.writeInt(return_);
            dataOutputStream.writeInt(return_2);

            //começo do metodo
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return_3 = true;
    }

    @Override
    public void enterWhile(marParser.WhileContext ctx) {
        tmp = dataOutputStream.size();
    }

    @Override
    public void exitWhile(marParser.WhileContext ctx) {
        try {
            dataOutputStream.write(33);
            dataOutputStream.writeInt(tmp);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void enterIf( marParser.IfContext ctx ) {
        lineNum++;
    }

    @Override
    public void exitIf(marParser.IfContext ctx) {
    }

    @Override
    public void enterElse(marParser.ElseContext ctx) {
        try {
            dataOutputStream.write(33);
            dataOutputStream.writeInt(jumpaddr.get(ctx.depth()-1).poll());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        //lineNum++;
    }


    @Override
    public void exitPrint(marParser.PrintContext ctx){
        Symbol.Type type = exprType.get(ctx.expression());
        try {
            if (type == Symbol.Type.NUMBER){
                dataOutputStream.write(26);
                assemblyCode += lineNum + ": "  + "PRINT_N" + '\n';
            }
            else if (type == Symbol.Type.BOOLEAN){
                dataOutputStream.write(27);
                assemblyCode += lineNum + ": "  + "PRINT_B" + '\n';
            }
            else if (type == Symbol.Type.STRING){
                dataOutputStream.write(28);
                assemblyCode += lineNum + ": "  + "PRINT_S" + '\n';
            }
            else{
                dataOutputStream.write(29);
                assemblyCode += lineNum + ": "  + "PRINT_NIL" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void enterVariable(marParser.VariableContext ctx) {
        try {
            if (ctx.parent.getRuleIndex() == 8) {
                dataOutputStream.write(34);
                dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()));
            }
            else if (ctx.parent.getRuleIndex() == 7) {
                dataOutputStream.write(34);
                dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()) + 1);
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void exitVariable(marParser.VariableContext ctx) {
        try {
            if (ctx.ASSIGN() != null){
                if (ctx.parent.getRuleIndex() == 0 || (ctx.parent.getRuleIndex() == 4 && ctx.parent.parent.getRuleIndex() == 0)) {
                    //System.out.println(ctx.ID());
                    dataOutputStream.write(38);
                    dataOutputStream.writeInt(variables.get(ctx.ID().toString()));
                }
                else {
                    dataOutputStream.write(40);
                    dataOutputStream.writeInt(variables.get(ctx.ID().toString() + "l"));
                }
                assemblyCode += lineNum + ": "  + "STORE" + " " +variables.get(ctx.ID().toString()) + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        if (ctx.ASSIGN() != null)
            lineNum++;
    }

    @Override
    public void exitUNNOT(marParser.UNNOTContext ctx ){
        try {
            String op = String.valueOf(ctx.getChild(0));
            if (op.equals("-")) {
                dataOutputStream.write(5);
                assemblyCode += lineNum + ": "  + "UMINUS" + '\n';
            } else {
                dataOutputStream.write(13);
                assemblyCode += lineNum + ": "  + "NOT" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void exitMULDIV( marParser.MULDIVContext ctx ) {
        try {
            String op = String.valueOf(ctx.getChild(1));
            if (op.equals("*")) {
                dataOutputStream.write(3);
                assemblyCode += lineNum + ": " + "MUL" + '\n';
            }
            else {
                dataOutputStream.write(4);
                assemblyCode += lineNum + ": "  + "DIV" + '\n';
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void exitADDSUB(marParser.ADDSUBContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        try {
            if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER)) {
                String op = String.valueOf(ctx.getChild(1));
                if (op.equals("+")) {
                    dataOutputStream.write(1);
                    assemblyCode += lineNum + ": " + "ADD" + '\n';
                } else {
                    dataOutputStream.write(2);
                    assemblyCode += lineNum + ": " + "SUB" + '\n';
                }
            }
            else if ((type1 == Symbol.Type.STRING) && (type2 == Symbol.Type.STRING)){
                dataOutputStream.write(6);
                assemblyCode += lineNum + ": "  + "CONCAT" + '\n';
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void exitREL(marParser.RELContext ctx) {
        try {
            String op = String.valueOf(ctx.getChild(1));
            switch (op) {
                case ">" -> {
                    dataOutputStream.write(14);
                    assemblyCode += lineNum + ": " + "GT" + '\n';
                }
                case "<" -> {
                    dataOutputStream.write(15);
                    assemblyCode += lineNum + ": " + "LT" + '\n';
                }
                case ">=" -> {
                    dataOutputStream.write(16);
                    assemblyCode += lineNum + ": " + "GEQ" + '\n';
                }
                default -> {
                    dataOutputStream.write(17);
                    assemblyCode += lineNum + ": " + "LEQ" + '\n';
                }
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void exitEQDIF(marParser.EQDIFContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression(0));
        try {
            String op = String.valueOf(ctx.getChild(1));
            if (op.equals("==")) {
                if (type == Symbol.Type.NUMBER){
                    dataOutputStream.write(18);
                    assemblyCode += lineNum + ": "  + "EQ_N" + '\n';
                }
                else if (type == Symbol.Type.BOOLEAN){
                    dataOutputStream.write(19);
                    assemblyCode += lineNum + ": "  + "EQ_B" + '\n';
                }
                else if (type == Symbol.Type.STRING){
                    dataOutputStream.write(20);
                    assemblyCode += lineNum + ": "  + "EQ_S" + '\n';
                }
                else{
                    dataOutputStream.write(21);
                    assemblyCode += lineNum + ": "  + "EQ_NIL" + '\n';
                }
            } else {
                if (type == Symbol.Type.NUMBER){
                    dataOutputStream.write(22);
                    assemblyCode += lineNum + ": "  + "DIF_N" + '\n';
                }
                else if (type == Symbol.Type.BOOLEAN){
                    dataOutputStream.write(23);
                    assemblyCode += lineNum + ": "  + "DIF_B" + '\n';
                }
                else if (type == Symbol.Type.STRING){
                    dataOutputStream.write(24);
                    assemblyCode += lineNum + ": "  + "DIF_S" + '\n';
                }
                else{
                    dataOutputStream.write(25);
                    assemblyCode += lineNum + ": "  + "DIF_NIL" + '\n';
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        lineNum++;
    }

    @Override
    public void exitAND(marParser.ANDContext ctx) {
        try {
            dataOutputStream.write(11);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        assemblyCode += lineNum + ": "  + "AND" + '\n';
        lineNum++;
    }

    @Override
    public void exitOR(marParser.ORContext ctx) {
        try {
            dataOutputStream.write(12);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        assemblyCode += lineNum + ": "  + "OR" + '\n';
        lineNum++;
    }

    @Override
    public void enterVAR(marParser.VARContext ctx) {
        try {
            if (ctx.parent.getRuleIndex() == 8) {
                dataOutputStream.write(34);
                dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()));
            }
            else if (ctx.parent.getRuleIndex() == 7) {
                dataOutputStream.write(34);
                dataOutputStream.writeInt((jumpaddr.get(ctx.depth()-1).poll()) + 1);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void exitVAR(marParser.VARContext ctx) {
        try {
            //System.out.println(ctx.depth());
            /*if (ctx.depth() <= 4){

            }
            else*/ if (variables.get(ctx.ID().toString()) != null/* && ctx.parent.getRuleIndex() == 0 || ctx.depth() <= 4*/){
                dataOutputStream.write(37);
                dataOutputStream.writeInt(variables.get(ctx.ID().toString()));
            }
            else {
                dataOutputStream.write(39);
                //System.out.println(ctx.ID().toString() + " VAR");
                dataOutputStream.writeInt(variables.get(ctx.ID().toString()+ "l") );
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void exitNUMBER( marParser.NUMBERContext ctx ){
        try {
            double value = Double.parseDouble(ctx.getText());
            dataOutputStream.write(0);
            dataOutputStream.writeDouble(value);

            // System.out.println(ctx.parent.getRuleIndex());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        constantPool += "<" + constNum + ": " + "NUMBER" + ' ' + Double.parseDouble(ctx.getText()) + ">" + '\n';
        assemblyCode += lineNum + ": " + "CONST" + ' ' + constNum + '\n';
        lineNum++;
        constNum++;
    }

    @Override
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
        assemblyCode += lineNum + ": " + (Boolean.parseBoolean(ctx.getText()) ? "TRUE" : "FALSE") + '\n';
        lineNum++;
    }

    @Override
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
        constantPool += "<" + this.constNum + ": " + "STRING" + ' ' + ctx.STRING().getText() + ">" + '\n';
        assemblyCode += lineNum + ": " + "CONST" + ' ' + constNum + '\n';
        lineNum++;
        constNum++;
    }

    @Override
    public void exitNIL(marParser.NILContext ctx) {
        try {
            dataOutputStream.write(8);

            dataOutputStream.writeChars("nil");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        constantPool += "<" + constNum + ": " + "CONST" + ' ' + "Nil" + ">" + '\n';
        assemblyCode += lineNum + ": "  + "NIL" + '\n';
        lineNum++;
        constNum++;
    }

    public String getConstantPool() {
        return this.constantPool;
    }

    public String getAssemblyCode() {
        return assemblyCode;
    }
}

public class marCompiler {

    public static Symbol.Type getType(int tokenType) {
        return switch (tokenType) {
            case marParser.K_VOID -> Symbol.Type.VOID;
            case marParser.K_NUMBER -> Symbol.Type.NUMBER;
            case marParser.K_STRING -> Symbol.Type.STRING;
            case marParser.K_BOOL -> Symbol.Type.BOOLEAN;
            case marParser.K_NIL -> Symbol.Type.NIL;
            default -> Symbol.Type.INVALID;
        };
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
        String errors = def.getErrors();
        if (errors.equals("")) {
            Compiler comp = new Compiler(def.getExprType(), def.getJumps());
            //System.out.println(def.getJumpAddr());
            walker.walk(comp, tree);
            String vm = comp.getConstantPool();
            vm += comp.getAssemblyCode();
            try {
                FileWriter writer = new FileWriter("vm.txt");
                writer.write(vm);
                writer.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
            }
            marVM.bytecodes("test.marbc");
        } else
            System.err.print(errors);
    }
}
