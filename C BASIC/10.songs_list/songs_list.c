#include "ext/io.h"
#include "cgen.ic"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// GLOBAL VAR
dll_t list;
char **name,
    **artist,
    **composer;
int *year;
//
// COMPARE FUNCTION
#define to_string(s) (*(const char **)s)

int cmp_s(const void *a, const void *b)
{
    return strcmp(to_string(a), to_string(b));
}

#define to_int(p) (*((const int *)p))

int cmp_i(const void *a, const void *b)
{
    return to_int(a) - to_int(b);
}
//
typedef struct _info_
{
    char *song;
    char *artist;
    char *composer;
    int year;
} info;
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

void sort_by_name(dll_t list)
{
    int size = (int)dll_length(list);
    name = malloc(size * sizeof(char *));
    dll_node_t cur = list->front;
    for (int i = 0; i < size; i++)
    {
        name[i] = malloc(sizeof(char));
        name[i] = dll_node_song_song(cur);
        cur = cur->next;
    }
    qsort(name, size, sizeof(name[0]), cmp_s);
}

void print_list_name(dll_t list)
{
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < dll_length(list); i++)
    {
        dll_traverse(cur, list)
        {
            if (strcmp(name[i], dll_node_song_song(cur)) == 0)
            {
                printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
            }
        }
    }
}

void sort_by_artist(dll_t list)
{
    int size = (int)dll_length(list);
    artist = malloc(size * sizeof(char *));
    dll_node_t cur = list->front;
    for (int i = 0; i < size; i++)
    {
        artist[i] = malloc(sizeof(char));
        artist[i] = dll_node_song_artist(cur);
        cur = cur->next;
    }
    qsort(artist, size, sizeof(artist[0]), cmp_s);
}

void print_list_artist(dll_t list)
{
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < dll_length(list); i++)
    {
        dll_traverse(cur, list)
        {
            if (strcmp(artist[i], dll_node_song_artist(cur)) == 0)
            {
                printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
            }
        }
    }
}

void sort_by_composer(dll_t list)
{
    int size = (int)dll_length(list);
    composer = malloc(size * sizeof(char *));
    dll_node_t cur = list->front;
    for (int i = 0; i < size; i++)
    {
        composer[i] = malloc(sizeof(char));
        composer[i] = dll_node_song_composer(cur);
        cur = cur->next;
    }
    qsort(composer, size, sizeof(composer[0]), cmp_s);
}

void print_list_composer(dll_t list)
{
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < dll_length(list); i++)
    {
        dll_traverse(cur, list)
        {
            if (strcmp(composer[i], dll_node_song_composer(cur)) == 0)
            {
                printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
            }
        }
    }
}

void sort_by_year(dll_t list)
{
    int size = (int)dll_length(list);
    year = malloc(size * sizeof(int));
    dll_node_t cur = list->front;
    for (int i = 0; i < size; i++)
    {
        year[i] = dll_node_song_year(cur);
        cur = cur->next;
    }
    qsort(year, size, sizeof(year[0]), cmp_i);
}

void print_list_year(dll_t list)
{
    printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < dll_length(list); i++)
    {
        dll_traverse(cur, list)
        {
            if (year[i] == dll_node_song_year(cur))
            {
                printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
            }
        }
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
    sort_by_name(list);
    sort_by_artist(list);
    sort_by_composer(list);
    sort_by_year(list);
}

void delete_line_file(char *argv, char *str)
{
    char buff[100];
    char *x;
    int c = 0;
    FILE *f1 = fopen(argv, "r");
    FILE *f2 = fopen("tmp.txt", "w");
    while (feof(f1) == 0)
    {
        fscanf(f1, " %[^\n]%*c", buff);
        x = strstr(buff, str);
        if (!x)
        {
            if (c != 0)
                fprintf(f2, "\n");
            fputs(buff, f2);
        }
        c++;
    }
                printf("ye\n");

    remove(argv);
    rename("tmp.txt", argv);
    fclose(f1);
    fclose(f2);
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
        dll_traverse(cur, list)
        {
            if (strcmp(str, dll_node_song_song(cur)) == 0)
            {
                dll_erase(list, cur);
                printf("ye\n");
                delete_line_file(argv, str);
            }
        }
        sort_by_name(list);
    }
    break;
    case 2:
    {
        char str[100];
        printf("Nhap ten ca si: ");
        scanf(" %[^\n]%*c", str);
        dll_traverse(cur, list)
        {
            if (strcmp(str, dll_node_song_artist(cur)) == 0)
            {
                dll_erase(list, cur);
                delete_line_file(argv, str);
            }
        }
        sort_by_artist(list);
    }
    break;
    case 3:
    {
        char str[100];
        printf("Nhap ten nhac si: ");
        scanf(" %[^\n]%*c", str);
        dll_traverse(cur, list)
        {
            if (strcmp(str, dll_node_song_composer(cur)) == 0)
            {
                dll_erase(list, cur);
                delete_line_file(argv, str);
            }
        }
        sort_by_composer(list);
    }
    break;
    case 4:
    {
        int x;
        char str[100];
        printf("Nhap nam sang tac: ");
        scanf("%d", &x);
        sprintf(str, "%d", x);
        dll_traverse(cur, list)
        {
            if (x == dll_node_song_year(cur))
            {
                dll_erase(list, cur);
                delete_line_file(argv, str);
            }
        }
        sort_by_year(list);
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
            info I;
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
    int length = (int)dll_length(list);
    sort_by_name(list);
    sort_by_artist(list);
    sort_by_composer(list);
    sort_by_year(list);
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
                print_list_name(list);
            }
            break;
            case 2:
            {
                print_list_artist(list);
            }
            break;
            case 3:
            {
                print_list_composer(list);
            }
            break;
            case 4:
            {
                print_list_year(list);
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
                printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
                printf("-------------------------------------------------------------------\n");
                dll_traverse(cur,list){
                    result=strstr(dll_node_song_song(cur),str);
                    if(result){
                        printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
                    }
                }
            }
            break;

            case 2:
            {
                char str[100], *result;
                printf("Nhap ten ca si: ");
                scanf(" %[^\n]%*c", str);
                printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
                printf("-------------------------------------------------------------------\n");
                dll_traverse(cur,list){
                    result=strstr(dll_node_song_artist(cur),str);
                    if(result){
                        printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
                    }
                }
            }
            break;

            case 3:
            {
                char str[100], *result;
                printf("Nhap ten nhac si: ");
                scanf(" %[^\n]%*c", str);
                printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
                printf("-------------------------------------------------------------------\n");
                dll_traverse(cur,list){
                    result=strstr(dll_node_song_composer(cur),str);
                    if(result){
                        printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
                    }
                }
            }
            break;

            case 4:
            {
                int x;
                printf("Nhap nam sang tac: ");
                scanf("%d", &x);
                printf("\n%-20s  %-15s  %-15s %-20s\n", "Ten bai hat", "Ca si", "Nhac si", "Nam sang tac");
                printf("-------------------------------------------------------------------\n");
                dll_traverse(cur, list)
                {
                    if (x <= dll_node_song_year(cur))
                        printf("%-20s  %-15s  %-15s %-4d\n", dll_node_song_song(cur), dll_node_song_artist(cur), dll_node_song_composer(cur), dll_node_song_year(cur));
                }
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
    dll_free_list(list);
    free(name);
    free(artist);
    free(composer);
    free(year);
    return 0;
}
