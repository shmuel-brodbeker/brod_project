#ifndef _DB_OPERATIONS_H_
#define _DB_OPERATIONS_H_

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

void build_sort_list (List*, Sort_list**, Sort_list**);
void print_sort_list(Sort_list*);



#endif