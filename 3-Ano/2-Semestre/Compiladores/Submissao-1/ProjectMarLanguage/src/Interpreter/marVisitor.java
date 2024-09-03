// Generated from java-escape by ANTLR 4.11.1
package Interpreter;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link marParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface marVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link marParser#prog}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProg(marParser.ProgContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#print}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrint(marParser.PrintContext ctx);
	/**
	 * Visit a parse tree produced by the {@code PAR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPAR(marParser.PARContext ctx);
	/**
	 * Visit a parse tree produced by the {@code DIV}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDIV(marParser.DIVContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ADD}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitADD(marParser.ADDContext ctx);
	/**
	 * Visit a parse tree produced by the {@code SUB}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSUB(marParser.SUBContext ctx);
	/**
	 * Visit a parse tree produced by the {@code MUL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMUL(marParser.MULContext ctx);
	/**
	 * Visit a parse tree produced by the {@code UN}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUN(marParser.UNContext ctx);
	/**
	 * Visit a parse tree produced by the {@code DTYPE}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDTYPE(marParser.DTYPEContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#data}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitData(marParser.DataContext ctx);
}