//status
#ifndef _SORT_H
#define _SORT_H

#include<stdio.h>
#include"Status.h"
#include<ElementType.h>
void InsertSort(ElementType es[],int , int (*cmp)(ElementType, ElementType));
void ShellSort(ElementType es[],int , int (*cmp)(ElementType, ElementType));
void BubbleSort(ElementType es[],int n, int (*cmp)(ElementType, ElementType));
void QuickSort(ElementType es[],int n, int (*cmp)(ElementType, ElementType));
void SelectSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType));
void HeapSort(ElementType es[], int n, int (*cmp)(ElementType, ElementType));

#endif