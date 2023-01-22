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

  yyparse();

  hashPrint();
  
  printf("Main done! File has %d lines\n", lineNumber);
  exit(0);
}
