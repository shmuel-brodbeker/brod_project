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


#endif