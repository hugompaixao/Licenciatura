package com.company;

/***
 * Excerpted from "The Definitive ANTLR 4 Reference",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpantlr2 for more book information.
 *
 * -- with a few modifications by Fernando Lobo (see readme.txt file for details)
 ***/
//import jdk.internal.access.JavaIOFileDescriptorAccess;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeProperty;

import SymbolTable.*;
import Interpreter.*;

import org.antlr.v4.runtime.tree.TerminalNode;

import java.util.ArrayList;
import java.util.List;

public class DefPhase extends marBaseListener {
    ParseTreeProperty<Scope> scopes = new ParseTreeProperty<>();
    ParseTreeProperty<Symbol.Type> exprType = new ParseTreeProperty<>();
    ArrayList<TypeSymbol> Types = new ArrayList<>();
    Scope global;
    Scope currentScope;   // define symbols in this scope
    int semanticErrors = 0;

    FunctionSymbol currentFunction = null;
    TypeSymbol currentType = null;

    public void enterProg(marParser.ProgContext ctx) {
        global = new Scope(null, "global");
        currentScope = global;
    }

    @Override
    public void exitPrint(marParser.PrintContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression());

        if (type == Symbol.Type.BOOLEAN)
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        else if (type == Symbol.Type.NUMBER) {
            exprType.put(ctx, Symbol.Type.NUMBER);
        } else if (type == Symbol.Type.STRING) {
            exprType.put(ctx, Symbol.Type.STRING);
        }
        else if (type == Symbol.Type.NIL) {
            exprType.put(ctx, Symbol.Type.NIL);
        }
       /* else
            System.err.println("lineSum " + ctx.start.getLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString());*/
    }

    public void exitProg(marParser.ProgContext ctx) {
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

    public void exitNUMBER(marParser.NUMBERContext ctx) {
        exprType.put(ctx, Symbol.Type.NUMBER);
    }

    public void exitBOOL(marParser.BOOLContext ctx) {
        exprType.put(ctx, Symbol.Type.BOOLEAN);
    }

    public void exitSTRING(marParser.STRINGContext ctx) {
        exprType.put(ctx, Symbol.Type.STRING);
    }

    public void exitNIL( marParser.NILContext ctx ) {
        exprType.put(ctx,Symbol.Type.NIL);
    }

    public void exitUNNOT(marParser.UNNOTContext ctx) {
        Symbol.Type type = exprType.get(ctx.expression());
        String operator = ctx.children.get(0).getText();

        if (operator.equals("-") && type == Symbol.Type.NUMBER) {
            exprType.put(ctx, Symbol.Type.NUMBER);

        }
        else if (operator.equals("not") && type == Symbol.Type.BOOLEAN) {
            exprType.put(ctx, Symbol.Type.BOOLEAN);

        }
        else {
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't use " + "\"" + operator + "\"" + " with " + type.toString());
        }
    }


    @Override
    public void exitADDSUB(marParser.ADDSUBContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER)) {
            exprType.put(ctx, Symbol.Type.NUMBER);
        } else if ((type1 == Symbol.Type.STRING) && (type2 == Symbol.Type.STRING)) {
            exprType.put(ctx, Symbol.Type.STRING);
        } else
            System.err.println("lineSum " + ctx.start.getLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString());
    }

    public void exitMULDIV(marParser.MULDIVContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER)) {
            exprType.put(ctx, Symbol.Type.NUMBER);
        } else
            System.err.println("lineSum " + ctx.start.getLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString());
    }


    public void exitREL(marParser.RELContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String operator = ctx.children.get(1).getText();

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if ((type1 == Symbol.Type.NUMBER) && (type2 == Symbol.Type.NUMBER)) {
            exprType.put(ctx, Symbol.Type.NUMBER);
        } else
            System.err.println("lineSum " + ctx.start.getLine() + " error: Invalid types for binary operator " + type1.toString() + " " + operator + " " + type2.toString());
    }

    public void exitEQDIF(marParser.EQDIFContext ctx) {
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        String verifyDef = verifyIfDefined(ctx.expression());
        if (verifyDef.compareTo("") != 0)
            return;
        else if (type1 == type2) {
            exprType.put(ctx, Symbol.Type.BOOLEAN);

        } else {
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString());
        }
    }

    @Override
    public void exitAND(marParser.ANDContext ctx) {
        String verifyDef = verifyIfDefined(ctx.expression());
        if(verifyDef.compareTo("") != 0)
            return;
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        if(type1 == Symbol.Type.BOOLEAN && type2 == Symbol.Type.BOOLEAN) {
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        }
        else {
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString());
        }
    }

    @Override
    public void exitOR(marParser.ORContext ctx) {
        String verifyDef = verifyIfDefined(ctx.expression());
        if(verifyDef.compareTo("") != 0)
            return;
        Symbol.Type type1 = exprType.get(ctx.expression(0));
        Symbol.Type type2 = exprType.get(ctx.expression(1));

        if(type1 == Symbol.Type.BOOLEAN && type2 == Symbol.Type.BOOLEAN) {
            exprType.put(ctx, Symbol.Type.BOOLEAN);
        }
        else {
            System.err.println("line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Can't compare " + type1.toString() + " with " + type2.toString());
        }
    }

    void saveScope(ParserRuleContext ctx, Scope s) {
        scopes.put(ctx, s);
    }

    public ParseTreeProperty<Symbol.Type> getExprType() {
        return exprType;
    }
}