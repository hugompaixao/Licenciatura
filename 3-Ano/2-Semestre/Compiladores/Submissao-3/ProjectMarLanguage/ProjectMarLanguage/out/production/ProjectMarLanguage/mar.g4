grammar mar;

// grammar parser
prog :
    variable*
    method*
    instructions
    EOF
    ;

method :
    type? ID LPAR (argument (COMMA argument)*)? RPAR bloc
    ;

argument :
    type ID
    ;

bloc :
    LBRAC instructions RBRAC
    ;

instructions :
    (bloc | while | if | print | variable |expression SCOL)* return?
    ;

method_call :
    ID LPAR (expression (COMMA (expression))*)? RPAR
    ;

return :
    RETURN expression? SCOL
    ;

while :
    WHILE expression DO (bloc | expression | return | variable)
    ;

if :
    IF expression THEN (bloc | expression | return | variable) else?
    ;

else:
    ELSE (bloc | expression | return | variable)
    ;

print :
    PRINT expression SCOL
    ;

variable :
    (type)? ID (ASSIGN expression)? SCOL
    ;

type :
    (K_NUMBER | K_BOOL | K_STRING)
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
    | method_call                                   #METHCALL
    | ID                                            #VAR
    | NUMBER                                        #NUMBER
    | BOOL                                          #BOOL
    | STRING                                        #STRING
    | K_NIL                                         #NIL
    ;


// grammar lexer
//
    K_VOID :'void';
    K_NUMBER :'number';
    K_BOOL :'bool';
    K_STRING :'string';
    K_NIL :'nil';

//
    NUMBER :[0-9]+ (DOT [0-9]+)?;
    BOOL : 'true' | 'false';
    STRING : '"' ('\\' [tnr"\\] | .) *? '"';

//
    RETURN :'return';
    WHILE :'while';
    DO :'do';
    IF :'if';
    THEN :'then';
    ELSE :'else';
    PRINT :'print';
    NOT :'not';
    AND :'and';
    OR :'or';
    ID :('_' | [a-zA-Z]) ([a-zA-Z] | '_' |NUMBER)*;

//
    WS :[ \r\n\t] -> skip;
    SL_C :'//' .*? (EOF | '\n') -> skip;
    ML_C :'/*' .*? '*/' -> skip;
    DOT :'.';
    COMMA :',';
    SCOL :';';
    LPAR :'(';
    RPAR :')';
    LBRAC:'{';
    RBRAC:'}';
    ASSIGN :'=';

//
    MUL :'*';
    DIV :'/';
    ADD :'+';
    SUB :'-';

//
    GT :'>';
    LT :'<';
    GEQ :'>=';
    LEQ :'<=';
    EQ :'==';
    DIF :'!=';
