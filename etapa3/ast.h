// AST - Abstract Syntax Tree

#include "hash.h" 

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

#define AST_SYMBOL  1
#define AST_ADD 2
#define AST_SUB 3
#define AST_MULT 4
#define AST_DIV 5
#define AST_LESS 6
#define AST_GREATER 7
#define AST_AND 8
#define AST_OR 9
#define AST_NOT 10
#define AST_LE 11
#define AST_GE 12
#define AST_EQ 13
#define AST_DIFF 14
#define AST_PARENTESIS 15
#define AST_IDENT 16
#define AST_ENTRADA 17
#define AST_INDEXL 18
#define AST_CARA 19
#define AST_INTE 20
#define AST_REAL 21
#define AST_PROGRAMA 22
#define AST_GLOBALVARS 23
#define AST_GLOBALVAR 24
#define AST_VETDEC 25
#define AST_VETLIT 26
#define AST_FUNC 27
#define AST_PARAMETRO 28
#define AST_PARAMIDENT 29
#define AST_BLOCO 30
#define AST_LCMD 31
#define AST_TAIL 32
#define AST_ATT 33
#define AST_ATTVET 34
#define AST_SE 35
#define AST_SENAUM 36
#define AST_ENQUANTO 37
#define AST_ESCREVA 38
#define AST_ESCREVAPARAMS 39
#define AST_ESCREVAPARAM 40
#define AST_ESCREVAVEC 41
#define AST_RETORNE 42

typedef struct astnode {
    int type;
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);

#endif

// END OF FILE
