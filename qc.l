%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "tree.h"
#include "y.tab.h"
%}

identifier  [a-zA-Z]+
number      [0-9]+
whitespace  [ \t]+

%%

"def"           { fprintf( stderr, "[DEF]" ); return DEF; }
"var"           { fprintf( stderr, "[VAR]" ); return VAR; }
"array"         { fprintf( stderr, "[ARRAY]" ); return ARRAY; }
"of"            { fprintf( stderr, "[OF]" ); return OF; }
"integral"      { fprintf( stderr, "[INTEGRAL]" ); return INTEGRAL; }
"rational"      { fprintf( stderr, "[RATIONAL]" ); return RATIONAL; }
"begin"         { fprintf( stderr, "[BEGIN]" ); return BBEGIN; }
"end"           { fprintf( stderr, "[END]" ); return END; }
"if"            { fprintf( stderr, "[IF]" ); return IF; }
"then"          { fprintf( stderr, "[THEN]" ); return THEN; }
"else"          { fprintf( stderr, "[ELSE]" ); return ELSE; }
"while"         { fprintf( stderr, "[WHILE]" ); return WHILE; }
"do"            { fprintf( stderr, "[DO]" ); return DO; }
{identifier}    { fprintf( stderr, "[ID:%s]", yylval.sval = make_list(yytext) ); return ID; }
{number}        { fprintf( stderr, "[INUM:%d]", yylval.ival = atoi(yytext) ); return INUM; }
{number}"."{number}     { fprintf( stderr, "[RNUM:%f]", yylval.rval = atof(yytext) ); return RNUM; }
{whitespace}    { ; }
":="            { fprintf( stderr, "[ASSIGNOP]" ); return ASSIGNOP; }
"<"             { fprintf( stderr, "[RELOP:%d]", yylval.opval = LT ); return RELOP; }
"<="            { fprintf( stderr, "[RELOP:%d]", yylval.opval = LE ); return RELOP; }
">"             { fprintf( stderr, "[RELOP:%d]", yylval.opval = GT ); return RELOP; }
">="            { fprintf( stderr, "[RELOP:%d]", yylval.opval = GE ); return RELOP; }
"<>"            { fprintf( stderr, "[RELOP:%d]", yylval.opval = NE ); return RELOP; }
"="             { fprintf( stderr, "[RELOP:%d]", yylval.opval = EQ ); return RELOP; }
"+"             { fprintf( stderr, "[ADDOP:%d]", yylval.opval = PLUS ); return ADDOP; }
"-"             { fprintf( stderr, "[ADDOP:%d]", yylval.opval = MINUS ); return ADDOP; }
"or"            { fprintf( stderr, "[ADDOP:%d]", yylval.opval = OR ); return ADDOP; }
"*"             { fprintf( stderr, "[MULOP:%d]", yylval.opval = STAR ); return MULOP; }
"/"             { fprintf( stderr, "[MULOP:%d]", yylval.opval = SLASH ); return MULOP; }
"div"           { fprintf( stderr, "[MULOP:%d]", yylval.opval = DIV ); return MULOP; }
"mod"           { fprintf( stderr, "[MULOP:%d]", yylval.opval = MOD ); return MULOP; }
"and"           { fprintf( stderr, "[MULOP:%d]", yylval.opval = AND ); return MULOP; }
"("             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
")"             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
"["             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
"]"             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
":"             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
";"             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
","             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
".."            { fprintf( stderr, "[DOTDOT]" ); return DOTDOT; }
"."             { fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
\n              { fprintf( stderr, "\n"); }
.               { fprintf( stderr, "<%c>", yytext[0] ); return yytext[0]; }

%%

int yyerror( char *message )
{
    fprintf( stderr, "ERROR: %s\n", message );
    exit(1);
}