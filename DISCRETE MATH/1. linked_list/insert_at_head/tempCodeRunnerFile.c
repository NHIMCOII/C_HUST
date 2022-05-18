void print_list(node_t *head)
{
    node_t *traver = head;
    while (traver != NULL)
    {
        printf("%d->", traver->value);
        traver = traver->next;
    }
    printf("\n");
}