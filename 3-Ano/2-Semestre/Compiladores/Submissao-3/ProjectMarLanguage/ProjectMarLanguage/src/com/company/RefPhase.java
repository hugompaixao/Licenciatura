package com.company;/*package com.company;

/***
 * Excerpted from "The Definitive ANTLR 4 Reference",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpantlr2 for more book information.
 ***/
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.tree.ParseTreeProperty;
import Interpreter.*;
import SymbolTable.*;

import java.util.ArrayList;
import java.util.List;


public class RefPhase extends marBaseListener {
    ParseTreeProperty<Scope> scopes = new ParseTreeProperty<>();
    ParseTreeProperty<Symbol.Type> exprType = new ParseTreeProperty<>();
    Scope global;
    Scope currentScope;// define symbols in this scope
    int count = 0;
    int test = 0;

    @Override
    public void enterProg(marParser.ProgContext ctx) {
        global = new Scope(null, "global");
        currentScope = global;
    }

    @Override
    public void enterBloc(marParser.BlocContext ctx) {
        currentScope = new Scope(currentScope, "bloc"  + count++);
        saveScope(ctx, currentScope);
        //System.out.println("enterBloc >> " + currentScope);
    }

    @Override
    public void exitBloc(marParser.BlocContext ctx) {
        //System.out.println("exitBloc >> " + currentScope);
        currentScope = currentScope.getEnclosingScope();
    }

    @Override
    public void exitWhile(marParser.WhileContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression(0));
        if (type !=  Symbol.Type.BOOLEAN)
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't use " + "\"" + "while" + "\"" + " with " + type.toString());
    }

    @Override
    public void exitIf(marParser.IfContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression(0));
        if (type !=  Symbol.Type.BOOLEAN)
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't use " + "\"" + "if" + "\"" + " with " + type.toString());
    }

    public void exitVariable(marParser.VariableContext ctx) {
        String varName = ctx.ID().getText();
        if (ctx.ASSIGN() != null){
            Symbol.Type type = currentScope.resolve(varName).getType();
            if (type != exprType.get(ctx.expression()))
                System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't covert from type " + type + " into "+ exprType.get(ctx.expression()));
        }
    }

    @Override
    public void exitUNNOT(marParser.UNNOTContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression());
        String operator = ctx.children.get(0).getText();

        if (operator.equals("not") && type != Symbol.Type.BOOLEAN)
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't use " + "\"" + operator + "\"" + " with " + type.toString());
    }

    @Override
    public void exitMULDIV(marParser.MULDIVContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        if ((type1 != Symbol.Type.NUMBER) && (type2 != Symbol.Type.NUMBER))
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString());
    }

    @Override
    public void exitADDSUB(marParser.ADDSUBContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        if ((type1 != Symbol.Type.STRING) && (type2 != Symbol.Type.STRING))
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString());
    }

    @Override
    public void exitREL(marParser.RELContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        if ((type1 != Symbol.Type.NUMBER) && (type2 != Symbol.Type.NUMBER))
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString());
    }

    @Override
    public void exitEQDIF(marParser.EQDIFContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        if (type1 != type2)
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString());
    }

    @Override
    public void exitAND(marParser.ANDContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        if(!(type1 == Symbol.Type.BOOLEAN && type2 == Symbol.Type.BOOLEAN))
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString());
    }

    @Override
    public void exitOR(marParser.ORContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        if(!(type1 == Symbol.Type.BOOLEAN && type2 == Symbol.Type.BOOLEAN))
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString());
    }

    @Override
    public void exitVAR(marParser.VARContext ctx) {
        String varName = ctx.ID().getText();
        if (currentScope.resolve(ctx.ID().getText()) == null)
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Undefined variable " + varName);
    }

    void saveScope(ParserRuleContext ctx, Scope s) {
        scopes.put(ctx, s);
    }
}