#include <Sort.h>
#include <ElementType.h>
#include <math.h>
#include <stdbool.h>
void printes2(ElementType es[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", i);
        PrintElement(es[i]);
        printf("\n");
    }
}
int rightposition_straight(ElementType es[], int n, ElementType e, int d)
{
    if (n < 1)
        return 0;
    int i = n - d;
    for (; i >= 0; i -= d)
    {
        if (CmpElement(es[i], e) <= 0)
            return i + d;
    }
    return i + d;
}

int rightposition_binary(ElementType es[], int n, ElementType e)
{
    if (n < 1)
        return 0;
    int a = 0, b = n - 1, m;
    while (a < b)
    {
        m = (a + b) / 2;
        if (CmpElement(es[m], e) > 0)
        {
            b = m - 1;
        }
        else
        {
            a = m + 1;
        }
    }
    if (CmpElement(es[a], e) < 0)
    {
        return a + 1;
    }
    else
    {
        return a;
    }
}
void move(ElementType es[], int n, int from, int to, int d)
{
    if (n <= from || n <= to || (from - to) % d != 0)
        EXIT(ERROR, "error whent move");
    void *x = es[from].content;
    if (from > to)
    {
        for (int i = from; i > to; i -= d)
        {
            es[i].content = es[i - d].content;
        }
        es[to].content = x;
    }
    else
    {
        for (int i = from; i < to; i += d)
        {
            es[i].content = es[i + d].content;
        }
        es[to].content = x;
    }
}
void InsertSort(ElementType es[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int k;
        // k = rightposition_straight(es, i, es[i], 1);
        k = rightposition_binary(es, i, es[i]);
        move(es, n, i, k, 1);
        // printf("\n%d:\n",i);
        // printes2(es,n);
    }
}

void shellsort_helper(ElementType es[], int n, int d)
{
    for (int i = d; i < n; i++)
    {
        // int k = rightposition_straight(es, i, es[i]);
        int k = rightposition_straight(es, i, es[i], d);
        move(es, n, i, k, d);
        // printf("\n%d:\n",i);
        // printes2(es,n);
    }
}
void ShellSort(ElementType es[], int n)
{
    int k = (int)log2(n + 1);
    for (int i = 1; i <= k; i++)
    {
        int d = (int)pow(2, k - i);
        shellsort_helper(es, n, d);
    }
}
void exchangeelem(ElementType es[], int i, int j)
{
    void *x = es[i].content;
    es[i].content = es[j].content;
    es[j].content = x;
}
void BubbleSort(ElementType es[], int n)
{
    bool inorder;
    for (int i = n - 1; i > 0; i--)
    {
        inorder = TRUE;
        for (int j = 0; j < i; j++)
        {
            if (CmpElement(es[j], es[j + 1]) > 0)
            {
                exchangeelem(es, j, j + 1);
                if (inorder)
                    inorder = false;
            }
        }
        if (inorder)
            return;
    }
}
int seletpivot(ElementType es[], int n)
{
    int m = (n) / 2;
    int a = CmpElement(es[0], es[m]) > 0 ? 1 : -1;
    int b = CmpElement(es[m], es[n - 1]) > 0 ? 1 : -1;
    if (a + b != 0)
        return m;
    else
    {
        if (a == 1)
            return CmpElement(es[0], es[n - 1]) > 0 ? n - 1 : 0;
        else
            return CmpElement(es[0], es[n - 1]) > 0 ? 0 : n - 1;
    }
}
void partition_bubble(ElementType es[], int big, int small, bool *inorder, bool *isfirst)
{
    if (!*isfirst && CmpElement(es[small], es[big]) > 0)
    {
        exchangeelem(es, small, big);
        if (*inorder)
            *inorder = false;
    }
    if (*isfirst)
        *isfirst = false;
}
int partition(ElementType es[], int n, int pivot, bool *linorder, bool *rinorder)
{
    int p = pivot;
    *linorder = *rinorder = true;
    ElementType e;
    InitiateElement(&e, Tint);
    e.content = es[p].content;
    int low = 0, high = n - 1;
    bool isfirst;
    while (low < high)
    {
        isfirst = true;
        while (high > p && CmpElement(es[high], e) >= 0)
        {
            partition_bubble(es, high + 1, high, linorder, &isfirst);
            high--;
        }
        if (high != p)
        {
            es[p].content = es[high].content;
            p = high;
        }
        isfirst = true;
        while (low < p && CmpElement(es[low], e) <= 0)
        {
            partition_bubble(es, low, low - 1, rinorder, &isfirst);
            low++;
        }
        if (low != p)
        {
            es[p].content = es[low].content;
            p = low;
        }
    }
    es[p].content = e.content;
    return p;
}
void QuickSort(ElementType es[], int n)
{
    if (n == 0 || n == 1)
        return;
    else if (n == 2)
    {
        if (CmpElement(es[0], es[1]) > 0)
            exchangeelem(es, 0, 1);
        return;
    }
    int p = seletpivot(es, n);
    bool linorder = false, rinorder = false;
    p = partition(es, n, p, &linorder, &rinorder);
    int laster = n - p - 1;
    if (p < laster)
    {
        if (!linorder)
            QuickSort(es, p);
        if (!rinorder)
            QuickSort(es + p + 1, n - p - 1);
    }
    else
    {
        if (!rinorder)
            QuickSort(es + p + 1, n - p - 1);
        if (!linorder)
            QuickSort(es, p);
    }
}