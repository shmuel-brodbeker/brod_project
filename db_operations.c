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


// void sum_debt (List *head, int *debt, int date[3])
// {
//     List *const_head = head;
//     int id = head->id;
//     while(head)
//     {
//         if ()
//     }
// }

void print_sum_debt(List *head)
{
    int debt = 0;
    int date[3] = 0;
    if (!head)
        return;
    printf("%s, %s, %s, %d  ->  ", head->first_name, head->last_name, head->phone, head->id);
    printf("debt: %d, date: %d/%d/%d \n",head->debt, head->date[0], head->date[1], head->date[2]);
    print_sum_debt (head->next);
}

