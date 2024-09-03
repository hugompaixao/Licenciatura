grammar mar;

// grammar parser
prog :
    print+ EOF
    ;

print :
    PRINT expression SCOL
    ;

expression :
    LPAR expression RPAR                            #PAR
    | (SUB | NOT) expression                        #UNNOT
    | expression (MUL | DIV) expression             #MULDIV
    | expression (ADD|SUB) expression               #ADDSUB
    | expression (GT | LT | GEQ | LEQ) expression   #REL
    | expression (EQ | DIF) expression              #EQDIF
    | expression AND expression                     #AND
    | expression OR expression                      #OR
    | NUMBER                                        #NUMBER
    | BOOL                                          #BOOL
    | STRING                                        #STRING
    | NIL                                           #NIL
    ;

/*data_type :
    NIL         #NIL
    |NUMBER     #NUMBER
    | BOOL      #BOOL
    | STRING    #STRING
    ;*/

// grammar lexer
// Pontuação
    WS :[ \r\n\t] -> skip;
    DOT :'.';
    SCOL :';';
    LPAR :'(';
    RPAR :')';

// Operadores Aritméticos
    MUL :'*';
    DIV :'/';
    ADD :'+';
    SUB :'-';

// Operadores Comparação
    GT :'>';
    LT :'<';
    GEQ :'>=';
    LEQ :'<=';
    EQ :'==';
    DIF :'!=';

// Tipos de Dados
    NUMBER :[0-9]+ (DOT [0-9]+)?;
    BOOL : 'true' | 'false';
    STRING : '"' ('\\' [tnr"\\] | .) *? '"';

// Palavras Reservadas
    PRINT :'print';
    NIL :'nil';
    NOT :'not';
    AND :'and';
    OR :'or';