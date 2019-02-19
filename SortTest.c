#include <stdio.h>
#include <ElementType.h>
#include <Sort.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

bool check(ElementType es[], ElementType co[], int n, bool printornot)
{
    bool correct = TRUE;
    for (int i = 0; i < n; i++)
    {
        int k = CmpElement(es[i], co[i]);
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
bool testsort(ElementType es[], int n, void (*sort)(ElementType[], int, int (*)(ElementType, ElementType)), char *info, ElementType correct[])
{
    TEST(info, 1);
    ElementType *esc = copyes(es, n);
    clock_t begin = clock();
    sort(esc, n, CmpElement); //sort
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("using %lf s\n", time_spent);
    // printes(esc, n);
    //deal with wrong result
    bool right = check(esc, correct, n, false);
    printf("%s", right == true ? "pass\n" : "wrong\n");
    if (right == false)
    {
        printf("origin data and sorted");
        getchar();
        for (int i = 0; i < n; i += 1000)
        {
            PrintElement(es[i]);
            printf("\t");
            PrintElement(esc[i]);
            printf("\n");
        }
    }
    DestroyElementArray(esc, n);
    free(esc);
}
ElementType *_getes(int n)
{
    //public
    ElementType e;
    InitiateElement(&e, Tint);
    int x;

    //file access
    // FILE *f = fopen("./TestData/SortData.txt", "r");
    // if (!f)
    //     EXIT(ERROR, "open file failed");
    // fscanf(f, "%d", &n);
    // ElementType *es = MALLOC(sizeof(ElementType), n, "space error in sorttest");
    // for (int i = 0; i < n; i++)
    // {
    //     fscanf(f, "%d", &x);
    //     InitiateElement(es + i, Tint);
    //     SetValue(es[i], &x);
    // }

    //random access
    printf("how many randoms do you need?\n");
    // scanf("%d", &n);
    fflush(stdin);
    ElementType *es = MALLOC(sizeof(ElementType), n, "space error in sorttest");
    int i;
    for (i = 0; i < n; i += 1)
    {
        x = RANDOM(0, INT_MAX);
        // fscanf(f, "%d", &x);
        // x=1;
        for (int j = i; j < i + 1; j++)
        {
            InitiateElement(es + j, Tint);
            SetValue(es[j], &x);
        }
    }
    return es;
}
int main(void)
{
    while (true)
    {
        int n = 100000;
        ElementType *es = _getes(n);
        ElementType *esc = NULL;

        ElementType *co = copyes(es, n);
        MergeSort(co, n, CmpElement);
        //
        // testsort(es, n, InsertSort, "insertsort", co);
        // testsort(es, n, ShellSort, "shellsort", co);
        // testsort(es, n, BubbleSort, "bubblesort",co);
        testsort(es, n, QuickSort, "QuickSort", co);
        // testsort(es, n, SelectSort, "SelectSort", co);
        testsort(es, n, HeapSort, "HeapSort", co);
        testsort(es, n, KeySort, "KeySort", co);
        testsort(es, n, MergeSort, "MergeSort", co);
        DestroyElementArray(es, n);
        free(es);
        DestroyElementArray(co, n);
        free(co);
        printf("disposed es\n");
    }
    printf("\ntest over\n");
    getchar();
}