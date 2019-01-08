//status
#ifndef _CODENODE_H
#define _CODENODE_H

typedef struct{
    char c;
    int a;//weight
    char* code;
} codenode;

void print_codenode(void *k);
int cmp_codenode(void *a, void *b);
void copy_codenode(void *copy, void *a);
void initiate_codenode(void *e);
void destroy_codenode(void* e);

#endif