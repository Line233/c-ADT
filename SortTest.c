#include <stdio.h>
#include <ElementType.h>
#include <Sort.h>

void printes(ElementType es[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", i);

        PrintElement(es[i]);
        printf("\n");
    }
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
void testsort(ElementType es[], int n, void (*sort)(ElementType[], int, int (*)(ElementType, ElementType)), char *info)
{
    TEST(info, 1);
    ElementType *esc = copyes(es, n);
    sort(esc, n, CmpElement);
    printes(esc, n);
    free(esc);
}
int main(void)
{
    FILE *f = fopen("./TestData/SortData.txt", "r");
    if (!f)
        EXIT(ERROR, "open file failed");
    ElementType e;
    InitiateElement(&e, Tint);
    int n, x;
    //GET DATA
    fscanf(f, "%d", &n);
    ElementType *es = MALLOC(sizeof(ElementType), n, "space error in sorttest");
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &x);
        InitiateElement(es + i, Tint);
        SetValue(es[i], &x);
    }
    printf("old order:\n");
    printes(es, n);
    ElementType *esc = NULL;

    //
    testsort(es, n, InsertSort, "insertsort");
    testsort(es, n, ShellSort, "shellsort");
    testsort(es, n, BubbleSort, "bubblesort");
    testsort(es, n, QuickSort, "QuickSort");
    testsort(es, n, SelectSort, "SelectSort");
    testsort(es, n, HeapSort, "HeapSort");

    getchar();
}