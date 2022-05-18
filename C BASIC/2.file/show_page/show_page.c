#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fi = fopen(argv[1], "r");
    char c[100];
    int count = 0;
    while(fgets(c,100,fi)){
        count++;
        if(argc == 3){
            if(strcmp(argv[2],"-p")==0){
                if(count == 10){
                    if(getchar()==13){
                        fputs(c,stdout);
                    }
                    count = 0;
                    continue;
                }
            }
        }
        else if(argc == 2){
            fputs(c,stdout);
        }
        if(argc==3){
            fputs(c,stdout);
        }
    }

    if(fgets(c,100,fi)==NULL){
        printf("\nThe end\n");
    }
    fclose(fi);

    return 0;
}