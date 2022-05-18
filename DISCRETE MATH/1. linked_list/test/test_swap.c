Node* sort(Node* head)
{
    Node* newhead = NULL;
    Node* tail = NULL;
    Node* cur = head;
    while (cur != NULL)
    {
        Node* MIN = cur;
        for (Node* p = cur; p != NULL; p = p->next)
        if (MIN->getValue() > p->getValue())
            MIN = p;

        Node* preMIN = NULL;
        Node* afterMIN = MIN->next;

        if (MIN == head)
        {
            head = afterMIN;
        }
        else
        {
            for (Node* p = cur; p != NULL; p = p->next)
            {
                preMIN = p;
                if (p->next == MIN)
                    break;
            }
            preMIN->next = afterMIN;
        }

        if (newhead == NULL)
        {
            newhead = MIN;
            newhead->next = NULL;
            tail = newhead;
            tail->next = NULL;
        }
        else
        {
            tail->next = MIN;
            MIN->next = NULL;
            tail = MIN;
        }

        cur = head;
    }
    return newhead;
}