#include <stdio.h>
#include <ElementType.h>
#include <Sort.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

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

    // file access
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
// void _exchange_es_x(int **es1, int **es2)
// {
//     int *tmp = *es1;
//     *es1 = *es2;
//     *es2 = tmp;
// }
// void sort(int *adds, int *tmpp, int n, int (*cmp)(int, int)) //small to big
// {
//     if (n == 1)
//     {
//         return;
//     }
//     else if (n == 2)
//     {
//         if (cmp(adds[0], adds[1]) > 0)
//         {
//             int tmp = adds[0];
//             adds[0] = adds[1];
//             adds[1] = tmp;
//         }

//         return;
//     }
//     else
//     {
//         sort(adds, tmpp, n / 2, cmp);
//         sort(adds + n / 2, tmpp, n - n / 2, cmp);
//         int j = 0, k = n / 2, i = 0;
//         for (; j < n / 2 && k < n; i++)
//         {
//             if (cmp(adds[j], adds[k]) < 0)
//             {
//                 tmpp[i] = adds[j];
//                 j++;
//             }
//             else
//             {
//                 tmpp[i] = adds[k];
//                 k++;
//             }
//         }
//         while (j < n / 2)
//         {
//             tmpp[i] = adds[j];
//             i++;
//             j++;
//         }
//         while (k < n)
//         {
//             tmpp[i] = adds[k];
//             i++;
//             k++;
//         }
//         for (int i = 0; i < n; i++)
//         {
//             adds[i] = tmpp[i];
//         }

//         return;
//     }
// }
// void mergesort(int es[],int n,int (*cmp)(int,int))
// {
//     int* tmp=MALLOC(sizeof(int),n,"");
//     sort(es,tmp,n,cmp);
// }
// int _seletpivot_x(int es[], int n, int (*cmp)(int, int))
// {
//     int m = (n) / 2;
//     int a = (*cmp)(es[0], es[m]) > 0 ? 1 : -1;
//     int b = (*cmp)(es[m], es[n - 1]) > 0 ? 1 : -1;
//     if (a + b != 0)
//         return m;
//     else
//     {
//         if (a == 1)
//             return (*cmp)(es[0], es[n - 1]) > 0 ? n - 1 : 0;
//         else
//             return (*cmp)(es[0], es[n - 1]) > 0 ? 0 : n - 1;
//     }
// }
// void _partition_x_bubble(int es[], int n, int big, int small, bool *inorder, int (*cmp)(int, int))
// {
//     if (big >= n)
//         EXIT(ERROR, "_partition_x_bubble");
//     if ((*cmp)(es[small], es[big]) > 0)
//     {
//         // _exchangeelem_x(es, small, big);
//         if (*inorder)
//             *inorder = false;
//     }
// }
// int _partition_x(int es[], int n, int pivot, int (*cmp)(int, int))
// {
//     int p = pivot;
//     int e;
//     // static bool first = true;
//     // if (first)
//     // {
//     //     InitiateElement(&e, Tint);
//     //     first = false;
//     // }
//     e = es[p];
//     int low = 0, high = n - 1;
//     bool isfirst;
//     while (low < high)
//     {
//         while (high > p && (*cmp)(es[high], e) >= 0)
//         {
//             // if (high + 1 < n)
//             //     _partition_x_bubble(es, n, high + 1, high, rinorder, cmp);
//             high--;
//         }
//         if (high != p)
//         {
//             es[p] = es[high];
//             p = high;
//         }
//         isfirst = true;
//         while (low < p && (*cmp)(es[low], e) <= 0)
//         {
//             // if (low - 1 >= 0)
//             //     _partition_x_bubble(es, n, low, low - 1, linorder, cmp);
//             low++;
//         }
//         if (low != p)
//         {
//             es[p] = es[low];
//             p = low;
//         }
//     }
//     es[p] = e;
//     return p;
// }
// void _exchangeelem_x(int es[], int i, int j)
// {
//     if (i == j)
//         return;
//     int x = es[i];
//     es[i] = es[j];
//     es[j] = x;
// }
// void quicksort_x(int es[], int n, int (*cmp)(int, int))
// {
//     if (n == 0 || n == 1)
//         return;
//     else if (n == 2)
//     {
//         if ((*cmp)(es[0], es[1]) > 0)
//             _exchangeelem_x(es, 0, 1);
//         return;
//     }
//     int p = _seletpivot_x(es, n, cmp);
//     bool linorder = false, rinorder = false;
//     p = _partition_x(es, n, p, cmp);
//     // printf("a:");
//     // _printes2(es,n);
//     int laster = n - p - 1;
//     if (p < laster)
//     {

//             quicksort_x(es, p, cmp);

//             quicksort_x(es + p + 1, n - p - 1, cmp);
//     }
//     else
//     {

//             quicksort_x(es + p + 1, n - p - 1, cmp);

//             quicksort_x(es, p, cmp);
//     }
// }
// int *getints(int n)
// {

//     printf("how many randoms do you need?\n");
//     // scanf("%d", &n);
//     fflush(stdin);
//     int *es = MALLOC(sizeof(int), n, "space error in sorttest");
//     int i;
//     int x;
//     for (i = 0; i < n; i += 1)
//     {
//         x = RANDOM(0, INT_MAX);
//         // fscanf(f, "%d", &x);
//         // x=1;
//         for (int j = i; j < i + 1; j++)
//         {
//             es[j] = x;
//         }
//     }
//     return es;
// }
// int *copyints(int *es, int n)
// {
//     int *co = (int *)MALLOC(sizeof(int), n, "getints");
//     for (int i = 0; i < n; i++)
//         co[i] = es[i];
//     return co;
// }
// int cmpint(int a, int b)
// {
//     return a - b;
// }
// bool checkx(int es[], int co[], int n, bool printornot)
// {
//     bool correct = TRUE;
//     for (int i = 0; i < n; i++)
//     {
//         int k = cmpint(es[i], co[i]);
//         if (co != NULL && cmpint(es[i], co[i]) != 0)
//         {
//             correct = false;
//             // if (printornot)
//             // {
//             //     printf("*%d\t:", i);
//             //     PrintElement(es[i]);
//             //     printf("\tshould be  ");
//             //     PrintElement(co[i]);
//             //     printf("\n");
//             // }
//         }
//     }
//     return correct;
// }
// bool testsortx(int es[], int n, void (*sort)(int[], int, int (*)(int, int)), char *info, int correct[])
// {
//     TEST(info, 1);
//     int *esc = copyints(es, n);
//     clock_t begin = clock();
//     sort(esc, n, cmpint); //sort
//     clock_t end = clock();
//     double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//     printf("using %lf s\n", time_spent);
//     // printes(esc, n);
//     //deal with wrong result
//     bool right = checkx(esc, correct, n, false);
//     printf("%s", right == true ? "pass\n" : "wrong\n");
//     // if (right == false)
//     // {
//     //     printf("origin data and sorted");
//     //     getchar();
//     //     for (int i = 0; i < n; i += 1000)
//     //     {
//     //         PrintElement(es[i]);
//     //         printf("\t");
//     //         PrintElement(esc[i]);
//     //         printf("\n");
//     //     }
//     // }
//     // DestroyElementArray(esc, n);
//     free(esc);
// }
int indexs(ElementType e, int i)
{
    if (e.t == Tint)
    {
        int x;
        GetValue(e, &x);
        return (x / ((int)(pow(10, i) + 0.5)) % 10);
    }
}

void radixsort_helper(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    RadixSort(es, n, 10, 10, indexs);
}
int main(void)
{
    while (true)
    {
        int n = 100000;
        ElementType *es = _getes(n);
        // printes(es, n);
        ElementType *esc = NULL;

        ElementType *co = copyes(es, n);
        MergeSort(co, n, CmpElement);
        //
        // testsort(es, n, InsertSort, "insertsort", co);
        // testsort(es, n, ShellSort, "shellsort", co);
        // testsort(es, n, BubbleSort, "bubblesort",co);
        testsort(es, n, QuickSort, "quicksort_x", co);
        // testsort(es, n, SelectSort, "SelectSort", co);
        // testsort(es, n, HeapSort, "HeapSort", co);
        // testsort(es, n, KeySort, "KeySort", co);
        testsort(es, n, MergeSort, "MergeSort", co);
        testsort(es, n, radixsort_helper, "radixsort_helper", co);
        DestroyElementArray(es, n);
        free(es);
        DestroyElementArray(co, n);
        free(co);
        printf("disposed es\n");
    }
    printf("\ntest over\n");
    getchar();
    // while (true)
    // {
    //     int n = 1000000;
    //     int *es = getints(n);
    //     int *esc = NULL;

    //     int *co = copyints(es, n);
    //     quicksort_x(co, n, cmpint);
    //     //
    //     testsortx(es, n, mergesort, "mergesort", co);
    //     testsortx(es, n, quicksort_x, "quicksort_x", co);
    //     free(es);
    //     free(co);
    //     printf("disposed es\n");
    // }
    // printf("\ntest over\n");
    // getchar();
}