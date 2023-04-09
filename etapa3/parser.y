%{
    #include "ast.h"
    #include <stdlib.h>
    #include <stdio.h>
    
    int getLineNumber(void);
	int yyerror();
    int yylex();

    AST *initNode;
%}

%union
{
    HASH_NODE *symbol;
    AST *ast;
}


%token KW_CARA           
%token KW_INTE           
%token KW_REAL           

%token KW_SE             
%token KW_ENTAUM         
%token KW_SENAUM         
%token KW_ENQUANTO       
%token KW_ENTRADA        
%token KW_ESCREVA        
%token KW_RETORNE        

%token OPERATOR_LE       
%token OPERATOR_GE       
%token OPERATOR_EQ       
%token OPERATOR_DIF      

%token<symbol> TK_IDENTIFIER     

%token<symbol> LIT_INTEIRO       
%token<symbol> LIT_FLOAT         
%token<symbol> LIT_CHAR          
%token<symbol> LIT_STRING   

%token TOKEN_ERROR

%type<ast> init
%type<ast> programa
%type<ast> globalvars
%type<ast> globalvar
%type<ast> vetor
%type<ast> valorvetor
%type<ast> func
%type<ast> parametrosl
%type<ast> parametro
%type<ast> bloco
%type<ast> lcmd
%type<ast> tail
%type<ast> cmd
%type<ast> attcmd
%type<ast> fluxocmd
%type<ast> escrevacmd
%type<ast> escrevaparams
%type<ast> escrevaparam
%type<ast> retornecmd
%type<ast> expr
%type<ast> literal
%type<ast> tipo

%left '&' '|' '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%%

init: programa                                       { initNode = $$; astPrint(initNode, 0); }

programa: globalvars programa                        { $$ = astCreate(AST_PROGRAMA, 0, $1, $2, 0, 0); }
    |                                                { $$ = 0; }
    ;

globalvars: globalvar ';'                            { $$ = astCreate(AST_GLOBALVARS, 0, $1, 0, 0, 0); }
    | func                                           { $$ = $1; }
    ;

globalvar: tipo TK_IDENTIFIER '=' literal            { $$ = astCreate(AST_GLOBALVAR, $2, $1, $4, 0, 0); }
    | tipo TK_IDENTIFIER '[' LIT_INTEIRO ']' vetor   { $$ = astCreate(AST_VETDEC, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $6, 0); }
    ;

vetor: valorvetor                                    { $$ = $1; }
    |                                                { $$ = 0; }
    ;

valorvetor: literal valorvetor                       { $$ = astCreate(AST_VETLIT, 0, $1, $2, 0, 0);}
    |                                                { $$ = 0; }
    ;
  
func: tipo TK_IDENTIFIER '(' parametrosl ')' bloco   { $$ = astCreate(AST_FUNC, $2, $1, $4, $6, 0); }
    ;

parametrosl: parametro                               { $$ = $1; }
    |                                                { $$ = 0; }
    ;

parametro: tipo TK_IDENTIFIER                        { $$ = astCreate(AST_PARAMETRO, $2, $1, 0, 0, 0);}
    | tipo TK_IDENTIFIER parametro                   { $$ = astCreate(AST_PARAMIDENT, $2, $1, $3, 0, 0);}
    ;

bloco: '{' lcmd '}'                                  { $$ = astCreate(AST_BLOCO, 0, $2, 0, 0, 0);}
    ;

lcmd: cmd tail                                       { $$ = astCreate(AST_LCMD, 0, $1, $2, 0, 0); }                                   
    ;

tail: ';' cmd tail                                  { $$ = astCreate(AST_TAIL, 0, $2, $3, 0, 0);}
    |                                               { $$ = 0; }
    ;

cmd: attcmd                                          { $$ = $1; }
    | fluxocmd                                       { $$ = $1; }
    | escrevacmd                                     { $$ = $1; }
    | retornecmd                                     { $$ = $1; }
    | bloco                                          { $$ = $1; }
    |                                                { $$ = 0; }
    ;

attcmd: TK_IDENTIFIER '=' expr                       { $$ = astCreate(AST_ATT, $1, $3, 0, 0, 0);}
    | TK_IDENTIFIER '[' expr ']' '=' expr            { $$ = astCreate(AST_ATTVET, $1, $3, $6, 0, 0);}
    ;

fluxocmd: KW_ENTAUM cmd KW_SE '(' expr ')'           { $$ = astCreate(AST_SE, 0, $2, $5, 0, 0);}
    | KW_ENTAUM cmd KW_SENAUM cmd KW_SE '(' expr ')' { $$ = astCreate(AST_SENAUM, 0, $2, $4, $7, 0);}
    | cmd KW_ENQUANTO '(' expr ')'                   { $$ = astCreate(AST_ENQUANTO, 0, $1, $4, 0, 0);}
    ;

escrevacmd: KW_ESCREVA escrevaparams                 { $$ = astCreate(AST_ESCREVA, 0, $2, 0, 0, 0);}
    ;

escrevaparams: escrevaparam                          { $$ = $1}
    | escrevaparam escrevaparams                     { $$ = astCreate(AST_ESCREVAPARAMS, 0, $1, $2, 0, 0);}
    |                                                { $$ = 0; }
    ;

escrevaparam: expr                                   { $$ = $1}
    | LIT_STRING                                     { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    ;

retornecmd: KW_RETORNE expr                          { $$ = astCreate(AST_RETORNE, 0, $2, 0, 0, 0); }
    ;

expr: TK_IDENTIFIER                                  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
    | TK_IDENTIFIER '[' expr ']'                     { $$ = astCreate(AST_INDEXL, $1, $3, 0, 0, 0); } 
    | literal                                        { $$ = $1; }
    | expr '+' expr                                  { $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }  
    | expr '-' expr                                  { $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0); }  
    | expr '*' expr                                  { $$ = astCreate(AST_MULT, 0, $1, $3, 0, 0); }  
    | expr '/' expr                                  { $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }  
    | expr '<' expr                                  { $$ = astCreate(AST_LESS, 0, $1, $3, 0, 0); }  
    | expr '>' expr                                  { $$ = astCreate(AST_GREATER, 0, $1, $3, 0, 0); }  
    | expr '|' expr                                  { $$ = astCreate(AST_OR, 0, $1, $3, 0, 0); }  
    | expr '&' expr                                  { $$ = astCreate(AST_AND, 0, $1, $3, 0, 0); }  
    | '~' expr                                       { $$ = astCreate(AST_NOT, 0, $2, 0, 0, 0); }
    | expr OPERATOR_LE expr                          { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }  
    | expr OPERATOR_GE expr                          { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }  
    | expr OPERATOR_EQ expr                          { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }  
    | expr OPERATOR_DIF expr                         { $$ = astCreate(AST_DIFF, 0, $1, $3, 0, 0); }  
    | '(' expr ')'                                   { $$ = astCreate(AST_PARENTESIS, 0, $2, 0, 0, 0); }
    | TK_IDENTIFIER expr                             { $$ = astCreate(AST_IDENT, $1, $2, 0, 0, 0); } 
    | KW_ENTRADA                                     { $$ = astCreate(AST_ENTRADA, 0, 0, 0, 0, 0); }
	  ;

literal: LIT_INTEIRO                                 { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
    | LIT_FLOAT                                      { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
    | LIT_CHAR                                       { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); } 
    ;

tipo: KW_CARA                                        { $$ = astCreate(AST_CARA, 0, 0, 0, 0, 0); } 
    | KW_INTE                                        { $$ = astCreate(AST_INTE, 0, 0, 0, 0, 0); } 
    | KW_REAL                                        { $$ = astCreate(AST_REAL, 0, 0, 0, 0, 0); } 
    ;

%%

int yyerror() {
  fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
  exit(3);
}

AST *getAst(){
    return initNode;
}