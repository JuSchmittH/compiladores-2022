#include <stdio.h>
#include <stdlib.h>

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;


int isRunning(void);
void initMe(void);

int main(int argc, char **argv) {
  int tok;
  if (argc < 2) {
    fprintf(stderr, "Call: ./etapa1.out file_name\n");
    exit(1);
  }
  yyin = fopen(argv[1], "r");

  initMe();

  while(running) {
      tok = yylex();
      if(running == 0) break;
      switch(tok)
      {
          case KW_CARA: printf("KW_CARA\n");
              break;
          case KW_INTE: printf("KW_INTE\n");
              break;
          case KW_REAL: printf("KW_REAL\n");
              break;
          case KW_SE: printf("KW_SE\n");
              break;
          case KW_ENTAUM: printf("KW_ENTAUM\n");
              break;
          case KW_SENAUM: printf("KW_SENAUM\n");
              break;
          case KW_ENQUANTO: printf("KW_ENQUANTO\n");
              break;
          case KW_ENTRADA: printf("KW_ENTRAD\n");
              break;
          case KW_ESCREVA: printf("KW_ESCREVA\n");
              break;
          case KW_RETORNE: printf("KW_RETORNE\n");
              break;
          case OPERATOR_LE: printf("OPERATOR_LE\n");
              break;
          case OPERATOR_GE: printf("OPERATOR_GE\n");
              break;
          case OPERATOR_EQ: printf("OPERATOR_EQ\n");
              break;
          case OPERATOR_DIF: printf("OPERATOR_DIF\n");
              break;
          case TK_IDENTIFIER: printf("TK_IDENTIFIER\n");
              break;
          case LIT_INTEIRO: printf("LIT_INTEIRO\n");
              break;
          case LIT_FLOAT: printf("LIT_FLOAT\n");
              break;
          case LIT_CHAR: printf("LIT_CHAR\n");
              break;
          case LIT_STRING: printf("LIT_STRING\n");
              break;
          case TOKEN_ERROR: printf("Unexpected token %d\n", tok);
              break;
          default: printf("Encontrei %c\n", yytext[0]);
              break; 
      }

  }
  printf("Main done! File has %d lines\n", lineNumber);
  hashPrint();
  exit(0);
}
