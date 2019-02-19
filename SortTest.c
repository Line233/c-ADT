#include <stdio.h>
#include <ElementType.h>
#include <Sort.h>
#include <time.h>
#include <stdbool.h>

bool check(ElementType es[], ElementType co[], int n, bool printornot)
{
    bool correct = TRUE;
    for (int i = 0; i < n; i++)
    {
        int k=CmpElement(es[i], co[i]);
        if (co != NULL && CmpElement(es[i], co[i]) != 0)
        {
            correct = false;
            if (printornot)
            {
                printf("*%d\t:", i);
                PrintElement(es[i]);
                printf("\tshould be  ");
                PrintElement(co[i]);
                printf("\n");
            }
        }
    }
    return correct;
}
bool printes(ElementType es[], int n)
{
    bool correct = TRUE;
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", i);
        PrintElement(es[i]);
        printf("\n");
    }
    printf("\n");
}
ElementType *copyes(ElementType es[], int n)
{
    ElementType *x = (ElementType *)MALLOC(sizeof(ElementType), n, "space error in sorttest");
    for (int i = 0; i < n; i++)
    {
        InitiateElement(x + i, Tint);
        CopyElement(x[i], es[i]);
    }
    return x;
}
void testsort(ElementType es[], int n, void (*sort)(ElementType[], int, int (*)(ElementType, ElementType)), char *info, ElementType correct[])
{
    TEST(info, 1);
    ElementType *esc = copyes(es, n);
    clock_t begin = clock();
    sort(esc, n, CmpElement); //sort
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("using %lf s\n", time_spent);

    printes(esc, n);
    bool right = check(esc, correct, n,true);
    printf("%s", right == true ? "pass\n" : "wrong\n");
    free(esc);
    /* here, do your time-consuming job */
}
int main(void)
{
    FILE *f = fopen("./TestData/SortData.txt", "r");
    if (!f)
        EXIT(ERROR, "open file failed");
    ElementType e;
    InitiateElement(&e, Tint);
    int n, x;
    // GET DATA
    fscanf(f, "%d", &n);
    ElementType *es = MALLOC(sizeof(ElementType), n, "space error in sorttest");
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &x);
        InitiateElement(es + i, Tint);
        SetValue(es[i], &x);
    }
    // n = 1000;
    // ElementType *es = MALLOC(sizeof(ElementType), n, "space error in sorttest");
    // for (int i = 0; i < n; i++)
    // {
    //     x = RANDOM(0, 1000);
    //     InitiateElement(es + i, Tint);
    //     SetValue(es[i], &x);
    // }
    printf("old order:\n");
    printes(es, n);
    ElementType *esc = NULL;

    ElementType *co = copyes(es, n);
    MergeSort(co, n, CmpElement);
    //
    // testsort(es, n, InsertSort, "insertsort");
    testsort(es, n, ShellSort, "shellsort", co);
    // testsort(es, n, BubbleSort, "bubblesort");
    testsort(es, n, QuickSort, "QuickSort", co);
    // testsort(es, n, SelectSort, "SelectSort");
    testsort(es, n, HeapSort, "HeapSort", co);
    testsort(es, n, MergeSort, "MergeSort", co);
    testsort(es, n, KeySort, "KeySort", co);

    printf("\ntest over\n");
    getchar();
}