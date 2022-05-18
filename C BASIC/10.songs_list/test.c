#include "ext/io.h"
#include "cgen.ic"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// GLOBAL VAR
typedef struct _info_
{
    char *song;
    char *artist;
    char *composer;
    int year;
} *info;

dll_t list;
info a;
//
// RESTRUCTURE
typedef struct dll_node_song_s
{
    struct dll_node_s base;
    char *song;
    char *artist;
    char *composer;
    int year;
} * dll_node_song_t;

dll_node_t dll_create_node_song(char *song, char *artist, char *composer, int year)
{
    dll_node_song_t nn = malloc(sizeof(struct dll_node_song_s));
    nn->song = strdup(song);
    nn->artist = strdup(artist);
    nn->composer = strdup(composer);
    nn->year = year;
    nn->base.next = NULL;
    return (dll_node_t)nn;
}

#define to_dll_node_song(n) ((dll_node_song_t)n)
#define dll_node_song_song(n) (to_dll_node_song(n)->song)
#define dll_node_song_artist(n) (to_dll_node_song(n)->artist)
#define dll_node_song_composer(n) (to_dll_node_song(n)->composer)
#define dll_node_song_year(n) (to_dll_node_song(n)->year)
//
// COMPARE FUNCTION
int cmp_song(const void *a, const void *b){
    return strcmp(((info)a)->song, ((info)b)->song);
}

int cmp_artist(const void *a, const void *b){
    return strcmp(((info)a)->artist, ((info)b)->artist);
}

int cmp_composer(const void *a, const void *b){
    return strcmp(((info)a)->composer, ((info)b)->composer);
}

int cmp_year(const void *a, const void *b)
{
    return (((info) a)->year)- (((info) b)->year);
}
//
void update_a(){
    int index=0;
    a=realloc(a,sizeof(struct _info_)*dll_length(list));
    dll_traverse(cur,list){
        a[index].song=dll_node_song_song(cur);
        a[index].artist=dll_node_song_artist(cur);
        a[index].composer=dll_node_song_composer(cur);
        a[index].year=dll_node_song_year(cur);
        index++;
    }
}

void print_list(int length){
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");
    for(int i=0;i<length;i++){
        printf("%-20s  %-15s  %-15s %-4d\n",a[i].song,a[i].artist,a[i].composer,a[i].year);
    }
}

void print_list_name(int length){
    qsort(a,length,sizeof(struct _info_),cmp_song);
    print_list(length);
}

void print_list_artist(int length){
    qsort(a,length,sizeof(struct _info_),cmp_artist);
    print_list(length);
}

void print_list_composer(int length){
    qsort(a,length,sizeof(struct _info_),cmp_composer);
    print_list(length);
}

void print_list_year(int length){
    qsort(a,length,sizeof(struct _info_),cmp_year);
    print_list(length);
}

void screening_song(int length,char *str){
    qsort(a,length,sizeof(struct _info_),cmp_song);
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");   
    for(int i=0;i<length;i++){
        if(strstr(a[i].song,str))
            printf("%-20s  %-15s  %-15s %-4d\n",a[i].song,a[i].artist,a[i].composer,a[i].year);
    }
}

void screening_artist(int length,char *str){
    qsort(a,length,sizeof(struct _info_),cmp_artist);
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");   
    for(int i=0;i<length;i++){
        if(strstr(a[i].artist,str))
            printf("%-20s  %-15s  %-15s %-4d\n",a[i].song,a[i].artist,a[i].composer,a[i].year);
    }
}

void screening_composer(int length,char *str){
    qsort(a,length,sizeof(struct _info_),cmp_composer);
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");   
    for(int i=0;i<length;i++){
        if(strstr(a[i].composer,str))
            printf("%-20s  %-15s  %-15s %-4d\n",a[i].song,a[i].artist,a[i].composer,a[i].year);
    }
}

void screening_year(int length,int year){
    qsort(a,length,sizeof(struct _info_),cmp_year);
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");   
    for(int i=0;i<length;i++){
        if(year<=a[i].year)
            printf("%-20s  %-15s  %-15s %-4d\n",a[i].song,a[i].artist,a[i].composer,a[i].year);
    }
}

void add_song(dll_t list, char *argv)
{
    char new_song[100],
        new_artist[100],
        new_composer[100];
    int new_year;
    printf("\nTen bai hat: ");
    scanf(" %[^\n]%*c", new_song);
    printf("Ten ca si: ");
    scanf(" %[^\n]%*c", new_artist);
    printf("Ten nhac si: ");
    scanf(" %[^\n]%*c", new_composer);
    printf("Nam sang tac: ");
    scanf("%d", &new_year);
    dll_push_back(list, dll_create_node_song(new_song, new_artist, new_composer, new_year));
    FILE *fptr = fopen(argv, "a+");
    if (fptr == NULL)
    {
        perror("ERROR!!!\n");
        exit(1);
    }
    fprintf(fptr, "\n%s#*#%s#*#%s#*#%d", new_song, new_artist, new_composer, new_year);
    fclose(fptr);
    update_a();
}

void delete_line_file(char *argv, char *str)
{
    // char buff[100];
    // char *x;
    // int c = 0;
    // FILE *f1 = fopen(argv, "r");
    // FILE *f2 = fopen("tmp.txt", "w");
    // while (feof(f1) == 0)
    // {
    //     fscanf(f1, " %[^\n]%*c", buff);
    //     x = strstr(buff, str);
    //     if (!x)
    //     {
    //         if (c != 0)
    //             fprintf(f2, "\n");
    //         fputs(buff, f2);
    //     }
    //     c++;
    // }
    // fclose(f1);
    // fclose(f2);
    // remove(argv);
    // rename("tmp.txt", argv);
    int c=0;
    FILE *fi=fopen(argv,"w");
    for(int i=0;i<dll_length(list);i++){
        if(c!=0)
            fprintf(fi,"\n");
        fprintf(fi,"%s#*#%s#*#%s#*#%d",a[i].song,a[i].artist,a[i].composer,a[i].year);
        c++;
    }
    fclose(fi);
}

void delete_song(dll_t list, char *argv)
{
    int msub = 0;
    printf("\nXoa theo thuoc tinh:\n");
    printf("1. Ten bai hat\n");
    printf("2. Ca si\n");
    printf("3. Nhac si\n");
    printf("4. Nam sang tac\n");
    printf("\nLua chon cua ban: ");
    scanf("%d", &msub);
    switch (msub)
    {
    case 1:
    {
        char str[100];
        printf("Nhap ten bai hat: ");
        scanf(" %[^\n]%*c", str);
        dll_node_t *tmp=malloc(sizeof(struct dll_node_s));
        int idx=0;
        dll_traverse(cur, list)
        {
            if (strcmp(str, dll_node_song_song(cur)) == 0)
            {
                tmp[idx]=cur;
                if(idx!=0)
                tmp=realloc(tmp,(idx+1)*sizeof(struct dll_node_s));
                idx++;
            }
        }
        printf("Xac nhan thong tin xoa: \n");
        for(int i=0;i<idx;i++){
            printf("%-20s | %-15s | %-15s | %-4d\n",dll_node_song_song(tmp[i]),dll_node_song_artist(tmp[i]),dll_node_song_composer(tmp[i]),dll_node_song_year(tmp[i]));
        }
        int k;
        printf("Ban co muon xoa (1-0): ");
        scanf("%d",&k);
        
        if(k==1){
            for(int i=0;i<idx;i++){
                dll_erase(list,tmp[i]);
                free(dll_node_song_song(tmp[i]));
                free(dll_node_song_artist(tmp[i]));
                free(dll_node_song_composer(tmp[i]));
            }
            update_a();
            delete_line_file(argv, str);
        }
        free(tmp);
    }
    break;
    case 2:
    {
        char str[100];
        printf("Nhap ten ca si: ");
        scanf(" %[^\n]%*c", str);
        dll_node_t *tmp=malloc(sizeof(struct dll_node_s));
        int idx=0;
        dll_traverse(cur, list)
        {
            if (strcmp(str, dll_node_song_artist(cur)) == 0)
            {
                tmp[idx]=cur;
                if(idx!=0)
                tmp=realloc(tmp,(idx+1)*sizeof(struct dll_node_s));
                idx++;
            }
        }
        printf("Xac nhan thong tin xoa: \n");
        for(int i=0;i<idx;i++){
            printf("%-20s | %-15s | %-15s | %-4d\n",dll_node_song_song(tmp[i]),dll_node_song_artist(tmp[i]),dll_node_song_composer(tmp[i]),dll_node_song_year(tmp[i]));
        }
        int k;
        printf("Ban co muon xoa (1-0): ");
        scanf("%d",&k);
        
        if(k==1){
            for(int i=0;i<idx;i++){
                dll_erase(list,tmp[i]);
                free(dll_node_song_song(tmp[i]));
                free(dll_node_song_artist(tmp[i]));
                free(dll_node_song_composer(tmp[i]));
            }
            update_a();
            delete_line_file(argv, str);
        }
        free(tmp);
    }
    break;
    case 3:
    {
        char str[100];
        printf("Nhap ten nhac si: ");
        scanf(" %[^\n]%*c", str);
        dll_node_t *tmp=malloc(sizeof(struct dll_node_s));
        int idx=0;
        dll_traverse(cur, list)
        {
            if (strcmp(str, dll_node_song_composer(cur)) == 0)
            {
                tmp[idx]=cur;
                if(idx!=0)
                    tmp=realloc(tmp,(idx+1)*sizeof(struct dll_node_s));
                idx++;
            }
        }
        printf("Xac nhan thong tin xoa: \n");
        for(int i=0;i<idx;i++){
            printf("%-20s | %-15s | %-15s | %-4d\n",dll_node_song_song(tmp[i]),dll_node_song_artist(tmp[i]),dll_node_song_composer(tmp[i]),dll_node_song_year(tmp[i]));
        }
        int k;
        printf("Ban co muon xoa (1-0): ");
        scanf("%d",&k);
        
        if(k==1){
            for(int i=0;i<idx;i++){
                dll_erase(list,tmp[i]);
                free(dll_node_song_song(tmp[i]));
                free(dll_node_song_artist(tmp[i]));
                free(dll_node_song_composer(tmp[i]));
            }
            update_a();
            delete_line_file(argv, str);
        }
        free(tmp);
    }
    break;
    case 4:
    {
        char str[100];
        int x=0;
        printf("Nhap nam sang tac: ");
        scanf("%d", &x);
        sprintf(str,"%d",x);
        dll_node_t *tmp=malloc(sizeof(struct dll_node_s));
        int idx=0;
        dll_traverse(cur, list)
        {
            if (x==dll_node_song_year(cur))
            {
                tmp[idx]=cur;
                if(idx!=0)
                    tmp=realloc(tmp,(idx+1)*sizeof(struct dll_node_s));
                idx++;
            }
        }
        printf("Xac nhan thong tin xoa: \n");
        for(int i=0;i<idx;i++){
            printf("%-20s | %-15s | %-15s | %-4d\n",dll_node_song_song(tmp[i]),dll_node_song_artist(tmp[i]),dll_node_song_composer(tmp[i]),dll_node_song_year(tmp[i]));
        }
        int k;
        printf("Ban co muon xoa (1-0): ");
        scanf("%d",&k);
        
        if(k==1){
            for(int i=0;i<idx;i++){
                dll_erase(list,tmp[i]);
                free(dll_node_song_song(tmp[i]));
                free(dll_node_song_artist(tmp[i]));
                free(dll_node_song_composer(tmp[i]));
            }
            update_a();
            delete_line_file(argv, str);
        }
        free(tmp);
    }
    break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    FILE *inp = fopen(argv[1], "r");
    if (argc != 2)
    {
        printf("Usage: ./prog inp.txt \n");
        return 0;
    }
    list = dll_create_list();
    char *line = NULL;
    char *token, *l;
    while (cgetline(&line, 0, inp))
    {
        l = strtok(line, "\n");
        while (l != NULL)
        {
            struct _info_ I;
            int flag = 0;
            token = strtok(l, "#*#");
            while (token != NULL)
            {
                if (flag == 0)
                    I.song = token;
                if (flag == 1)
                    I.artist = token;
                if (flag == 2)
                    I.composer = token;
                if (flag == 3)
                    I.year = atoi(token);
                flag++;
                token = strtok(NULL, "#*#");
            }
            dll_push_back(list, dll_create_node_song(I.song, I.artist, I.composer, I.year));
            l = strtok(NULL, "\n");
        }
    }
    fclose(inp);

    a=calloc(dll_length(list),sizeof(struct _info_));
    update_a();
    // MENU
    int m = 0;
    do
    {
        printf("\n1. Xem danh sach bai hat\n");
        printf("2. Loc danh sach bai hat\n");
        printf("3. Them bai hat\n");
        printf("4. Xoa bai hat\n");
        printf("5. Thoat\n");
        printf("\nLua chon cua ban: ");
        scanf("%d", &m);
        switch (m)
        {
        case 1:
        {
            int msub = 0;
            printf("\nSap xep danh sach theo:\n");
            printf("1. Ten bai hat\n");
            printf("2. Ca si\n");
            printf("3. Nhac si\n");
            printf("4. Nam sang tac\n");
            printf("\nLua chon cua ban: ");
            scanf("%d", &msub);          
            switch (msub)
            {
            case 1:
            {
                print_list_name((int) dll_length(list));
            }
            break;
            case 2:
            {
                print_list_artist((int) dll_length(list));
            }
            break;
            case 3:
            {
                print_list_composer((int) dll_length(list));
            }
            break;
            case 4:
            {
                print_list_year((int) dll_length(list));
            }
            break;

            default:
                break;
            }
        }
        break;

        case 2:
        {
            int msub = 0;
            printf("\nLoc theo thuoc tinh:\n");
            printf("1. Ten bai hat\n");
            printf("2. Ca si\n");
            printf("3. Nhac si\n");
            printf("4. Nam sang tac\n");
            printf("\nLua chon cua ban: ");
            scanf("%d", &msub);
            switch (msub)
            {
            case 1:
            {
                char str[100], *result;
                printf("Nhap ten bai hat: ");
                scanf(" %[^\n]%*c", str);
                screening_song((int) dll_length(list),str);
            }
            break;

            case 2:
            {
                
                char str[100], *result;
                printf("Nhap ten ca si: ");
                scanf(" %[^\n]%*c", str);
                screening_artist((int) dll_length(list),str);
            }
            break;

            case 3:
            {
                char str[100], *result;
                printf("Nhap ten nhac si: ");
                scanf(" %[^\n]%*c", str);
                screening_composer((int) dll_length(list),str);
            }
            break;

            case 4:
            {
                int x;
                printf("Nhap nam sang tac: ");
                scanf("%d", &x);
                screening_year((int) dll_length(list),x);
            }
            break;

            default:
                break;
            }
        }
        break;

        case 3:
        {
            add_song(list, argv[1]);
        }
        break;

        case 4:
        {
            delete_song(list, argv[1]);
        }
        break;

        default:
            break;
        }
    } while (m != 5);
    //

    free(line);
    free(a);
    dll_traverse(cur,list){
        free(dll_node_song_song(cur));
        free(dll_node_song_artist(cur));
        free(dll_node_song_composer(cur));
    }
    dll_free_list(list);
    return 0;
}
