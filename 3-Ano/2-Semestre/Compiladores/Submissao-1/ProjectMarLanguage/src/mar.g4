grammar mar;

// Grammar Parser
prog :
    print+ EOF
    ;

print :
    PRINT expression SCOL
;

expression :
    LPAR expression RPAR           #PAR
    | SUB expression               #UN
    | expression (MUL expression)+ #MUL
    | expression (DIV expression)+ #DIV
    | expression (ADD expression)+ #ADD
    | expression (SUB expression)+ #SUB
    | data                         #DTYPE
    ;

data :
    INT
    | DOUBLE
    ;


// Grammar Lexer
    WS :[ \t\r\n] -> skip;
    DOT :'.';
    SCOL :';';
    LPAR :'(';
    RPAR :')';

    MUL :'*';
    DIV :'/';
    ADD :'+';
    SUB :'-';

    INT : [0-9]+ | [1-9] [0-9]*;
    DOUBLE : [0-9]+ DOT [0-9]+;
    PRINT :'print';