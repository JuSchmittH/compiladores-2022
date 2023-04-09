#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

//lex.yy.h
int yylex();
extern int yyparse();
extern char *yytext;
extern FILE *yyin;
extern int lineNumber;

FILE *output;


int isRunning(void);
void initMe(void);
extern AST* getAst();

void decompile(AST *ast);

int main(int argc, char **argv) {
  int tok;
  if (argc < 2) {
    fprintf(stderr, "Call: ./etapa3.out file_name\n");
    exit(1);
  }
  yyin = fopen(argv[1], "r");

  initMe();

  yyparse();

  AST *ast = getAst();

  if(!(output = fopen(argv[2], "w"))){
    fprintf(stderr, "File not found: \"%s\"\n", argv[2]);
    exit(2);
  }

  decompile(ast);

  if(fclose(output) != 0){
    fprintf(stderr, "Cannot close file %s\n", argv[2]);
  }

  hashPrint();
  
  printf("Main done! File has %d lines\n", lineNumber);
  exit(0);
}

void decompile(AST *ast) {
  
  if(ast == 0)
    return;

  if(ast){

  //printf("ast type: %d\n", ast->type);

    switch(ast->type) {
      case AST_SYMBOL:
        fprintf(output, "%s ", ast->symbol->text);
        break;
      case AST_ADD:
        decompile(ast->son[0]);
        fprintf(output, " + "); 
        decompile(ast->son[1]);
        break;
      case AST_SUB:
        decompile(ast->son[0]);
        fprintf(output, " - ");
        decompile(ast->son[1]);
        break;
      case AST_MULT:
        decompile(ast->son[0]);
        fprintf(output, " * ");
        decompile(ast->son[1]);
        break;
      case AST_DIV:
        decompile(ast->son[0]);
        fprintf(output, " / ");
        decompile(ast->son[1]);
        break;
      case AST_LESS:
        decompile (ast->son[0]);
        fprintf(output, " < ");
        decompile(ast->son[1]);
        break;
      case AST_GREATER:
        decompile(ast->son[0]);
        fprintf(output, " > ");
        decompile(ast->son[1]);
        break;
      case AST_AND:
        decompile(ast->son[0]);
        fprintf(output, " & ");
        decompile(ast->son[1]);
        break;
      case AST_OR:
        decompile(ast->son[0]);
        fprintf(output, " | ");
        decompile(ast->son[1]);
        break;
      case AST_NOT:
        fprintf(output, "~");
        decompile(ast->son[0]);
        break;
      case AST_LE:
        decompile(ast->son[0]);
        fprintf(output, " <= ");
        decompile(ast->son[1]);
        break;
      case AST_GE:
        decompile(ast->son[0]);
        fprintf(output, " >= ");
        decompile(ast->son[1]);
        break;
      case AST_EQ:
        decompile(ast->son[0]);
        fprintf(output, " == ");
        decompile(ast->son[1]);
        break;
      case AST_DIFF:
        decompile(ast->son[0]);
        fprintf(output, " != ");
        decompile(ast->son[1]);
        break;
      case AST_PARENTESIS:
        fprintf(output, "(");
        decompile(ast->son[0]);
        fprintf(output, ")");
        break;
      case AST_IDENT:
        fprintf(output, "%s", ast->symbol->text);
        decompile(ast->son[0]);
      case AST_ENTRADA:
        fprintf(output, "entrada ");
        break;
      case AST_INDEXL:
        fprintf(output, "%s", ast->symbol->text); 
        fprintf(output, "[ ");
        decompile(ast->son[0]);
        fprintf(output, "] ");
        break;
      case AST_CARA:
        fprintf(output, "cara ");
        break;
      case AST_INTE:
        fprintf(output, "inte ");
        break;
      case AST_REAL:
        fprintf(output, "real ");
        break;
      case AST_PROGRAMA:
        decompile(ast->son[0]);
        decompile(ast->son[1]);
        break;
      case AST_GLOBALVARS:
        decompile(ast->son[0]);
        fprintf(output, ";\n");
        break;
      case AST_GLOBALVAR:
        decompile(ast->son[0]);
        fprintf(output, "%s = ", ast->symbol->text);
        decompile(ast->son[1]);
        break;
      case AST_VETDEC:
        decompile(ast->son[0]);
        fprintf(output, " %s[", ast->symbol->text);
        decompile(ast->son[1]);
        fprintf(output, "]");
        decompile(ast->son[2]);
        break;
      case AST_VETLIT:
        decompile(ast->son[0]);
        decompile(ast->son[1]);
        break;
      case AST_FUNC:
        decompile(ast->son[0]);
        fprintf(output, " %s (", ast->symbol->text);
        decompile(ast->son[1]);
        fprintf(output, ") ");
        decompile(ast->son[2]);
        break;
      case AST_PARAMETRO:
        decompile(ast->son[0]);
        fprintf(output, "  %s ", ast->symbol->text);
        break;
      case AST_PARAMIDENT:
        decompile(ast->son[0]);
        fprintf(output, "  %s ", ast->symbol->text);
        decompile(ast->son[1]);
        break;
      case AST_BLOCO:
        fprintf(output, "{\n");
        decompile(ast->son[0]);
        fprintf(output, "}\n");
        break;
      case AST_LCMD:
        decompile(ast->son[0]);
        decompile(ast->son[1]);
        break;
      case AST_TAIL:
        fprintf(output, ";\n");
        decompile(ast->son[0]);
        decompile(ast->son[1]);
        break;
      case AST_ATT:
        fprintf(output, "  %s =", ast->symbol->text);
        decompile(ast->son[0]);
        break;
      case AST_ATTVET:
        fprintf(output, " %s[", ast->symbol->text);
        decompile(ast->son[0]);
        fprintf(output, "] =");
        decompile(ast->son[1]);
        break;
      case AST_SE:
        fprintf(output, "entaum ");
        decompile(ast->son[0]);
        fprintf(output, "se ( ");
        decompile(ast->son[1]);
        fprintf(output, " )");
        break;
      case AST_SENAUM:
        fprintf(output, "entaum ");
        decompile(ast->son[0]);
        fprintf(output, "senaum ");
        decompile(ast->son[1]);
        fprintf(output, " se ( ");
        decompile(ast->son[2]);
        fprintf(output, " ) ");
        break;
      case AST_ENQUANTO:
        decompile(ast->son[0]);
        fprintf(output, "enquanto ( ");
        decompile(ast->son[1]);
        fprintf(output, " )");
        break;
      case AST_ESCREVA:
        fprintf(output, "escreva ");
        decompile(ast->son[0]);
        break;
      case AST_ESCREVAPARAMS:
        decompile(ast->son[0]);
        decompile(ast->son[1]);
        break;
      case AST_ESCREVAPARAM:
        decompile(ast->son[0]);
        decompile(ast->son[1]);
        break;
      case AST_ESCREVAVEC:
        fprintf(output, " %s", ast->symbol->text);
        decompile(ast->son[1]);
        break;
      case AST_RETORNE:
        fprintf(output, "retorne ");
        decompile(ast->son[0]);
        break;
      default: 
        printf("\n-------Error on decompile function--------\n"); 
        break;
    }
  }

  return;

}
