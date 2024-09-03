package com.company;

import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeProperty;

import SymbolTable.*;
import Interpreter.*;

import java.util.*;

public class DefPhase extends marBaseListener {
    ParseTreeProperty<Scope> scopes = new ParseTreeProperty<>();
    ParseTreeProperty<Symbol.Type> exprType = new ParseTreeProperty<>();
    HashMap<Integer, Queue<Integer>> jumps = new HashMap<>();
    HashMap<String, Boolean> declared = new HashMap<>();


    Stack<Symbol.Type> returns = new Stack<>();

    Scope global, current;
    FunctionSymbol currentFunction = null;
    TypeSymbol currentType = null;
    int jumpAddr = 0,count = 0;
    String errors = "";
    boolean hasReturn = false;

    @Override
    public void enterProg(marParser.ProgContext ctx) {
        global = new Scope(null, "global");
        current = global;
        jumpAddr += 5;
        //System.out.println(ctx.variable().size());
    }

    @Override
    public void exitProg(marParser.ProgContext ctx) {
       // System.out.println(scopes.toString());
    }

    /*TODO ----------------------------------------------------------------*/
    @Override
    public void enterMethod(marParser.MethodContext ctx) {
        Token token = ctx.ID().getSymbol();
        Symbol.Type type;
        if (ctx.type() == null){
            type = Symbol.Type.VOID;
            exprType.put(ctx, type);
        }
        else {
            type = marCompiler.getType(ctx.start.getType());
            exprType.put(ctx, type);
        }
        /*if (ctx.bloc().instructions() == null){
            exprType.put(ctx.bloc().instructions().return_(), Symbol.Type.VOID);
        }*/
        FunctionSymbol function = new FunctionSymbol(token, type);
        currentFunction = function;
        current.define(function);
        current = new Scope(current, ctx.ID().getSymbol().getText());
        jumpAddr += 10;
        if (jumps.get(ctx.depth() )== null){
            Queue<Integer> jump = new LinkedList<>();
            jumps.put(ctx.depth(), jump);
        }
    }

    @Override
    public void exitMethod(marParser.MethodContext ctx) {
        int typeTokenType = ctx.start.getType();
        Symbol.Type type = marCompiler.getType(typeTokenType);
        VariableSymbol function = new VariableSymbol(ctx.ID().getSymbol(), type);
        if (!hasReturn && exprType.get(ctx) != Symbol.Type.VOID){
            errors = ("in line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + "Function " + ctx.ID().toString() + " doesnt has return");
        }
        if (returns.isEmpty()){
            jumpAddr += 10;
        }
        while (!returns.isEmpty()){
            Symbol.Type returnType = returns.pop();
            if (returnType != exprType.get(ctx)){
                marCompiler.error(ctx.ID().getSymbol(), "returning " + returnType + " instead of "+ exprType.get(ctx));
            }
        }
        if (!current.contains(function.lexeme()))
            current.define(function);

        if (jumps.get(ctx.depth() )== null){
            Queue<Integer> jump = new LinkedList<>();
            jumps.put(ctx.depth(), jump);
        }
        /*if (ctx.bloc().instructions().return_() == null){
            jumpAddr += 10;
        }*/
        jumps.get(ctx.depth()).add(jumpAddr-1);
    }


    @Override
    public void exitArgument(marParser.ArgumentContext ctx) {
        Symbol sym = new Symbol(ctx.ID().getSymbol(), marCompiler.getType(ctx.type().start.getType()));
        declared.put(ctx.ID().toString(), true);
        if(current.resolve_local(ctx.ID().getText()) == null) {
            currentFunction.add_argument(sym);
            current.define(sym);
        }
        else
            marCompiler.error(sym.getToken(), "formal parameter " + sym.lexeme()
                    + " is defined more than once in function "
                    + currentFunction.lexeme() );
    }

    @Override
    public void enterBloc(marParser.BlocContext ctx) {
        //System.out.println();
        if (ctx.parent.getRuleIndex() != 1){
            current = new Scope(current, "bloc" + count++);
        }

        jumpAddr +=5;
        //System.out.println("enterBloc >> " + current);
    }

    @Override
    public void exitBloc(marParser.BlocContext ctx) {
        current = current.getEnclosingScope();
        if ((ctx.parent.getRuleIndex() != 8 && ctx.parent.getRuleIndex() != 7 && ctx.parent.getRuleIndex() != 9) && ctx.instructions().return_() != null){
            hasReturn=true;
        }
       /* if (ctx.parent.getRuleIndex() != 1){
            jumpAddr += 5;
        }*/
    }
    /*TODO ----------------------------------------------------------------*/
    //@Override
    //public void enterInstructions(marParser.InstructionsContext ctx) {}

    //@Override
    //public void exitInstructions(marParser.InstructionsContext ctx) {}

    @Override
    public void exitMethod_call(marParser.Method_callContext ctx) {
        String functionName = ctx.ID().getText();
        Symbol s = current.resolve(functionName);
        if (s == null) {
            errors = ("in line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Undefined function " + functionName);
        }
        else if (!(s instanceof FunctionSymbol)) {
            errors = ("in line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Using variable " + functionName);
        }
        else {
            int expressaoSize = ctx.expression().size();
            if (((FunctionSymbol) s).get_arguments().size() != expressaoSize) {
                errors = ("in line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " The expected number of arguments aren't the same " + ((FunctionSymbol) s).get_arguments().size()+ "/"+ ctx.expression().size());
            } else if (!verifyArgumentsType((FunctionSymbol) s, ctx)) {
                errors = ("in line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Type of the arguments don't match");
            }
            exprType.put(ctx,s.getType());
        }
        jumpAddr += 9;
    }

    public boolean verifyArgumentsType(FunctionSymbol s,marParser.Method_callContext ctx){
        Symbol.Type type;
        for(int i = 0; i < s.get_arguments().size(); i++) {
            type = exprType.get(ctx.expression(i));
            if(s.get_arguments().get(i).getType() != type)
                return false;
        }
        return true;
    }

    @Override
    public void exitReturn(marParser.ReturnContext ctx) {
        if (ctx.expression() == null) {
            exprType.put(ctx, Symbol.Type.VOID);
            returns.push(Symbol.Type.VOID);
        } else {
            exprType.put(ctx, exprType.get(ctx.expression()));
            returns.push(exprType.get(ctx.expression()));
        }
        jumpAddr += 9;
    }

    @Override
    public void enterWhile(marParser.WhileContext ctx) {
        //jumpAddr += 5;
        if (jumps.get(ctx.depth() )== null){
            Queue<Integer> jump = new LinkedList<>();
            jumps.put(ctx.depth(), jump);
        }
            jumpAddr += 5;
    }

    @Override
    public void exitWhile(marParser.WhileContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression(0));
        if (type !=  Symbol.Type.BOOLEAN){
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't use " + "\"" + "while" + "\"" + " with " + type.toString() + '\n';
        }
        jumpAddr += 5;
        jumps.get(ctx.depth()).add(jumpAddr-1);
    }

    @Override
    public void enterIf(marParser.IfContext ctx) {
        if (jumps.get(ctx.depth())== null){
            Queue<Integer> jump = new LinkedList<>();
            jumps.put(ctx.depth(), jump);
        }
        jumpAddr +=5;
    }

    @Override
    public void exitIf(marParser.IfContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression(0));
        if (type !=  Symbol.Type.BOOLEAN){
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't use " + "\"" + "while" + "\"" + " with " + type.toString() + '\n';
        }
        if ((ctx.return_() != null) && (ctx.else_() != null && ctx.else_().return_() != null))
            hasReturn = true;
        //jumpAddr++;
        jumps.get(ctx.depth()).add(jumpAddr);
    }

    public void enterElse(marParser.ElseContext ctx) {
        jumpAddr += 5;
        //System.out.println(ctx.depth());
        jumps.get(ctx.depth()-1).add(jumpAddr);
    }

    @Override
    public void exitPrint(marParser.PrintContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression());

        if (type == exprType.get(ctx.expression()))
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        else if (type == Symbol.Type.NUMBER) {
            exprType.put(ctx, Symbol.Type.NUMBER);
        } else if (type == Symbol.Type.STRING) {
            exprType.put(ctx, Symbol.Type.STRING);
        }
        else if (type == Symbol.Type.NIL) {
            exprType.put(ctx, Symbol.Type.NIL);
        }
        jumpAddr++;
    }

    void defineVar(marParser.TypeContext typeCtx, Token nameToken) {
        int typeTokenType = typeCtx.start.getType();
        Symbol.Type type = marCompiler.getType(typeTokenType);
        VariableSymbol var = new VariableSymbol(nameToken, type);
        if (!current.contains(var.lexeme()))
            current.define(var); // Define symbol in current scope
        else
            marCompiler.error(nameToken, "variable " + var.lexeme() + " is already defined" + "\n");
    }

    @Override
    public void exitVariable(marParser.VariableContext ctx) {
        String varName = ctx.ID().getText();
        if (current.resolve(varName)!= null && ctx.type() != null){
            errors += "line " + ctx.start.getLine() + ":" + "variable " + varName + " is already defined" + "\n";
        }
        else if (ctx.type() != null){
            defineVar(ctx.type(), ctx.ID().getSymbol());
        }
        else if (current.resolve(varName) == null) {
            exprType.put(ctx, Symbol.Type.INVALID);
        } else{
            Symbol symbol = current.resolve(varName);
            exprType.put(ctx,symbol.getType());
        }
        if (ctx.ASSIGN() != null){
            if (declared.containsKey(ctx)){
                declared.replace(ctx.ID().toString(), true);
            }
            else {
                declared.put(ctx.ID().toString(), true);
            }
            if (current.resolve(varName) == null){
                errors += ("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Undefined variable " + varName);
                exprType.put(ctx,Symbol.Type.INVALID);
            }
            else {
                Symbol.Type type = current.resolve(varName).getType();
                //System.out.println(exprType.get(ctx.expression()));
                if (type != exprType.get(ctx.expression())){
                    errors += ("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't covert from type " + type + " into "+ exprType.get(ctx.expression()));
                }
            }
            jumpAddr+=5;
        }
        else {
            declared.put(ctx.ID().toString(), false);
        }
    }

    @Override
    public void exitPAR(marParser.PARContext ctx) {
        exprType.put(ctx, exprType.get(ctx.expression()));
    }

    @Override
    public void exitUNNOT(marParser.UNNOTContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression());
        String operator = ctx.children.get(0).getText();

        if (operator.equals("-") && type == Symbol.Type.NUMBER)
            exprType.put(ctx, Symbol.Type.NUMBER);
        else if (operator.equals("not") && type == Symbol.Type.BOOLEAN)
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        else
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't use " + "\"" + operator + "\"" + " with " + type.toString() + '\n';

        jumpAddr++;
    }

    public String verifyIfDefined(List<marParser.ExpressionContext> exprCtx) {
        String result = "";
        for (marParser.ExpressionContext expr : exprCtx) {
            if (exprType.get(expr) == null) {
                result = expr.getText() + " is not defined";
            }
        }
        return result;
    }

    @Override
    public void exitMULDIV(marParser.MULDIVContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER))
            exprType.put(ctx, Symbol.Type.NUMBER);
        else {
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString() + '\n';
            exprType.put(ctx, Symbol.Type.INVALID);
        }
        jumpAddr++;
    }

    @Override
    public void exitADDSUB(marParser.ADDSUBContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER))
            exprType.put(ctx, Symbol.Type.NUMBER);
        else if ((type1 == Symbol.Type.STRING) && (type2 == Symbol.Type.STRING))
            exprType.put(ctx, Symbol.Type.STRING);
        else{
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString() + '\n';
            exprType.put(ctx, Symbol.Type.INVALID);
        }

        jumpAddr++;
    }

    @Override
    public void exitREL(marParser.RELContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER))
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        else {
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString() + '\n';
            exprType.put(ctx, Symbol.Type.INVALID);
        }

        jumpAddr++;
    }

    @Override
    public void exitEQDIF(marParser.EQDIFContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if (type1 == type2)
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        else {
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString() + '\n';
            exprType.put(ctx, Symbol.Type.INVALID);
        }

        jumpAddr++;
    }

    @Override
    public void exitAND(marParser.ANDContext ctx) {
        String verifyDef = verifyIfDefined(ctx.expression());
        if(verifyDef.compareTo("") != 0)
            return;
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        if(type1 == Symbol.Type.BOOLEAN && type2 == Symbol.Type.BOOLEAN)
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        else {
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString() + '\n';
            exprType.put(ctx, Symbol.Type.INVALID);
        }
        jumpAddr++;
    }

    @Override
    public void exitOR(marParser.ORContext ctx) {
        String verifyDef = verifyIfDefined(ctx.expression());
        if(verifyDef.compareTo("") != 0)
            return;
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        if(type1 == Symbol.Type.BOOLEAN && type2 == Symbol.Type.BOOLEAN)
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        else {
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString() + '\n';
            exprType.put(ctx, Symbol.Type.INVALID);
        }
        jumpAddr++;
    }

    /*TODO ----------------------------------------------------------------*/
   /* @Override
    public void enterMETHCALL(marParser.METHCALLContext ctx) {jumpAddr += 5;}*/

    @Override
    public void exitMETHCALL(marParser.METHCALLContext ctx) {
        exprType.put(ctx, exprType.get(ctx.method_call()));
    }

    @Override
    public void enterArgument(marParser.ArgumentContext ctx) {
        //jumpAddr +=5;
    }

    @Override
    public void exitVAR(marParser.VARContext ctx) {
        String varName = ctx.ID().getText();
        if (!declared.get(ctx.ID().toString())) {
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Is not initialized " + varName + '\n';
        }
        if (current.resolve(varName) != null){
            Symbol symbol = current.resolve(varName);
            exprType.put(ctx,symbol.getType());
        }
        else {
            errors += "line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Undefined variable " + varName + '\n';
            exprType.put(ctx,Symbol.Type.INVALID);
        }
        jumpAddr += 5;
    }

    @Override
    public void exitNUMBER(marParser.NUMBERContext ctx) {
        exprType.put(ctx, Symbol.Type.NUMBER);
        jumpAddr += 9;

    }

    @Override
    public void exitBOOL(marParser.BOOLContext ctx) {
        exprType.put(ctx, Symbol.Type.BOOLEAN);
        jumpAddr++;

    }

    @Override
    public void exitSTRING(marParser.STRINGContext ctx) {
        exprType.put(ctx, Symbol.Type.STRING);
        jumpAddr += ctx.STRING().getText().length();

    }

    @Override
    public void exitNIL(marParser.NILContext ctx) {
        exprType.put(ctx,Symbol.Type.NIL);
        jumpAddr++;
    }

    void saveScope(ParserRuleContext ctx, Scope s) {
        scopes.put(ctx, s);
    }

    public ParseTreeProperty<Symbol.Type> getExprType() {
        return exprType;
    }

    public int getJumpAddr() {
        return jumpAddr;
    }

    public HashMap<Integer, Queue<Integer>> getJumps() {
        return jumps;
    }

    public String getErrors() {
        return errors;
    }

    public ParseTreeProperty<Scope> getScopes() {
        return scopes;
    }
}