// AST - Abstract Syntax Tree

#include "hash.h" 

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_DCLST 40
#define AST_VAR 2
#define AST_VEC 3
#define AST_FUN 4
#define AST_INT 5
#define AST_FLOAT 6
#define AST_CHAR 7
#define AST_BOOL 8
#define AST_ADD 9
#define AST_SUB 10
#define AST_MUL 11
#define AST_DIV 12
#define AST_LESS 13
#define AST_GREAT 14
#define AST_OR 15
#define AST_AND 16
#define AST_NOT 17
#define AST_LE 18
#define AST_GE 19
#define AST_EQ 20
#define AST_DIF 21
#define AST_FUNCALL 22
#define AST_VECACCESS 23
#define AST_EXPLST 24
#define AST_RETURN 25
#define AST_PRINT 26
#define AST_PRINTLST 27
#define AST_READ 28
#define AST_IF 29
#define AST_ELSE 30
#define AST_WHILE 31
#define AST_LOOP 32
#define AST_PARAMLST 33
#define AST_PARAM 34
#define AST_ATR 35
#define AST_AATR 36
#define AST_CMDLST 37
#define AST_BODY 38
#define AST_PRINTLSTEND 39
#define AST_VECVALUES 41
#define AST_VECVALUESINIT 42
#define AST_PARENTHESIS 43

typedef struct astnode
{
    int type;
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);

#endif
