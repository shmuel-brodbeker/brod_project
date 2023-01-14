#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _List {
    char first_name[15];
    char last_name[15];
    char phone[11];
    struct _List *next;
    int date[3]; // "01/01/2023"
    int id;
    int debt;
} List;

typedef struct _sort_list {
    struct _sort_list *next;
    List *data;
    int debt;
} Sort_list;

void add_to_sort_list(List *head, Sort_list **sHead, Sort_list **sTail)
{
    Sort_list *new = calloc(1, sizeof(Sort_list));
    new->data = head;
    new->debt = head->debt;
    new->next = *sHead;
    *sHead = new;
}

int cmp_date (int a[3], int b[3])
{
    if (a[2] > b[2])
        return 1;
    else if (a[2] < b[2])
        return -1;
    else // the same year
    {
        if (a[1] > b[1])
            return 1;
        else if (a[1] < b[1])
            return -1;
        else // the same month
        {
            if (a[0] > b[0])
                return 1;
            else if (a[0] < b[0])
                return -1;
            else // the same date
            {
                return 0;
            }
        }
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
    // sort_by_debt(sHead);
}

void print_sort_list(Sort_list *sHead)
{
    if (!sHead)
        return;
    print_sort_list (sHead->next);
    List *p = sHead->data;
    printf("%s, %s, %s, %d  ->  ", p->first_name, p->last_name, p->phone, p->id);
    printf("debt: %d, date: %d/%d/%d \n",sHead->debt, p->date[0], p->date[1], p->date[2]);
}
