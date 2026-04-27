lexer grammar ExprLexer;

// ==========================================
// TOKENS
// ==========================================

STRING_UTF8         : 'u8' STR_BODY ;
STRING_UTF16        : 'u' STR_BODY ;
STRING_UTF32        : 'U' STR_BODY ;
STRING_WIDE         : 'L' STR_BODY ;
STRING_C            : [cC] STR_BODY ;
STRING_RAW          : [rR] STR_BODY 
                    | 'u8' [rR] STR_BODY
                    | [uUL] [rR] STR_BODY
                    | [rR] [uUL] STR_BODY
                    | [cC] [rR] STR_BODY
                    | [rR] [cC] STR_BODY
                    ;
STRING_NORMAL       : STR_BODY ;

LPAREN              : '(' ;
RPAREN              : ')' ;
LBRACKET            : '[' | '<:' ;
RBRACKET            : ']' | ':>' ;
LBRACE              : '{' | '<%' ;
RBRACE              : '}' | '%>' ;
MOD                 : '%' ;
MUL                 : '*' ;
DIV                 : '/' ;
ADD                 : '+' ;
SUB                 : '-' ;

SHL                 : '<<' ;
SHR                 : '>>' ;
SPACESHIP           : '<=>' ;
GE                  : '>=' ;
GT                  : '>' ;
LE                  : '<=' ;
LT                  : '<' ;
EQ                  : '==' ;
NE                  : '!=' ;
BIT_AND             : '&' ;
BIT_XOR             : '^' ;
BIT_OR              : '|' ;
LOG_AND             : '&&' ;
LOG_OR              : '||' ;
INC                 : '++' ;
DEC                 : '--' ;
DOT                 : '.' ;
COMMA               : ',' ;
LOG_NOT             : '!' ;
BIT_NOT             : '~' ;
QUESTION            : '?' ;
COLON               : ':' ;
SEMI                : ';' ;
ASSIGN              : '=' ;
ADD_ASSIGN          : '+=' ;
SUB_ASSIGN          : '-=' ;
MUL_ASSIGN          : '*=' ;
MOD_ASSIGN          : '%=' ;
DIV_ASSIGN          : '/=' ;
XOR_ASSIGN          : '^=' ;
SHL_ASSIGN          : '<<=' ;
SHR_ASSIGN          : '>>=' ;
OR_ASSIGN           : '|=' ;
AND_ASSIGN          : '&=' ;

IF                  : 'if' ;
ELSE                : 'else' ;
FOR                 : 'for' ;
IN                  : 'in' ;
DO                  : 'do' ;
WHILE               : 'while' ;

BREAK               : 'break' ;
CONTINUE            : 'continue' ;
RETURN              : 'return' ;
KW_TRUE             : 'true' ;
KW_FALSE            : 'false' ;

IDENTIFIER          : L (L | D)* ;

PUREDEC_CONSTANT    : '#' D+ IS? ;
BIN_CONSTANT        : '0' [bB] B+ IS? ;

OCT_CONSTANT        : '0' [oO] O+ IS? 
                    | '0' O+ IS? 
                    ;

// 1. The 0x prefix (e.g., 0xBADBEEF).
// 2. The 'h' suffix (e.g., FFh, 123h).
// 3. The MASM-style bare hex: Starts with a digit, MUST contain at least one A-F.
HEX_CONSTANT        : HP H+ IS? 
                    | H+ IS? [hH] 
                    | D H* [a-fA-F] H* IS? 
                    ;
                    
DEC_CONSTANT        : D+ IS? ;

FLOAT_CONSTANT      : D+ E FS?
                    | D* '.' D+ E? FS?
                    | D+ '.' D* E? FS?
                    | HP H+ P FS?
                    | HP H* '.' H+ P FS?
                    | HP H+ '.' P FS?
                    ;
					
CHAR_CONSTANT       : '\'' .*? '\'' ;

WS                  : [ \t\u000B\r\n\f]+ -> skip ;
LINE_COMMENT        : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT       : '/*' .*? '*/' -> skip ;

// ==========================================
// FRAGMENTS
// ==========================================

fragment STR_BODY
            : '"""' .*? '"""'
            | '"' .*? '"'
            ;
fragment D  : [0-9] ;
fragment O  : [0-7] ;
fragment B  : [0-1] ;
fragment L  : [a-zA-Z_] ;
fragment H  : [a-fA-F0-9] ;
fragment HP : '0' [xX] ;
fragment E  : [Ee] [+-]? D+ ;
fragment P  : [Pp] [+-]? D+ ;
fragment FS : [fFlL] ;

fragment IS : [uU] ([lL] [lL]?)? 
            | ([lL] [lL]?) [uU]? 
            ;
