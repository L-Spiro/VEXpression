lexer grammar ExprLexer;

// ==========================================
// 1. TOKENS
// ==========================================

LPAREN              : '(' ;
RPAREN              : ')' ;
MUL                 : '*' ;
DIV                 : '/' ;
ADD                 : '+' ;
SUB                 : '-' ;

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

WS                  : [ \t\u000B\r\n\f]+ -> skip ;

// ==========================================
// 2. FRAGMENTS
// ==========================================

fragment D  : [0-9] ;
fragment O  : [0-7] ;
fragment B  : [0-1] ;
fragment L  : [a-zA-Z_] ;
fragment H  : [a-fA-F0-9] ;
fragment HP : '0' [xX] ;
fragment E  : [Ee] [+-]? D+ ;
fragment P  : [Pp] [+-]? D+ ;
fragment FS : [fFlL] ;

fragment IS : [uU] ('ll' | 'LL' | [lL])? 
            | ('ll' | 'LL' | [lL]) [uU]? 
            ;
