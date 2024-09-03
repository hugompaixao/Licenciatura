package com.company;

/***
 * Excerpted from "The Definitive ANTLR 4 Reference",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpantlr2 for more book information.
 ***/
import org.antlr.v4.runtime.tree.ParseTreeProperty;
import Interpreter.*;
import SymbolTable.*;



public class RefPhase extends marBaseListener {
    ParseTreeProperty<Scope> scopes;
    Scope globals;
    Scope currentScope; // resolve symbols starting in this scope

    public RefPhase(Scope globals, ParseTreeProperty<Scope> scopes) {
        this.scopes = scopes;
        this.globals = globals;
        //this.currentScope = globals;
    }

    public void enterProg(marParser.ProgContext ctx) {
        currentScope = globals;
        //System.out.println();
    }

    /*public void enterDeclaracaoFuncao(a22.DeclaracaoFuncaoContext ctx) {
        currentScope = scopes.get(ctx);
        System.out.println("sou eu" +currentScope);
        if(globals.resolve("main") == null){
            System.err.println("You must have a main function");
        }
    }

    public void exitDeclaracaoFuncao(a22.DeclaracaoFuncaoContext ctx) {
        currentScope = currentScope.getEnclosingScope();
    }*/

    /*public void enterFile(a22.FileContext ctx) {
        currentScope = globals;
    }*/


    /*
    public void enterFunctionDecl(CymbolParser.FunctionDeclContext ctx) {
        currentScope = scopes.get(ctx);
    }
    public void exitFunctionDecl(CymbolParser.FunctionDeclContext ctx) {
        currentScope = currentScope.getEnclosingScope();
    }
    */

    /*public void enterBlock(CymbolParser.BlockContext ctx) {
        currentScope = scopes.get(ctx);
    }
    public void exitBlock(CymbolParser.BlockContext ctx) {
        currentScope = currentScope.getEnclosingScope();
    }

    public void exitVar(CymbolParser.VarContext ctx) {
        String name = ctx.ID().getSymbol().getText();
        Symbol var = currentScope.resolve(name);
        if ( var==null ) {
            CheckSymbols.error(ctx.ID().getSymbol(), "no such variable: "+name);
        }
        if ( var instanceof FunctionSymbol) {
            CheckSymbols.error(ctx.ID().getSymbol(), name+" is not a variable");
        }
    }

    public void exitCall(CymbolParser.CallContext ctx) {
        String funcName = ctx.ID().getText();
        Symbol meth = currentScope.resolve(funcName);
        if ( meth==null ) {
            CheckSymbols.error(ctx.ID().getSymbol(), "no such function: "+funcName);
        }
        if ( meth instanceof VariableSymbol) {
            CheckSymbols.error(ctx.ID().getSymbol(), funcName+" is not a function");
        }
    }*/
}
