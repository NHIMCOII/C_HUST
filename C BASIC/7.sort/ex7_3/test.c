#include "../cgen/ext/io.h"
#include "../cgen/cgen.ic"
#include<string.h>
#include<time.h>

#define to_string(s) (*(const char**) s)

int cmp_s(const void *a, const void *b) {
    return strcmp(to_string(a), to_string(b));
}

#define to_int(p) (*((const int*) p))

int cmp_i(const void *a, const void *b) {
    return to_int(b) - to_int(a);
}

typedef struct sll_node_w_s{
    struct sll_node_s base;
    char *word;
    int count;
} *sll_node_w_t;

sll_node_t sll_create_node_w(char *w) {
    sll_node_w_t tmp = malloc(sizeof(struct sll_node_w_s));
    tmp->word = w;
    tmp->count = 1;
    return (sll_node_t) tmp;
}

#define to_sll_node_w(n) ((sll_node_w_t)n)
#define sll_node_w_word(n) (to_sll_node_w(n)->word)
#define sll_node_w_count(n) (to_sll_node_w(n)->count)

int main() {
    // -- INITIALIZE
    clock_t start_t, end_t;
    start_t = clock();
    FILE *f = fopen("C:\\Users\\PC\\c_library\\c-basic\\text\\lisa_all_text.txt", "r");
    char *tmp = malloc(50);
    // -- COUNT WORDS
    int wcount = 0;
    while(feof(f) == 0) {
        fscanf(f, "%s", tmp);
        wcount++;
    }
    free(tmp);
    fseek(f, 0, SEEK_SET);

    // -- STORE DATA INTO 2D ARRAY
    char **word = malloc(wcount * sizeof(char*));
    long i = 0; // index
    while(feof(f) == 0) {
        *(word + i) = malloc(50);
        fscanf(f, "%s", *(word + i));
        /*if((*(word + i))[strlen(*(word + i)) - 1] == ',' || (*(word + i))[strlen(*(word + i)) - 1] == '.' || (*(word + i))[strlen(*(word + i)) - 1] == ':'){
            (*(word + i))[strlen(*(word + i)) - 1] = '\0';
        }*/
        i++;
    }
    fclose(f);

    // -- SORT DATA
    qsort(word, i, sizeof(char*), cmp_s);

    // -- STORE DATA INTO SLL
    sll_t list = sll_create_list();
    sll_push_back(list, sll_create_node_w(*word));
    for (int j = 1; j < i; j++) {
        if (!strcmp(*(word + j), *(word + j - 1))) {
            sll_node_w_count(list->back)++;
            continue;
        }
        sll_push_back(list, sll_create_node_w(*(word + j)));
    }

    // -- PRINT NEEDED INFO
    long length = sll_length(list);
    printf("Total number of words: %d\n", wcount);
    printf("The number of unique words: %ld\n\n", length);
    int arr[length];
    int pos = 0;
    sll_traverse(cur, list) {
        arr[pos] = sll_node_w_count(cur);
        pos++;
    }
    qsort(arr, length, sizeof(int), cmp_i);
    printf("Top 10 most frequent words:\n");
    sll_traverse(cur, list) {
        if (sll_node_w_count(cur) >= arr[9])  printf("\"%s\" %s (%d)\n", sll_node_w_word(cur), "-", sll_node_w_count(cur));
    }
    printf("\n");

    // FREE MEMORY
    sll_free_list(list);
    for (int j = i - 1; j >= 0; j--) {
        free(*(word + j));
    }
    free(word);
    end_t = clock();
    double time = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    printf("Time taken: %lf\n", time);
    return 0;
}