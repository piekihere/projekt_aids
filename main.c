#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ns[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };
void swap(int *A, int i, int j)
{
    int tmp;
    tmp=A[i];
    A[i]=A[j];
    A[j]=tmp;
}

int argMin(int *A, int begin, int end)
{
    int argMin;
    argMin=begin;
    for(int i=begin+1;i<end;i++)
    {
        if(A[i]<A[argMin])
        {
            argMin=i;
        }
    }
    return argMin;

}
int partition(int *A, int p, int r)
{
    int x=A[r];
    int i=p-1;

    for(int j=p; j<r; j++)
        {
        if(A[j]<=x)
            {
            i=i+1;
            swap(A,i,j);
            }
        }
    i=i+1;
    swap(A,i,r);
    return i;
}
int random(int p, int r)
{
    return (rand() % (r + 1 - p)) + p;

}
int randomized_partition(int *A, int p,int r)
{
 int i=random(p,r);
 swap(A,i,r);
 return partition(A,p,r);
}
int left(int i)
{
    return 2i+1;
}
int right(int i)
{
    2i+2;
}

void fill_random(int *A,int n)  //wypelnia losowymi liczbami
{
    for(int i=0;i<n;i++)
    {
        A[i]=rand()%n;
    }
}

void fill_increasing(int *A, int n) // wypelnia rosnaca
{

    for(int i=0;i<n;i++)
    {
        A[i]=i;
    }
}

void fill_decreasing(int *A, int n) // wypelnia malejaco
{

    int i;
    for (i=n; i>=0; i--)
    {
        A[n-i]=i;
    }
}

void fill_vshape(int *A, int n) // wypelnia malejaca do polowy i od polowy rosnaca np  1000->500->1000
{

 for(int i=n; i>=n/2; i--)
    {
        A[n-i]=i;
    }

    for(int i=n/2+1; i<n; i++)
    {
        A[i]=i;
    }
}

void selection_sort(int *A, int n)
{
    int j;
    for(int i=0;i<n;i++)
    {
     j=argMin(A,i,n);
     swap(A,i,j);
    }

}

void insertion_sort(int *A, int n)
{
    int key;
    int i;
    for(int j=1;j<n;j++)
    {
     key=A[j];
     i=j-1;
     while(i>=0 && A[i]>key)
     {
         A[i+1]=A[i];
         i=i-1;
     }
     A[i+1]=key;
    }
}

void quick_sort(int *A, int p, int r)
{
   int q;
   if(p<r)
   {
       q=partition(A,p,r);
       quick_sort(A,p,q-1);
       quick_sort(A,q+1,r);
   }

}

void quick_sort_all(int *A, int n)
{
    quick_sort(A, 0, n - 1);
}

void randomized_quick_sort(int *A, int p, int r)
{
    int q;
    if(p<r)
    {
       q=randomized_partition(A,p,r);
       randomized_quick_sort(A,p,q-1);
       randomized_quick_sort(A,q+1,r);
    }



}

void randomized_quick_sort_all(int *A, int n)
{
    randomized_quick_sort(A, 0, n - 1);
}
/*void maxHeapify(int *A,int i,int size)
{
    int l=left(i);
    int r=right(i);
    int largest=i;
    if(l<size && A[l]>A[largest])
    {
        largest=l;
    }
    if(r<size && A[r]>A[largest])
    {
        largest=r;
    }
    if(largest!=i)
    {
        swap(A,i,largest);
        maxHeapify(A,largest,size);
    }

}*/
/*void buildMaxHeap(int *A,int n)
{
    for(int i=n/2; i>0;i--)
    {
        maxHeapify(A,i,n);
    }
}*/

void heap_sort(int *A, int n)
{
   /* buildMaxHeap(A,n);
    for(int i=n;i>1;i--)
    {
        swap(A,0,i);
        maxHeapify(A,0,i);
    }*/

}

bool is_random(int *A, int n)
{
    return true;
}

bool is_increasing(int *A, int n)
{
    for (int i = 1; i < n; i++) {
        if (A[i] <= A[i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_decreasing(int *A, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (A[i] >= A[i - 1])
        {
            return false;
        }
    }
    return true;
}

bool is_vshape(int *A, int n)
{
    if (n % 2 == 0)
    {
        return is_decreasing(A, n/2) && is_increasing(A + n/2, n/2);
    }
    return is_decreasing(A, n/2 + 1) && is_increasing(A + n/2, n/2 + 1);
}

bool is_sorted(int *A, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (A[i] < A[i - 1])
        {
            return false;
        }
    }
    return true;
}

char *bool_to_string(bool b)
{
    return b ? "Y" : "N";
}

void (*fill_functions[])(int *, int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
bool (*check_functions[])(int *, int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, int) = { selection_sort, insertion_sort, quick_sort_all, randomized_quick_sort_all, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "RandomizedQuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++)
    {
        void (*sort)(int *, int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++)
        {
            void (*fill)(int *, int) = fill_functions[j];
            bool (*check)(int *, int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++)
            {
                int n = ns[k];
                int *A = calloc(n, sizeof(*A));

                fill(A, n);
                bool is_filled_ok = check(A, n);

                clock_t begin = clock();
                sort(A, n);
                clock_t end = clock();
                double seconds = (double) (end - begin) / (double) CLOCKS_PER_SEC;

                bool is_sorted_ok = is_sorted(A, n);

                printf("%-20s %-11s %-10d %-4s %-4s %.6f\n", sort_names[i], fill_names[j], n,
                       bool_to_string(is_filled_ok), bool_to_string(is_sorted_ok), seconds);//zmienilem g na %.6f bo mialem czasami 0 w wyniku zamiast jakiegos czasu
                free(A);
            }
        }
    }
    return 0;
}

