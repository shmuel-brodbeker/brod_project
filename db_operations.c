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

typedef struct _Select {
    int field;
    int to_test_num[3];
    char parameter;
    char to_test_str[20];
} Select;

enum FIELDS {
    FIRST_N,
    LAST_N,
    ID,
    PHONE,
    DEBT,
    DATE
};

void free_list (List *head)
{
    if (!head)
        return;
    free_list(head->next);
    free(head);
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

void print_node(List *head)
{
    if (!head)
        return;
    printf("%s %s, %s, ID: %09d  \n  ", head->first_name, head->last_name, head->phone, head->id);
    printf("\t-> debt: %d \n\t-> date: %d/%d/%d \n",head->debt, head->date[0], head->date[1], head->date[2]);
}

void print_list (List *head)
{
    if (!head)
        return;
    print_node(head);
    print_list(head->next);
}

int cmp (int res, char parameter)  
{
    switch (parameter)
    {
        case '<':
            return (res < 0) ? 0 : 1 ;
        case '>':
            return (res > 0) ? 0 : 1 ;
        case '=':
            return (res == 0) ? 0 : 1 ;
        case '!':
            return (res != 0) ? 0 : 1 ;
        default:
            return 1 ;
    }
}

void print_query (Select *pro_query, List *head)
{
    if (!head)
        return;

    switch (pro_query->field)
    {
        case FIRST_N:
            if (!cmp (strcmp(head->first_name, pro_query->to_test_str), pro_query->parameter))
                print_node(head);
            break;
        case LAST_N:
            if (!cmp (strcmp(head->last_name, pro_query->to_test_str), pro_query->parameter))
                print_node(head);
            break;
        case ID:
            if (!cmp(head->id - pro_query->to_test_num[0], pro_query->parameter))
                print_node(head);
            break;
        case PHONE:
            if (!cmp (strcmp(head->phone, pro_query->to_test_str), pro_query->parameter))
                print_node(head);
            break;
        case DEBT:
            if (!cmp(head->debt - pro_query->to_test_num[0], pro_query->parameter))
                print_node(head);
            break;
        case DATE:
            if (!cmp(cmp_date(head->date, pro_query->to_test_num), pro_query->parameter))
                print_node(head);
            break;
    }
    print_query(pro_query, head->next);
}

void update_row (List *a, List *b)
{
    a->debt += b->debt;
    if (cmp_date(a->date, b->date) < 0)
    {
        memcpy(a->date, b->date, sizeof(b->date));
        memcpy(a->phone, b->phone, sizeof(b->phone));
    }
    if (strcmp(a->first_name, b->first_name) || strcmp(a->last_name, b->last_name))
        printf("Warning! found different names for id %09d\n", a->id);
}

List *is_id_exist(List *row, List **head)
{
    List **pNext = head;
    List *temp;
    
    if (!row)
        return NULL;

    while (*pNext)
    {
        if (row->id == (*pNext)->id)
        {
            update_row(row, *pNext);
                temp = *pNext;
                *pNext = (*pNext)->next;
                free(temp);
            return row;
        }
        pNext = &((*pNext)->next);
    }
    return row;
}

void add_to_list (List *row, List **head)
{
    List **temp = head;
    
    if (!row)
    {
        return;
    }

    if (*head == NULL || (*head)->debt > row->debt)
    {
        row->next = *head;
        *head = row;
    }
    else
    {
        while (*temp && (*temp)->debt < row->debt)
        {
            temp = &((*temp)->next);
        }
        row->next = *temp;
        *temp = row;
    }
}
