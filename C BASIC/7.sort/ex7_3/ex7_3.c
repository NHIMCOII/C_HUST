#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.ic"
#include<time.h>

#define N 100
#define to_str(p) (*((const char*)p))
int cmp_inc_s(const void *a, const void *b){
    to_str(a); 
    to_str(b);
    // printf("%s %s\n",b,a);
    return strcmp(a,b);
}

typedef struct info{
    int occur;
    char *word;
}WORDS;

int main(){
    clock_t start,end;
    double time;
    start=clock();
    char buff[N];
    int count=0,idx=0;
    // FILE *fptr=fopen("lisa_all_text.txt","r");
    FILE *fptr=fopen("file.txt","r");
    while(feof(fptr)==0){
        fscanf(fptr," %s",buff);
        // sll_push_back_g(l,(gtype){.s=strdup(buff)});
        count++;
    }
    rewind(fptr);
    char **arr=malloc(count*sizeof(char*));
    
    while(feof(fptr)==0){
        arr[idx]=malloc(sizeof(char));
        fscanf(fptr,"%s",&arr[idx]);
        idx++;
    }
    fclose(fptr); 
    
    qsort(arr,count,sizeof(arr[0]),cmp_inc_s);
    end=clock();
    time=(double) (end-start)/CLOCKS_PER_SEC;
    printf("%d",count);
    printf("%lf\n",time);

    /*WORDS **w;
    for(int i=0;i<count;i++){
        w[i]=malloc(sizeof(struct info));
        w[i]->occur=0;
    }
    arr[count]="-081102";
    int j=0;
    for(int i=0;i<count;i++){
        w[j]->word=arr[i];
        w[j]->occur++;
        while(w[j]->word==arr[i+1]){
            w[j]->occur++;
            i++;
        }
        j++;
    }*/

    // for(int i=0;i<5;i++){
    //     printf("[%s] - (%d)\n",&w[i].word,w[i].occur);
    // }

    printf("ye\n");
    free(arr);
    return 0;
}