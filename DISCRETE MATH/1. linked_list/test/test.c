Node *insertNode(Node *head, Node *newNode)
{
    if (head == NULL || head->getValue() >= newNode->getValue())
    {
        newNode->next = head;
        head = newNode;
        return head;
    }
    else
    {
        Node *cur = head;
        while (cur->next != NULL && cur->next->getValue() < newNode->getValue())
        {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
    }
    return head;
}

Node *sort(Node *head)
{
    Node *temp = NULL;
    Node *cur = head;
    while (cur != NULL)
    {
        Node *cur_next = cur->next;
        temp = insertNode(temp, cur);
        cur = cur_next;
        //cur=cur->next;
    }
    return temp;
}