#include <stdio.h>
#include <math.h>
#include <time.h>

void printIntArray(int *arr,const int len, int format) {
      for (int j=0;j<len;++j) {
         printf("[%*d]",format, arr[j]);
     }
}

void swapInt(int *a,int *b) {
    int t=*a;
    *a=*b;
    *b=t;
}

void fillIntRandom(int *arr, int len, int randN) {
     for (int j=0;j<len;++j)
      arr[j]=rand()%randN;
}

//Task 1

//Быстрая сортировка (Хоара)
void qs(int *arr, int first,int last) {
    int i=first;
    int j=last;

    int x=arr[(first+last)/2];

    do {
        while (arr[i]<x) i++;
        while (arr[j]>x) j--;

        if (i<=j) {
            swapInt(&arr[i],&arr[j]);
            i++;
            j--;
        }
    } while (i<=j);

    if (i<last) qs(arr,i,last);
    if (first<j) qs(arr,first,j);
}

//Сортировка вставками
void sortInserts(int *arr,int len) {
    int temp,pos;
    for (int i=1;i<len;++i) {
        temp=arr[i];
        pos=i-1;
        while (pos>=0 && arr[pos]>temp) {
            arr[pos+1]=arr[pos];
            pos--;
        }
        arr[pos+1]=temp;
    }
}

//Быстрая сортировка улучшенная
void qsImp(int *arr, int first,int last) {

   if ((last+1-first)>10) {
    int i=first;
    int j=last;
    int ave=(first+last)/2;

    int tm[3]={arr[first],arr[ave],arr[last-1]};
    sortInserts(tm, 3);
    int x=tm[1];
    if (x==arr[first]) swapInt(&arr[first],&arr[ave]);
    else if (x==arr[last-1]) swapInt(&arr[last-1],&arr[ave]);

    x=arr[ave];
    do {
        while (arr[i]<x) i++;
        while (arr[j]>x) j--;

        if (i<=j) {
            swapInt(&arr[i],&arr[j]);
            i++;
            j--;
        }
    } while (i<=j);



    if (i<last) qsImp(arr,i,last);
    if (first<j) qsImp(arr,first,j);
   }

   sortInserts(arr, (last+1-first));

}

//Task 2

//Блочная сортировка
void bucketSort(int* arr,int len) {
 const int max=len;
 const int b=10;

 int buckets[b][max+1];
 for (int i=0;i<b;++i) {
     buckets[i][max]=0;
 }

 for (int digit=1;digit<1000000000;digit*=10) {
   for (int i=0;i<max;++i) {
        int d=(arr[i]/digit)%b;
        buckets[d][buckets[d][max]++]=arr[i];
   }
   int idx=0;
   for (int i=0;i<b;++i) {
       for (int j=0; j<buckets[i][max];++j) {
           arr[idx++]=buckets[i][j];
       }
       buckets[i][max]=0;
   }
 }
}


//Блочная сортировка для четных чисел
void bucket2Sort(int* arr,int len) {
 const int max=len;
 const int b=10;

 int buckets[b][max+1];
 for (int i=0;i<b;++i) {
     buckets[i][max]=0;
 }

 for (int digit=1;digit<1000000000;digit*=10) {
   for (int i=0;i<max;++i) {
       int d=(arr[i]/digit)%b;
       {
        buckets[d][buckets[d][max]++]=arr[i];
       }
   }
   int idx=0;
   int i=0;
   while(i<b) { int j=0;
       while (j<buckets[i][max]) {
           if (arr[idx]%2==0) {
            if (buckets[i][j]%2==0)
             arr[idx++]=buckets[i][j];
            else break;
            }
           else {
            idx++;
            if (buckets[i][j]%2==0) continue;
            else
             break;
           }
          j++;
       }
       buckets[i++][max]=0;
   }
 }
}


int main()
{
    printf("Task 1\n");

    srand(time(NULL));
    const int SZ=30;
    int arr[SZ];
    fillIntRandom(arr,SZ,100);
    printIntArray(arr,SZ,2);
    qsImp(arr,0,SZ-1);
    printf("\n");
    printIntArray(arr,SZ,2);
    printf("\n");

    printf("Task 2\n");
    const int SZ1=12;
    int arr1[]= {0,2,8,3,4,6,5,9,8,2,7,3};

    printIntArray(arr1,SZ1,2);
    bucket2Sort(arr1,SZ1);
    printf("\n");
    printIntArray(arr1,SZ1,2);
    printf("\n\n");

    const int SZ2=20;
    int arr2[]= { 3, 1, 2, 3, 7, 3, 4, 1, 3, 5, 6, 8, 5, 5, 7, 6, 2, 4, 8, 0};

    printIntArray(arr2,SZ2,2);
    bucket2Sort(arr2,SZ2);
    printf("\n");
    printIntArray(arr2,SZ2,2);
    printf("\n");

    return 0;
}
