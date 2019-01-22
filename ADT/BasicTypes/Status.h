//status
#ifndef _STATUS_h
#define _STATUS_h

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

void EXIT(int x,char s[]);
void TEST(char content[],int level);
void *MALLOC(int size, int num, char *errorinfo);
void IntiateIntArray(int* array,int n,int defaulti);

#endif