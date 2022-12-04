%{ 
  #include "tokens.h"
  #include "hash.h"
  int running = 1;
  int lineNumber = 1;
%}

%x COMMENT

%%

cara                return KW_CARA;
inte                return KW_INTE;
real                return KW_REAL;
se                  return KW_SE;
entaum              return KW_ENTAUM;
senaum              return KW_SENAUM;
enquanto            return KW_ENQUANTO;
entrada             return KW_ENTRADA;
escreva             return KW_ESCREVA;
retorne             return KW_RETORNE;


[-;\(\)\[\]\{\}=+*/<>&|~]	return yytext[0];

"<="                  return OPERATOR_LE;
">="                  return OPERATOR_GE;
"=="                  return OPERATOR_EQ;
"!="                  return OPERATOR_DIF;

[a-z._]+[a-z0-9._]* hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;
[0-9]*              hashInsert(yytext, LIT_INTEIRO); return LIT_INTEIRO;
[0-9]*\.[0-9]*      hashInsert(yytext, LIT_FLOAT); return LIT_FLOAT;
\'.\'               hashInsert(yytext, LIT_CHAR); return LIT_CHAR;
\"(\\.|[^"])*\"     hashInsert(yytext, LIT_STRING); return LIT_STRING;

" "
","
[ \t]
"\n"                ++lineNumber;
"///".*\n              BEGIN(COMMENT);
"//".*\n
.                   return TOKEN_ERROR;

<COMMENT>"\\\\\\"      BEGIN(INITIAL);
<COMMENT>"\n"       ++lineNumber;
<COMMENT>.

%%

#include "hash.c"
#include "main.c"

int yywrap() {
  running = 0;
  return 1;
}

int isRunning() {
    return running;
}

void initMe(){
	hashInit();
}

int getLineNumber(void) {
  return lineNumber;
}

