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
int RANDOM(int a,int b);
int *GetIntArray(int n, int max, int min);
void PrintIntArray_Tool(int ints[],int n,char* s);

#endif