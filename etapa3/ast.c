// AST - Abstract Syntax Tree

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3) {
    AST* newnode = (AST*) calloc(1, sizeof(AST));
    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;
    return newnode;
}

void astPrint(AST *node, int level) {
    if(node == 0)
        return;

    for(int i=0; i<level; i++)
        fprintf(stderr, "  ");

    switch(node->type) {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
        case AST_ADD: fprintf(stderr, "AST_ADD"); break;
        case AST_SUB: fprintf(stderr, "AST_SUB"); break;
        case AST_MULT: fprintf(stderr, "AST_MULT"); break;
        case AST_DIV: fprintf(stderr, "AST_DIV"); break;
        case AST_LESS: fprintf(stderr, "AST_LESS"); break;
        case AST_GREATER: fprintf(stderr, "AST_GREATER"); break;
        case AST_AND: fprintf(stderr, "AST_AND"); break;
        case AST_OR: fprintf(stderr, "AST_OR"); break;
        case AST_NOT: fprintf(stderr, "AST_NOT"); break;
        case AST_LE: fprintf(stderr, "AST_LE"); break;
        case AST_GE: fprintf(stderr, "AST_GE"); break;
        case AST_EQ: fprintf(stderr, "AST_EQ"); break;
        case AST_DIFF: fprintf(stderr, "AST_DIFF"); break;
        case AST_PARENTESIS: fprintf(stderr, "AST_PARENTESIS"); break;
        case AST_IDENT: fprintf(stderr, "AST_IDENT"); break;
        case AST_ENTRADA: fprintf(stderr, "AST_ENTRADA"); break;
        case AST_INDEXL: fprintf(stderr, "AST_INDEXL"); break;
        case AST_CARA: fprintf(stderr, "AST_CARA"); break;
        case AST_INTE: fprintf(stderr, "AST_INTE"); break;
        case AST_REAL: fprintf(stderr, "AST_REAL"); break;
        case AST_PROGRAMA: fprintf(stderr, "AST_PROGRAMA"); break;
        case AST_GLOBALVARS: fprintf(stderr, "AST_GLOBALVARS"); break;
        case AST_GLOBALVAR: fprintf(stderr, "AST_GLOBALVAR"); break;
        case AST_VETDEC: fprintf(stderr, "AST_VETDEC"); break;
        case AST_VETLIT: fprintf(stderr, "AST_VETLIT"); break;
        case AST_FUNC: fprintf(stderr, "AST_FUNC"); break;
        case AST_PARAMETRO: fprintf(stderr, "AST_PARAMETRO"); break;
        case AST_PARAMIDENT: fprintf(stderr, "AST_PARAMIDENT"); break;
        case AST_BLOCO: fprintf(stderr, "AST_BLOCO"); break;
        case AST_LCMD: fprintf(stderr, "AST_LCMD"); break;
        case AST_TAIL: fprintf(stderr, "AST_TAIL"); break;
        case AST_ATT: fprintf(stderr, "AST_ATT"); break;
        case AST_ATTVET: fprintf(stderr, "AST_ATTVET"); break;
        case AST_SE: fprintf(stderr, "AST_SE"); break;
        case AST_SENAUM: fprintf(stderr, "AST_SENAUM"); break;
        case AST_ENQUANTO: fprintf(stderr, "AST_ENQUANTO"); break;
        case AST_ESCREVA: fprintf(stderr, "AST_ESCREVA"); break;
        case AST_ESCREVAPARAMS: fprintf(stderr, "AST_ESCREVAPARAMS"); break;
        case AST_RETORNE: fprintf(stderr, "AST_RETORNE"); break;
        default: fprintf(stderr, "AST_UNKNOWN"); break;
    }

    if(node->symbol != 0){
        fprintf(stderr, ", %s\n", node->symbol->text);
    } else {
        fprintf(stderr, ", 0\n");
    }

    for(int i=0; i<MAX_SONS; i++) {
        astPrint(node->son[i], level + 1);
    }

}

// END OF FILE
