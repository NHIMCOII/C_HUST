#include "ext/io.h"
#include "cgen.ic"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _info_
{
    char *id;
    char *name;
    float value;
    int num;
} * info;

dll_t list;
dll_t cart;

typedef struct dll_node_product_s
{
    struct dll_node_s base;
    char *id;
    char *name;
    float value;
    int num;
} * dll_node_product_t;

dll_node_t dll_create_node_product(char *id, char *name, float value, int num)
{
    dll_node_product_t nn = malloc(sizeof(struct dll_node_product_s));
    nn->id = strdup(id);
    nn->name = strdup(name);
    nn->value = value;
    nn->num = num;
    nn->base.next = NULL;
    return (dll_node_t)nn;
}

#define to_dll_node_product(n) ((dll_node_product_t)n)
#define dll_node_product_id(n) (to_dll_node_product(n)->id)
#define dll_node_product_name(n) (to_dll_node_product(n)->name)
#define dll_node_product_value(n) (to_dll_node_product(n)->value)
#define dll_node_product_num(n) (to_dll_node_product(n)->num)

void func_1()
{
    char str[100];
    int i = 0;
    printf("Nhap ma so san pham: ");
    scanf(" %[^\n]%*c", str);
    printf("---------------------------------------------------------------------\n");
    printf("\n%-20s %-20s %-20s %-5s\n", "Ma san pham", "Ten san pham", "Don gia", "SL");
    dll_traverse(cur, list)
    {
        if (strstr(dll_node_product_id(cur), str))
        {
            printf("%-20s %-20s %-20.2f %-5d\n", dll_node_product_id(cur), dll_node_product_name(cur), dll_node_product_value(cur), dll_node_product_num(cur));
            i++;
        }
    }
    if (i == 0)
        printf("\n=> Khong tim thay mat hang!\n");
}

int check(char *str)
{
    int i = 0;
    dll_traverse(cur, list)
    {
        if (strstr(dll_node_product_id(cur), str))
        {
            i = 1;
        }
    }
    return i;
}

void func_2()
{
    float price=0;
    char str[100];
    cart = dll_create_list();
    do
    {
        printf("Nhap ma mat hang: ");
        scanf(" %[^\n]%*c", str);
        if (check(str) == 1)
        {
            int count;
            printf("So luong: ");
            scanf("%d", &count);
            dll_traverse(cur, list)
            {
                if (strstr(dll_node_product_id(cur), str))
                {
                    if (count <= dll_node_product_num(cur))
                    {
                        dll_push_back(cart, dll_create_node_product(dll_node_product_id(cur), dll_node_product_name(cur), dll_node_product_value(cur), count));
                        price+=dll_node_product_value(cur)*count;
                        printf("Da them thanh cong vao gio hang!\n");
                    }
                    else
                    {
                        printf("Khong con du so luong san pham!\n");
                    }
                }
            }
        }
        else
        {
            printf("Loi khong co mat hang!\n");
        }
    }while(strcmp(str,"STOP")!=0);

    printf("\n---------------------------------------------------------------------\n");
    printf("Don hang ban le:\n");
    printf("\n%-20s %-20s %-20s %-5s\n", "Ma san pham", "Ten san pham", "Don gia", "SL");
    dll_traverse(cur, cart)
    {        
        printf("%-20s %-20s %-20.2f %-5d\n", dll_node_product_id(cur), dll_node_product_name(cur), dll_node_product_value(cur), dll_node_product_num(cur));   
    }
    printf("Tong tien: %.2f",price);
}

int main(int argc, char *argv[])
{
    int n;
    struct _info_ I;
    FILE *inp = fopen(argv[1], "r");
    if (argc != 2)
    {
        printf("Usage: ./prog inp.txt \n");
        return 0;
    }
    fscanf(inp, "%d", &n);
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
            token = strtok(l, " ");
            while (token != NULL)
            {
                if (flag == 0)
                    I.id = token;
                if (flag == 1)
                    I.name = token;
                if (flag == 2)
                    I.value = atof(token);
                if (flag == 3)
                    I.num = atoi(token);
                flag++;
                token = strtok(NULL, " ");
            }
            dll_push_back(list, dll_create_node_product(I.id, I.name, I.value, I.num));
            l = strtok(NULL, "\n");
        }
    }
    fclose(inp);

    for (;;)
    {
        printf("\n\n=====MENU=====\n"
               "1. Xem thong tin mat hang\n"
               "2. Tao don hang\n"
               "3. Thoat\n"
               "Lua chon cua ban [1-3]: ");
        int c = 0;
        scanf("%d", &c);
        clear_stdin();
        if (c == 1)
        {
            func_1();
        }
        else if (c == 2)
        {
            func_2();
        }
        else if (c == 3)
        {
            break;
        }
        else
        {
            printf("Lựa chọn không hợp lệ.\n");
        }
    }
    free(line);
    // dll_traverse(cur,cart){
    //     free(dll_node_product_id(cur));
    //     free(dll_node_product_name(cur));
    // }
    dll_traverse(cur,list){
        free(dll_node_product_id(cur));
        free(dll_node_product_name(cur));
    }
    // dll_free_list(cart);
    dll_free_list(list);
    printf("ye\n");
    return 0;
}