#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int c=0;
// tối ưu hơn cách cũ vì giảm số lần swap sau 1 vòng for ngoài cùng
void selectionSort(int *a,int n){
    for(int k=0;k<n;k++){
        int min=k;
        for(int j=k+1;j<n;j++){
            if(a[min]>a[j])
                min=j;
        }
        int tmp=a[min];
        a[min]=a[k];
        a[k]=tmp;
    }
}
// chèn a[k] về vị trí trc đó
void insertionSort(int *a,int n){
    for(int k=1;k<n;k++){
        int last = a[k];
        int j=k;
        while(j>0&&a[j-1]>last){
            a[j]=a[j-1];
            j--;
        }
        a[j]=last;
    }
}
// đẩy max về cuối
void bubbleSort(int *a,int n){
    int swapped;
    do{
        swapped=0;
        for(int i=0;i<n-1;i++){
            if(a[i]>a[i+1]){
                int tmp=a[i];
                a[i]=a[i+1];
                a[i+1]=tmp;
                swapped=1;
            }
        }
    }while(swapped==1);
}
// MERGE SORT
void merge(int *a,int L,int M,int R){
    int TA[L+R+1];
    int i=L;
    int j=M+1;
    for(int k=L;k<=R;k++){
        if(i>M){
            TA[k]=a[j];
            j++;
        }
        else if(j>R){
            TA[k]=a[i];
            i++;
        }
        else{
            if(a[i]<a[j]){
                TA[k]=a[i];
                i++;
            }
            else{
                TA[k]=a[j];
                j++;
            }
        }
    }
    for(int k=L;k<=R;k++)
        a[k]=TA[k];
}

void mergeSort(int *a,int L,int R){
    if(L<R){
        int M=(L+R)/2;
        mergeSort(a,L,M);
        mergeSort(a,M+1,R);
        merge(a,L,M,R);
    }
}
// 
// QUICK SORT
void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

int partition(int *a,int L,int R,int indexPivot){
    int pivot=a[indexPivot];
    swap(&a[indexPivot],&a[R]);
    int storeIndex=L;
    for(int i =L;i<=R-1;i++){
        if(a[i]<pivot){
            swap(&a[storeIndex],&a[i]);
            storeIndex++;
        }
    }
    swap(&a[storeIndex],&a[R]);
    return storeIndex;
}

void quickSort(int *a,int L,int R){
    if(L<R){
        int index=R;//choose pivot
        index = partition(a,L,R,index);
        if(L<index)
            quickSort(a,L,index-1);
        if(index<R)
            quickSort(a,index+1,R);
    }
}
// 
// HEAP SORT
void heapify(int *a,int i,int n){
    int l = 2*i+1;
    int r=2*i+2;
    int max=i;
    if(l<=n&&a[l]>a[i])
        max = l;
    if(r<=n&&a[r]>a[max])
        max=r;
    if(max!=i){
        swap(&a[i],&a[max]);
        heapify(a,max,n);
    }
}

void buildHeap(int *a,int n){
    for(int i=n/2-1;i>=0;i--)
        heapify(a,i,n);
}

void heapSort(int *a, int n){
    buildHeap(a,n);
    // for(int i=0;i<9;i++){
    //     printf("%d  ",a[i]);
    // }
    for(int i=n-1;i>0;i--){
        swap(&a[0],&a[i]);
        heapify(a,0,i-1);
    }
}
// 

int main(){
    clock_t start,end;
    double cpu_time_used;
    int count;
    FILE *inp=fopen("inp.txt","r");
    if (inp == NULL)
    {
        perror("Error\n");
        exit(1);
    }
    fscanf(inp,"%d",&count);
    
    int *a=malloc(count*sizeof(int));
    int i=0;
    while(!feof(inp)){
        fscanf(inp,"%d",&a[i]);  
        i++;      
    }
    fclose(inp);
    start=clock();
    // selectionSort(a,count);
    insertionSort(a,count);
    // bubbleSort(a,count);
    // mergeSort(a,0,count-1);
    // quickSort(a,0,count-1);
    // heapSort(a,count); ERROR
    end=clock();
    cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
    printf("Sorted array:\n\n");
    for(int i=0;i<count;i++)
        printf("[%d] -> ",a[i]);
    printf("\nProcess time: %lf\n\n",cpu_time_used);
    free(a);
    return 0;
}