#include <Sort.h>
#include <ElementType.h>
#include <math.h>
#include <stdbool.h>
#include <Queue.h>
void _printes2(ElementType es[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", i);
        PrintElement(es[i]);
        printf("\n");
    }
}
int _rightposition_straight(ElementType es[], int n, ElementType e, int d, int (*cmp)(ElementType, ElementType))
{
    if (n < 1)
        return 0;
    int i = n - d;
    for (; i >= 0; i -= d)
    {
        if ((*cmp)(es[i], e) <= 0)
            return i + d;
    }
    return i + d;
}

int _rightposition_binary(ElementType es[], int n, ElementType e, int (*cmp)(ElementType, ElementType))
{
    if (n < 1)
        return 0;
    int a = 0, b = n - 1, m;
    while (a < b)
    {
        m = (a + b) / 2;
        if ((*cmp)(es[m], e) > 0)
        {
            b = m - 1;
        }
        else
        {
            a = m + 1;
        }
    }
    if ((*cmp)(es[a], e) < 0)
    {
        return a + 1;
    }
    else
    {
        return a;
    }
}
void _move(ElementType es[], int n, int from, int to, int d)
{
    if (n <= from || n <= to || (from - to) % d != 0)
        EXIT(ERROR, "error whent _move");
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
void InsertSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    for (int i = 1; i < n; i++)
    {
        int k;
        // k = _rightposition_straight(es, i, es[i], 1,cmp);
        k = _rightposition_binary(es, i, es[i], cmp);
        _move(es, n, i, k, 1);
        // printf("\n%d:\n",i);
        // _printes2(es,n);
    }
}

void _shellsort_helper(ElementType es[], int n, int d, int (*cmp)(ElementType, ElementType))
{
    for (int i = d; i < n; i++)
    {
        // int k = _rightposition_straight(es, i, es[i]);
        int k = _rightposition_straight(es, i, es[i], d, cmp);
        _move(es, n, i, k, d);
        // printf("\n%d:\n",i);
        // _printes2(es,n);
    }
}
void ShellSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    int k = (int)log2(n + 1);
    for (int i = 1; i <= k; i++)
    {
        int d = (int)pow(2, k - i);
        _shellsort_helper(es, n, d, cmp);
    }
}
void _exchangeelem(ElementType es[], int i, int j)
{
    if (i == j)
        return;
    void *x = es[i].content;
    es[i].content = es[j].content;
    es[j].content = x;
}
void BubbleSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    bool inorder;
    for (int i = n - 1; i > 0; i--)
    {
        inorder = TRUE;
        for (int j = 0; j < i; j++)
        {
            if ((*cmp)(es[j], es[j + 1]) > 0)
            {
                _exchangeelem(es, j, j + 1);
                if (inorder)
                    inorder = false;
            }
        }
        if (inorder)
            return;
    }
}
int _seletpivot(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    int m = (n) / 2;
    int a = (*cmp)(es[0], es[m]) > 0 ? 1 : -1;
    int b = (*cmp)(es[m], es[n - 1]) > 0 ? 1 : -1;
    if (a + b != 0)
        return m;
    else
    {
        if (a == 1)
            return (*cmp)(es[0], es[n - 1]) > 0 ? n - 1 : 0;
        else
            return (*cmp)(es[0], es[n - 1]) > 0 ? 0 : n - 1;
    }
}
void _partition_bubble(ElementType es[], int n, int big, int small, bool *inorder, int (*cmp)(ElementType, ElementType))
{
    if (big >= n)
        EXIT(ERROR, "_partition_bubble");
    if ((*cmp)(es[small], es[big]) > 0)
    {
        // _exchangeelem(es, small, big);
        if (*inorder)
            *inorder = false;
    }
}
int _partition(ElementType es[], int n, int pivot, bool *linorder, bool *rinorder, int (*cmp)(ElementType, ElementType))
{
    int p = pivot;
    *linorder = *rinorder = true;
    ElementType e;
    e.t = Tint;
    // static bool first = true;
    // if (first)
    // {
    //     InitiateElement(&e, Tint);
    //     first = false;
    // }
    e.content = es[p].content;
    int low = 0, high = n - 1;
    bool isfirst;
    while (low < high)
    {
        while (high > p && (*cmp)(es[high], e) >= 0)
        {
            if (high + 1 < n)
                _partition_bubble(es, n, high + 1, high, rinorder, cmp);
            high--;
        }
        if (high != p)
        {
            es[p].content = es[high].content;
            p = high;
        }
        isfirst = true;
        while (low < p && (*cmp)(es[low], e) <= 0)
        {
            if (low - 1 >= 0)
                _partition_bubble(es, n, low, low - 1, linorder, cmp);
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
void QuickSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    if (n == 0 || n == 1)
        return;
    else if (n == 2)
    {
        if ((*cmp)(es[0], es[1]) > 0)
            _exchangeelem(es, 0, 1);
        return;
    }
    int p = _seletpivot(es, n, cmp);
    bool linorder = false, rinorder = false;
    p = _partition(es, n, p, &linorder, &rinorder, cmp);
    // printf("a:");
    // _printes2(es,n);
    int laster = n - p - 1;
    if (p < laster)
    {
        if (!linorder)
            QuickSort(es, p, cmp);
        if (!rinorder)
            QuickSort(es + p + 1, n - p - 1, cmp);
    }
    else
    {
        if (!rinorder)
            QuickSort(es + p + 1, n - p - 1, cmp);
        if (!linorder)
            QuickSort(es, p, cmp);
    }
}

int _findmax(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    int r = 0;
    for (int i = 0; i < n; i++)
    {
        if ((*cmp)(es[r], es[i]) < 0)
            r = i;
    }
    return r;
}
void SelectSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    for (int i = n; i > 1; i--)
    {
        int r = _findmax(es, i, cmp);
        _exchangeelem(es, r, i - 1);
    }
}

int _parent(int k)
{
    return (k - 1) / 2;
}
int _lchild(int k)
{
    return 2 * k + 1;
}
int _rchild(int k)
{
    return _lchild(k) + 1;
}
int _reversecmp(ElementType e1, ElementType e2, int (*cmp)(ElementType, ElementType), bool reverse)
{
    return reverse ? -1 * ((*cmp)(e1, e2)) : ((*cmp)(e1, e2));
}
void _heapadjust(ElementType es[], int n, int root, int (*cmp)(ElementType, ElementType), bool reverse) //default small to big
{
    if (n <= 1)
        return;
    ElementType e;
    e.t = es[0].t;
    e.content = es[root].content;
    for (int i = _lchild(root); i < n; root = i, i = _lchild(i))
    {
        if (i + 1 < n && _reversecmp(es[i], es[i + 1], cmp, reverse) > 0)
            i = i + 1;
        if (_reversecmp(es[i], e, cmp, reverse) < 0)
            es[root].content = es[i].content;
        else
            break;
    }
    es[root].content = e.content;
}
void HeapSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    for (int i = _parent(n - 1); i >= 0; i--)
    {
        _heapadjust(es, n, i, cmp, true);
    }
    int i;
    for (i = n - 1; i >= 1; i--)
    {
        _exchangeelem(es, 0, i);
        _heapadjust(es, i, 0, cmp, true);
    }
    _heapadjust(es, i, 0, cmp, true);
}
void _fullrest(ElementType es[], ElementType tmp[], int n)
{
    for (int i = 0; i < n; i++)
    {
        tmp[i].content = es[i].content;
    }
}
void _exchange_es(ElementType **es1, ElementType **es2)
{
    ElementType *tmp = *es1;
    *es1 = *es2;
    *es2 = tmp;
}
void _merge(ElementType es[], ElementType tmp[], int n1, int n2, int (*cmp)(ElementType, ElementType))
{
    if (n1 < 0 || n2 < 0)
        EXIT(ERROR, "error when _merge in sort.c");
    int n = n1 + n2;
    if (n1 == 0 || n2 == 0 || (*cmp)(es[n1 - 1], es[n1]) <= 0)
    {
        _fullrest(es, tmp, n);
        return;
    }
    else if ((*cmp)(es[0], es[n - 1]) >= 0)
    {
        _fullrest(es + n1, tmp, n2);
        _fullrest(es, tmp + n2, n1);
        return;
    }

    int i = 0, j = n1, k = 0;
    for (i = 0, j = n1; i < n1 && j < n; k++)
    {
        if ((*cmp)(es[i], es[j]) > 0)
        {
            tmp[k] = es[j];
            j++;
        }
        else
        {
            tmp[k] = es[i];
            i++;
        }
    }
    if (i < n1)
        _fullrest(es + i, tmp + k, n1 - i);
    else if (j < n)
        _fullrest(es + j, tmp + k + n1 - i, n - j);
}
void MergeSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    ElementType *es2 = (ElementType *)MALLOC(sizeof(ElementType), n, "merge sort no space");
    for (int i = 0; i < n; i++)
        es2[i].t = es[0].t;
    ElementType *data = es, *tmp = es2;
    for (int d = 1; d < n; d *= 2)
    {
        int i = 0;
        for (i = 0; i < n && i + (2 * d) - 1 < n; i += 2 * d)
        {
            _merge(data + i, tmp + i, d, d, cmp);
        }
        int r = n % (2 * d);
        if (r > d)
        {
            _merge(data + n - r, tmp + n - r, d, r - d, cmp);
        }
        else if (r > 0)
        {
            _merge(data + n - r, tmp + n - r, r, 0, cmp);
        }

        _exchange_es(&data, &tmp);
    }
    //completely sorted array is data;
    if (data != es)
    {
        _fullrest(data, es, n);
    }
    free(es2);
}

typedef enum
{
    _decrease = -1,
    _increase = 1,
    _balance = 0
} _trend;
_trend _gettrend(ElementType e1, ElementType e2, int (*cmp)(ElementType, ElementType))
{
    int k = (*cmp)(e1, e2);
    if (k == 0)
        return _balance;
    else if (k < 0)
        return _increase;
    else
        return _decrease;
}
// typedef struct
// {
//     ElementType *es;
//     int n;
//     int first;
//     int last;
//     int used;
// } myqueue;
// void _initiatemyqueue(myqueue *queue, int n, type t)
// {
//     queue->es = (ElementType *)MALLOC(sizeof(ElementType), n, "_initiatemyqueue");
//     for (int i = 0; i < n; i++)
//     {
//         InitiateElement(queue->es + i, t);
//     }
//     queue->last = queue->first = n - 1;
//     queue->used = 0;
// }
// void _enqueueintmy(myqueue *queue, int i)
// {
//     if (queue->used == queue->n - 1)
//         EXIT(ERROR, "_enqueueint");
//     SetValue(queue->es[queue->last], i);
//     if (queue->last != 0)
//         queue->last--;
//     else
//     {
//         queue->last = queue->n - 1;
//     }

//     // DestroyElement(&e);
// }
void _enqueueint(Queue *queue, int i)
{
    static ElementType e;
    static bool first = true;
    if (first)
    {
        InitiateElement(&e, Tint);
        first = false;
    }
    SetValue(e, &i);
    EnQueue(queue, e);
    // DestroyElement(&e);
}

int _dequeueint(Queue *queue)
{
    if (IsEmptyQ(*queue))
        EXIT(ERROR, "_dequeueint in sort.c");
    static ElementType e;
    static bool first = true;
    if (first)
    {
        InitiateElement(&e, Tint);
        first = false;
    }
    DeQueue(queue, &e);
    int i;
    GetValue(e, &i);
    return i;
}

int _gotokey(ElementType es[], int n, int k, _trend trend, int (*cmp)(ElementType, ElementType))
{
    if (trend == _balance)
        EXIT(ERROR, "_gotokey");
    if (k + 1 >= n)
        return -1;
    for (; k + 1 < n && _gettrend(es[k], es[k + 1], cmp) != -trend; k++)
        ;
    if (k == n - 1)
        return -1;
    else
        return k;
}
void _reverse(ElementType es[], int n)
{
    if (n < 0)
        EXIT(ERROR, "_reverse error");
    for (int i = 0; i < n / 2; i++)
    {
        _exchangeelem(es, i, n - 1 - i);
    }
}
int _first_trend(ElementType es[], int n, int k, _trend *trend, int (*cmp)(ElementType, ElementType))
{
    if (k + 1 > n)
        return -1;
    //find first trend
    int i = k;
    *trend = _balance;
    for (i = k; i + 1 < n && *trend == _balance; i++)
    {
        *trend = _gettrend(es[i], es[i + 1], cmp);
    }
    if (i == n - 1)
        return -1;
    else
        return i - 1;
}
int _findkey(ElementType es[], int n, int k, int (*cmp)(ElementType, ElementType))
{
    //find first trend
    _trend t = _balance;
    int i = _first_trend(es, n, k, &t, cmp);
    if (i != -1)
    {
        i = _gotokey(es, n, i, t, cmp);
    }
    //-1 or another
    if (t == _decrease)
    {
        _reverse(es + k, (i == -1 ? n - 1 : i) - k + 1);
        t = _increase;
        if (i != -1)
            i = _gotokey(es, n, i, t, cmp);
    }
    return i;

    //
}

bool _full_key_queue(ElementType es[], int n, Queue *queue, int (*cmp)(ElementType, ElementType))
{
    int i = _findkey(es, n, 0, cmp);
    if (i == -1)
        return false;
    else
    {

        InitiateQueue(queue, Tint);
        _enqueueint(queue, i);
        while (i < n)
        {
            i = _findkey(es, n, i + 1, cmp);
            if (i == -1)
                break;
            else
                _enqueueint(queue, i);
        }
        _enqueueint(queue, -1);
        return true;
    }
}
void KeySort(ElementType es[], int n, int (*cmp)(ElementType, ElementType))
{
    //find all key node
    Queue queue;
    if (!_full_key_queue(es, n, &queue, cmp))
        return;
    else
    {
        ElementType *es2 = MALLOC(sizeof(ElementType), n, "no space when keysort");
        for (int j = 0; j < n; j++)
            es2[j].t = Tint;
        ElementType *data = es;
        ElementType *tmpes = es2;

        int start = 0, key = 0, key2 = 0;
        while (!IsEmptyQ(queue))
        {
            //first stage
            key = _dequeueint(&queue);
            if (key == -1)
            {
                if (start == 0)
                    break;
                _merge(data + start, tmpes + start, n - start, 0, cmp);
                _exchange_es(&data, &tmpes);
                _enqueueint(&queue, -1);
                start = 0;
            }
            else
            {
                key2 = _dequeueint(&queue);
                if (key2 == -1)
                {
                    _merge(data + start, tmpes + start, key + 1 - start, n - key - 1, cmp);
                    _exchange_es(&data, &tmpes);
                    _enqueueint(&queue, -1);
                    start = 0;
                }
                else
                {
                    _merge(data + start, tmpes + start, key + 1 - start, key2 - key, cmp);
                    _enqueueint(&queue, key2);
                    start = key2 + 1;
                }
            }
        }
        // DestroyQueue(&queue);
        //correct sorted array in data
        PrintQueue(queue, "");
        if (data != es)
        {
            _merge(data, es, n, 0, cmp);
        }
        free(es2);
    }
}