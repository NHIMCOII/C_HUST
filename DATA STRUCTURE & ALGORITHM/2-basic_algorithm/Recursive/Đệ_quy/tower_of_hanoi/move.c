#include<stdio.h>
    int count=1;
    // 2^n - 1
    // C : Intermediate 
    // A : Start
    // B : Destination
void move(int n,char A,char B,char C){
    if(n==1){
        printf("%d. Move 1 disk from %c to %c\n",count,A,B);
        count++;
    }
    else{
        move(n-1,A,C,B);
        move(1,A,B,C);
        move(n-1,C,B,A);
    }
}

int main(){
    int n;
    printf("Enter n = ");
    scanf("%d",&n);
    move(n,'A','B','C');
    printf("\n");
    return 0;
}