// Generated from D:/ProjectMarLanguage/src\mar.g4 by ANTLR 4.12.0
package Interpreter;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link marParser}.
 */
public interface marListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link marParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(marParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link marParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(marParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link marParser#print}.
	 * @param ctx the parse tree
	 */
	void enterPrint(marParser.PrintContext ctx);
	/**
	 * Exit a parse tree produced by {@link marParser#print}.
	 * @param ctx the parse tree
	 */
	void exitPrint(marParser.PrintContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PAR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterPAR(marParser.PARContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PAR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitPAR(marParser.PARContext ctx);
	/**
	 * Enter a parse tree produced by the {@code NIL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterNIL(marParser.NILContext ctx);
	/**
	 * Exit a parse tree produced by the {@code NIL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitNIL(marParser.NILContext ctx);
	/**
	 * Enter a parse tree produced by the {@code NUMBER}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterNUMBER(marParser.NUMBERContext ctx);
	/**
	 * Exit a parse tree produced by the {@code NUMBER}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitNUMBER(marParser.NUMBERContext ctx);
	/**
	 * Enter a parse tree produced by the {@code OR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterOR(marParser.ORContext ctx);
	/**
	 * Exit a parse tree produced by the {@code OR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitOR(marParser.ORContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BOOL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterBOOL(marParser.BOOLContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BOOL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitBOOL(marParser.BOOLContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ADDSUB}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterADDSUB(marParser.ADDSUBContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ADDSUB}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitADDSUB(marParser.ADDSUBContext ctx);
	/**
	 * Enter a parse tree produced by the {@code EQDIF}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterEQDIF(marParser.EQDIFContext ctx);
	/**
	 * Exit a parse tree produced by the {@code EQDIF}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitEQDIF(marParser.EQDIFContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AND}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterAND(marParser.ANDContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AND}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitAND(marParser.ANDContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UNNOT}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterUNNOT(marParser.UNNOTContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UNNOT}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitUNNOT(marParser.UNNOTContext ctx);
	/**
	 * Enter a parse tree produced by the {@code REL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterREL(marParser.RELContext ctx);
	/**
	 * Exit a parse tree produced by the {@code REL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitREL(marParser.RELContext ctx);
	/**
	 * Enter a parse tree produced by the {@code STRING}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterSTRING(marParser.STRINGContext ctx);
	/**
	 * Exit a parse tree produced by the {@code STRING}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitSTRING(marParser.STRINGContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MULDIV}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterMULDIV(marParser.MULDIVContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MULDIV}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitMULDIV(marParser.MULDIVContext ctx);
}