#include<stdio.h>

void split(float a,int *b,float* c)
{
    *b= (int)a;
    *c= a-*b;
    return ;
}
int main(){
    float num;
    int b;
    float c;
    printf("Enter: ");
    scanf("%f",&num);
    split(num,&b,&c);
    printf("%d\n%f\n",b,c);
    return 0;
}