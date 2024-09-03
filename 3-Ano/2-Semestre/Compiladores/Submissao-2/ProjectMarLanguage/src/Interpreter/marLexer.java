// Generated from D:/ProjectMarLanguage/src\mar.g4 by ANTLR 4.12.0
package Interpreter;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class marLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.12.0", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		WS=1, DOT=2, SCOL=3, LPAR=4, RPAR=5, MUL=6, DIV=7, ADD=8, SUB=9, GT=10, 
		LT=11, GEQ=12, LEQ=13, EQ=14, DIF=15, NUMBER=16, BOOL=17, STRING=18, PRINT=19, 
		NIL=20, NOT=21, AND=22, OR=23;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"WS", "DOT", "SCOL", "LPAR", "RPAR", "MUL", "DIV", "ADD", "SUB", "GT", 
			"LT", "GEQ", "LEQ", "EQ", "DIF", "NUMBER", "BOOL", "STRING", "PRINT", 
			"NIL", "NOT", "AND", "OR"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, "'.'", "';'", "'('", "')'", "'*'", "'/'", "'+'", "'-'", "'>'", 
			"'<'", "'>='", "'<='", "'=='", "'!='", null, null, null, "'print'", "'nil'", 
			"'not'", "'and'", "'or'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "WS", "DOT", "SCOL", "LPAR", "RPAR", "MUL", "DIV", "ADD", "SUB", 
			"GT", "LT", "GEQ", "LEQ", "EQ", "DIF", "NUMBER", "BOOL", "STRING", "PRINT", 
			"NIL", "NOT", "AND", "OR"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public marLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "mar.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0017\u008b\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002"+
		"\u0001\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002"+
		"\u0004\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002"+
		"\u0007\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002"+
		"\u000b\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e"+
		"\u0002\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011"+
		"\u0002\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014"+
		"\u0002\u0015\u0007\u0015\u0002\u0016\u0007\u0016\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002"+
		"\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005"+
		"\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001"+
		"\t\u0001\t\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\u000b\u0001\f"+
		"\u0001\f\u0001\f\u0001\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000f\u0004\u000fU\b\u000f\u000b\u000f\f\u000fV\u0001\u000f"+
		"\u0001\u000f\u0004\u000f[\b\u000f\u000b\u000f\f\u000f\\\u0003\u000f_\b"+
		"\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001"+
		"\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0003\u0010j\b\u0010\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0005\u0011p\b\u0011\n\u0011"+
		"\f\u0011s\t\u0011\u0001\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0001\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001"+
		"\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0016\u0001\u0016\u0001"+
		"\u0016\u0001q\u0000\u0017\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004"+
		"\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017"+
		"\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\'"+
		"\u0014)\u0015+\u0016-\u0017\u0001\u0000\u0003\u0003\u0000\t\n\r\r  \u0001"+
		"\u000009\u0005\u0000\"\"\\\\nnrrtt\u0090\u0000\u0001\u0001\u0000\u0000"+
		"\u0000\u0000\u0003\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000"+
		"\u0000\u0000\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000"+
		"\u0000\u000b\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000"+
		"\u000f\u0001\u0000\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000"+
		"\u0013\u0001\u0000\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000"+
		"\u0017\u0001\u0000\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000"+
		"\u001b\u0001\u0000\u0000\u0000\u0000\u001d\u0001\u0000\u0000\u0000\u0000"+
		"\u001f\u0001\u0000\u0000\u0000\u0000!\u0001\u0000\u0000\u0000\u0000#\u0001"+
		"\u0000\u0000\u0000\u0000%\u0001\u0000\u0000\u0000\u0000\'\u0001\u0000"+
		"\u0000\u0000\u0000)\u0001\u0000\u0000\u0000\u0000+\u0001\u0000\u0000\u0000"+
		"\u0000-\u0001\u0000\u0000\u0000\u0001/\u0001\u0000\u0000\u0000\u00033"+
		"\u0001\u0000\u0000\u0000\u00055\u0001\u0000\u0000\u0000\u00077\u0001\u0000"+
		"\u0000\u0000\t9\u0001\u0000\u0000\u0000\u000b;\u0001\u0000\u0000\u0000"+
		"\r=\u0001\u0000\u0000\u0000\u000f?\u0001\u0000\u0000\u0000\u0011A\u0001"+
		"\u0000\u0000\u0000\u0013C\u0001\u0000\u0000\u0000\u0015E\u0001\u0000\u0000"+
		"\u0000\u0017G\u0001\u0000\u0000\u0000\u0019J\u0001\u0000\u0000\u0000\u001b"+
		"M\u0001\u0000\u0000\u0000\u001dP\u0001\u0000\u0000\u0000\u001fT\u0001"+
		"\u0000\u0000\u0000!i\u0001\u0000\u0000\u0000#k\u0001\u0000\u0000\u0000"+
		"%v\u0001\u0000\u0000\u0000\'|\u0001\u0000\u0000\u0000)\u0080\u0001\u0000"+
		"\u0000\u0000+\u0084\u0001\u0000\u0000\u0000-\u0088\u0001\u0000\u0000\u0000"+
		"/0\u0007\u0000\u0000\u000001\u0001\u0000\u0000\u000012\u0006\u0000\u0000"+
		"\u00002\u0002\u0001\u0000\u0000\u000034\u0005.\u0000\u00004\u0004\u0001"+
		"\u0000\u0000\u000056\u0005;\u0000\u00006\u0006\u0001\u0000\u0000\u0000"+
		"78\u0005(\u0000\u00008\b\u0001\u0000\u0000\u00009:\u0005)\u0000\u0000"+
		":\n\u0001\u0000\u0000\u0000;<\u0005*\u0000\u0000<\f\u0001\u0000\u0000"+
		"\u0000=>\u0005/\u0000\u0000>\u000e\u0001\u0000\u0000\u0000?@\u0005+\u0000"+
		"\u0000@\u0010\u0001\u0000\u0000\u0000AB\u0005-\u0000\u0000B\u0012\u0001"+
		"\u0000\u0000\u0000CD\u0005>\u0000\u0000D\u0014\u0001\u0000\u0000\u0000"+
		"EF\u0005<\u0000\u0000F\u0016\u0001\u0000\u0000\u0000GH\u0005>\u0000\u0000"+
		"HI\u0005=\u0000\u0000I\u0018\u0001\u0000\u0000\u0000JK\u0005<\u0000\u0000"+
		"KL\u0005=\u0000\u0000L\u001a\u0001\u0000\u0000\u0000MN\u0005=\u0000\u0000"+
		"NO\u0005=\u0000\u0000O\u001c\u0001\u0000\u0000\u0000PQ\u0005!\u0000\u0000"+
		"QR\u0005=\u0000\u0000R\u001e\u0001\u0000\u0000\u0000SU\u0007\u0001\u0000"+
		"\u0000TS\u0001\u0000\u0000\u0000UV\u0001\u0000\u0000\u0000VT\u0001\u0000"+
		"\u0000\u0000VW\u0001\u0000\u0000\u0000W^\u0001\u0000\u0000\u0000XZ\u0003"+
		"\u0003\u0001\u0000Y[\u0007\u0001\u0000\u0000ZY\u0001\u0000\u0000\u0000"+
		"[\\\u0001\u0000\u0000\u0000\\Z\u0001\u0000\u0000\u0000\\]\u0001\u0000"+
		"\u0000\u0000]_\u0001\u0000\u0000\u0000^X\u0001\u0000\u0000\u0000^_\u0001"+
		"\u0000\u0000\u0000_ \u0001\u0000\u0000\u0000`a\u0005t\u0000\u0000ab\u0005"+
		"r\u0000\u0000bc\u0005u\u0000\u0000cj\u0005e\u0000\u0000de\u0005f\u0000"+
		"\u0000ef\u0005a\u0000\u0000fg\u0005l\u0000\u0000gh\u0005s\u0000\u0000"+
		"hj\u0005e\u0000\u0000i`\u0001\u0000\u0000\u0000id\u0001\u0000\u0000\u0000"+
		"j\"\u0001\u0000\u0000\u0000kq\u0005\"\u0000\u0000lm\u0005\\\u0000\u0000"+
		"mp\u0007\u0002\u0000\u0000np\t\u0000\u0000\u0000ol\u0001\u0000\u0000\u0000"+
		"on\u0001\u0000\u0000\u0000ps\u0001\u0000\u0000\u0000qr\u0001\u0000\u0000"+
		"\u0000qo\u0001\u0000\u0000\u0000rt\u0001\u0000\u0000\u0000sq\u0001\u0000"+
		"\u0000\u0000tu\u0005\"\u0000\u0000u$\u0001\u0000\u0000\u0000vw\u0005p"+
		"\u0000\u0000wx\u0005r\u0000\u0000xy\u0005i\u0000\u0000yz\u0005n\u0000"+
		"\u0000z{\u0005t\u0000\u0000{&\u0001\u0000\u0000\u0000|}\u0005n\u0000\u0000"+
		"}~\u0005i\u0000\u0000~\u007f\u0005l\u0000\u0000\u007f(\u0001\u0000\u0000"+
		"\u0000\u0080\u0081\u0005n\u0000\u0000\u0081\u0082\u0005o\u0000\u0000\u0082"+
		"\u0083\u0005t\u0000\u0000\u0083*\u0001\u0000\u0000\u0000\u0084\u0085\u0005"+
		"a\u0000\u0000\u0085\u0086\u0005n\u0000\u0000\u0086\u0087\u0005d\u0000"+
		"\u0000\u0087,\u0001\u0000\u0000\u0000\u0088\u0089\u0005o\u0000\u0000\u0089"+
		"\u008a\u0005r\u0000\u0000\u008a.\u0001\u0000\u0000\u0000\u0007\u0000V"+
		"\\^ioq\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}