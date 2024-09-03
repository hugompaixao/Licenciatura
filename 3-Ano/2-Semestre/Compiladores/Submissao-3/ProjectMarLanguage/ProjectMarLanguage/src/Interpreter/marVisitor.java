// Generated from D:/ProjectMarLanguage/src\mar.g4 by ANTLR 4.12.0
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
	 * Visit a parse tree produced by {@link marParser#method}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMethod(marParser.MethodContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#argument}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgument(marParser.ArgumentContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#bloc}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBloc(marParser.BlocContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#instructions}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInstructions(marParser.InstructionsContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#method_call}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMethod_call(marParser.Method_callContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#return}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReturn(marParser.ReturnContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#while}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhile(marParser.WhileContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#if}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIf(marParser.IfContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#else}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitElse(marParser.ElseContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#print}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrint(marParser.PrintContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#variable}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVariable(marParser.VariableContext ctx);
	/**
	 * Visit a parse tree produced by {@link marParser#type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType(marParser.TypeContext ctx);
	/**
	 * Visit a parse tree produced by the {@code PAR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPAR(marParser.PARContext ctx);
	/**
	 * Visit a parse tree produced by the {@code NUMBER}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNUMBER(marParser.NUMBERContext ctx);
	/**
	 * Visit a parse tree produced by the {@code OR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOR(marParser.ORContext ctx);
	/**
	 * Visit a parse tree produced by the {@code VAR}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVAR(marParser.VARContext ctx);
	/**
	 * Visit a parse tree produced by the {@code EQDIF}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEQDIF(marParser.EQDIFContext ctx);
	/**
	 * Visit a parse tree produced by the {@code UNNOT}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUNNOT(marParser.UNNOTContext ctx);
	/**
	 * Visit a parse tree produced by the {@code NIL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNIL(marParser.NILContext ctx);
	/**
	 * Visit a parse tree produced by the {@code BOOL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBOOL(marParser.BOOLContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ADDSUB}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitADDSUB(marParser.ADDSUBContext ctx);
	/**
	 * Visit a parse tree produced by the {@code AND}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAND(marParser.ANDContext ctx);
	/**
	 * Visit a parse tree produced by the {@code REL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitREL(marParser.RELContext ctx);
	/**
	 * Visit a parse tree produced by the {@code STRING}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSTRING(marParser.STRINGContext ctx);
	/**
	 * Visit a parse tree produced by the {@code MULDIV}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMULDIV(marParser.MULDIVContext ctx);
	/**
	 * Visit a parse tree produced by the {@code METHCALL}
	 * labeled alternative in {@link marParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMETHCALL(marParser.METHCALLContext ctx);
}