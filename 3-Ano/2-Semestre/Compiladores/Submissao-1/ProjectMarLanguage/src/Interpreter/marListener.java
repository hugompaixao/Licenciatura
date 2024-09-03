// Generated from java-escape by ANTLR 4.11.1
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
	 * Enter a parse tree produced by the {@code DIV}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterDIV(marParser.DIVContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DIV}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitDIV(marParser.DIVContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ADD}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterADD(marParser.ADDContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ADD}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitADD(marParser.ADDContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SUB}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterSUB(marParser.SUBContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SUB}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitSUB(marParser.SUBContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MUL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterMUL(marParser.MULContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MUL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitMUL(marParser.MULContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UN}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterUN(marParser.UNContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UN}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitUN(marParser.UNContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DTYPE}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterDTYPE(marParser.DTYPEContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DTYPE}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitDTYPE(marParser.DTYPEContext ctx);
	/**
	 * Enter a parse tree produced by {@link marParser#data}.
	 * @param ctx the parse tree
	 */
	void enterData(marParser.DataContext ctx);
	/**
	 * Exit a parse tree produced by {@link marParser#data}.
	 * @param ctx the parse tree
	 */
	void exitData(marParser.DataContext ctx);
}