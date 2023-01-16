

void add_to_sort_list(List *head, Sort_list **sHead, Sort_list **sTail)
{
    Sort_list *new = calloc(1, sizeof(Sort_list));
    new->data = head;
    new->debt = head->debt;
    new->next = *sHead;
    *sHead = new;
}

void bubble_sort_by_debt (Sort_list **sHead) // =========== !
{
    Sort_list *a = *sHead, *b = NULL, *temp = NULL;

    if (*sHead == NULL || (*sHead)->next == NULL)
        return;

    while (a)
    {
        b = a->next;
        while (b)
        {
            if (b->debt > a->debt)
            {
                temp = a;
                a = b;
                b = temp;
            }
            b = b->next;
        }
        a = a->next;
    }    
}

int does_id_exist (List *node, Sort_list *sHead)
{
    int id = node->id;
    while(sHead)
    {
        if (id == sHead->data->id)
        {
            int last_date = cmp_date(node->date, sHead->data->date);
            sHead->debt += node->debt; // Sum debt
            if (last_date > 0)
                sHead->data = node; // Update date and phone num, point to the last struct
            return 1;
        }
        sHead = sHead->next;
    }
    return 0;
}

void build_sort_list (List *head, Sort_list **sHead, Sort_list **sTail)
{
    if (!head)
        return;

    while (head)
    {
        if (does_id_exist(head, *sHead) == 0)
        {
            add_to_sort_list(head, sHead, sTail);
        }
        head = head->next;
    }
    // bubble_sort_by_debt(sHead);
}

void print_sort_list(Sort_list *sHead)
{
    if (!sHead)
        return;
    print_sort_list (sHead->next);
    List *p = sHead->data;
    printf("%s %s, %s, ID: %d \n", p->first_name, p->last_name, p->phone, p->id);
    printf("\t-> debt: %d, date: %d/%d/%d \n",sHead->debt, p->date[0], p->date[1], p->date[2]);
}


List *check_double_id(List *row, List *head) 
{
    int id = row->id;
    while (head)
    {
        if (id == head->id)
        {
            if (strcmp(row->first_name, head->first_name) || strcmp(row->last_name, head->last_name))
            {
                free(row);
                return NULL;
            }
        }
        head = head->next;
    }
    return row;
}
