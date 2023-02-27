// AST - Abstract Syntax Tree

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3) 
{
    AST *newnode = calloc(1, sizeof(AST));
    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;

    return newnode;
}

void astPrint(AST *node, int level)
{
    if(node == 0)
        return;

    for(int i=0; i<level; i++)
        fprintf(stderr, "  ");

    switch(node->type)
    {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
        case AST_DCLST: fprintf(stderr, "AST_DCLST"); break;
        case AST_ADD: fprintf(stderr, "AST_ADD"); break;
        case AST_SUB: fprintf(stderr, "AST_SUB"); break;
        case AST_VAR: fprintf(stderr, "AST_VAR"); break;
        case AST_VEC: fprintf(stderr, "AST_VEC"); break;
        case AST_VECVALUES: fprintf(stderr, "AST_VECVALUES"); break;
        case AST_VECVALUESINIT: fprintf(stderr, "AST_VECVALUESINIT"); break;
        case AST_FUN: fprintf(stderr, "AST_FUN"); break;
        case AST_INT: fprintf(stderr, "AST_INT"); break;
        case AST_FLOAT: fprintf(stderr, "AST_FLOAT"); break;
        case AST_CHAR: fprintf(stderr, "AST_CHAR"); break;
        case AST_BOOL: fprintf(stderr, "AST_BOOL"); break;
        case AST_MUL: fprintf(stderr, "AST_MUL"); break;
        case AST_DIV: fprintf(stderr, "AST_DIV"); break;
        case AST_LESS: fprintf(stderr, "AST_LESS"); break;
        case AST_GREAT: fprintf(stderr, "AST_GREAT"); break;
        case AST_OR: fprintf(stderr, "AST_OR"); break;
        case AST_AND: fprintf(stderr, "AST_AND"); break;
        case AST_NOT: fprintf(stderr, "AST_NOT"); break;
        case AST_LE: fprintf(stderr, "AST_LE"); break;
        case AST_GE: fprintf(stderr, "AST_GE"); break;
        case AST_EQ: fprintf(stderr, "AST_EQ"); break;
        case AST_DIF: fprintf(stderr, "AST_DIF"); break;
        case AST_FUNCALL: fprintf(stderr, "AST_FUNCALL"); break;
        case AST_VECACCESS: fprintf(stderr, "AST_VECACCESS"); break;
        case AST_EXPLST: fprintf(stderr, "AST_EXPLST"); break;
        case AST_RETURN: fprintf(stderr, "AST_RETURN"); break;
        case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
        case AST_PRINTLST: fprintf(stderr, "AST_PRINTLST"); break;
        case AST_READ: fprintf(stderr, "AST_READ"); break;
        case AST_IF: fprintf(stderr, "AST_IF"); break;
        case AST_ELSE: fprintf(stderr, "AST_ELSE"); break;
        case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
        case AST_LOOP: fprintf(stderr, "AST_LOOP"); break;
        case AST_PARAMLST: fprintf(stderr, "AST_PARAMLST"); break;
        case AST_PARAM: fprintf(stderr, "AST_PARAM"); break;
        case AST_ATR: fprintf(stderr, "AST_ATR"); break;
        case AST_AATR: fprintf(stderr, "AST_AATR"); break;
        case AST_CMDLST: fprintf(stderr, "AST_CMDLST"); break;
        case AST_BODY: fprintf(stderr, "AST_BODY"); break;
        case AST_PRINTLSTEND: fprintf(stderr, "AST_PRINTLSTEND"); break;
        case AST_PARENTHESIS: fprintf(stderr, "AST_PARENTHESIS"); break;
        default: fprintf(stderr, "Node type: %d", node->type); break;
    }

    if(node->symbol != 0)
        fprintf(stderr, ", %s\n", node->symbol->text);
    else
        fprintf(stderr, ", 0\n");

    for(int i=0; i<MAX_SONS; i++) {
        astPrint(node->son[i], level + 1);
    }

}
