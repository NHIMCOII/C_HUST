#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct std_id{
    char name[31];
    int SBD;
    char major[31];
    float grade;
}student;

int main(){
    FILE* f1,*f2;
    student std;
    f1=fopen("THISINH.Dat","wb");
    
    if (f1==NULL){
        perror("Error opening file ! \n");
        return 1;
    }
    int i=1;
    do{
        printf("Student No.%d: \n",i);
        printf("Name: ");
        fflush(stdin);
        fgets(std.name,sizeof(std.name),stdin);
        std.name[strlen(std.name)-1]='\0';//replace \n
        if(strcmp(std.name,"***")==0) break;
        printf("SBD: ");
        scanf("%d",&std.SBD);
        printf("Major: ");
        fflush(stdin);
        fgets(std.major,sizeof(std.major),stdin);
        std.major[strlen(std.major)-1]='\0';
        printf("Grade: ");
        scanf("%f",&std.grade);
        fwrite(&std,sizeof(student),1,f1);        
        i++;
    }while(1);
    fclose(f1);

    printf("\n\n ORIGINAL LIST:\n");
    f1=fopen("THISINH.Dat","rb");
    i=0;
    while(fread(&std,sizeof(student),1,f1)>0)
    printf("%-3d %-5d %-20s %-20s %-5.1f\n",++i,std.SBD,std.name,std.major,std.grade);
    printf("\n\n Students go for ICT above 21.0\n");
    i=0;
    rewind(f1);

    while(fread(&std,sizeof(student),1,f1)>0)
    if(strcmp(std.major,"IT")==0&&std.grade>21.0)
    printf("%-3d %-5d %-20s %-20s %-5.1f\n",++i,std.SBD,std.name,std.major,std.grade);
    
    printf("\n\n Create file CNTT.Dat\n");
    i=0;
    rewind(f1);
    f2=fopen("CNTT.Dat","wb");
    while (fread(&std,sizeof(student),1,f1)>0)
    if(strcmp(std.major,"IT")==0)
    fwrite(&std,sizeof(student),1,f2);
    fclose(f2);

    f2=fopen("CNTT.Dat","rb");
    while(fread(&std,sizeof(student),1,f2)>0)
    printf("%-3d %-5d %-20s %-20s %-5.1f\n",++i,std.SBD,std.name,std.major,std.grade);
    fclose(f2);
    
    int sbd;
    printf("\n\nFind student\n");
    printf("SBD: ");
    scanf("%d",&sbd);
    rewind(f1);
    while(fread(&std,sizeof(student),1,f1))
    if(std.SBD==sbd){
        printf("Found student %s",std.name);
        break;
    }

    if(feof(f1))
    printf("Cant find\n");
    fclose(f1);

    return 0;
}