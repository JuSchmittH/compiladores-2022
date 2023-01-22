%{
  int yyerror();
%}


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

%token TK_IDENTIFIER     

%token LIT_INTEIRO       
%token LIT_FLOAT         
%token LIT_CHAR          
%token LIT_STRING   

%token TOKEN_ERROR

%left '&' '|' '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%%

programa: globalvars programa
    |
    ;

globalvars: globalvar ';'
    | func
    ;

globalvar: tipo TK_IDENTIFIER '=' literal
    | tipo TK_IDENTIFIER '[' LIT_INTEIRO ']' vetor
    ;

vetor: valorvetor
    |
    ;

valorvetor: literal valorvetor
    |
    ;
  
func: tipo TK_IDENTIFIER '(' parametrosl ')' bloco
    ;

parametrosl: parametro
    |
    ;

parametro: tipo TK_IDENTIFIER
    | tipo TK_IDENTIFIER parametro
    ;

bloco: '{' lcmd '}'
    ;

lcmd: cmd
    | cmd ';' lcmd
    ;

cmd: attcmd
    | fluxocmd
    | escrevacmd
    | retornecmd
    | bloco
    |
    ;

attcmd: TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER '[' expr ']' '=' expr
    ;

fluxocmd: KW_ENTAUM cmd KW_SE '(' expr ')'
    | KW_ENTAUM cmd KW_SENAUM cmd KW_SE '(' expr ')'
    | cmd KW_ENQUANTO '(' expr ')'
    ;

escrevacmd: KW_ESCREVA escrevaparams
    ;

escrevaparams: escrevaparam
    | escrevaparam escrevaparams
    |
    ;

escrevaparam: expr
    | LIT_STRING
    ;

params: param
    | param params
    ;

param: expr
    |
    ;

retornecmd: KW_RETORNE expr
    ;

expr: TK_IDENTIFIER 
    | TK_IDENTIFIER '[' expr ']' 
    | literal
    | expr '+' expr 
    | expr '-' expr 
    | expr '*' expr 
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr 
    | expr '|' expr
    | expr '&' expr
    | '~' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr 
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | '(' expr ')'
    | TK_IDENTIFIER '(' params ')'
    | KW_ENTRADA
	  ;

literal: LIT_INTEIRO
    | LIT_FLOAT
    | LIT_CHAR
    ;

tipo: KW_CARA
    | KW_INTE
    | KW_REAL
    ;

%%

int yyerror() {
  fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
  exit(3);
}