#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "db_operations.h"

enum FIELDS {
    FIRST_N,
    LAST_N,
    ID,
    PHONE,
    DEBT,
    DATE
};

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

int check_name(char *str, int len)
{
    if (len == 0)
        return 1;

    for (int i = 0; i < len; i++)
    {
        // Checks for valid characters in a name
        if (str[i] >= 'a' && str[i] <= 'z')
            continue;

        if (str[i] == ' ' || str[i] == '_')
            continue;

        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += ('a' - 'A');
        }
        else
        {
            strcpy(str, "<Invalid name>");
            return 1;
        }
    }
    return 0;
}    

int check_id (int id)
{
    char check[20];
    sprintf(check, "%d", id);
    if (strlen(check) != 9)
        return 1;    
}

int check_phone (char *str, int len)
{
    if (str[0] != '0' || len != 10)
    {
        strcpy(str, "<rng num>");
        return 1;
    }
    return 0;
}

int check_date (int *date)
{
    int d = date[0], m = date[1], y = date[2];
    if (d < 0 || d > 31 || m < 0 || m > 12)
    {
        date[0] = 0, date[1] = 0, date[2] = 0;
        return 1;
    }
    return 0;
}

List *processing_file (char *input, int size)
{
    List *row;
    char *start_field = input, *p = input;
    int active_field = FIRST_N;
    int len = 0;

    row = calloc(1, sizeof(List));

    for (int i = 0; i < size; i++, p++, len++)
    {
        if (*p == '\n' && active_field < DATE)
        {
            goto err;
        }

        if (*p == ',' || *p == '\n' && active_field == DATE)
        {
            switch (active_field)
            {
                case FIRST_N:
                    strncpy(row->first_name, start_field, len);
                    break;
                case LAST_N:
                    strncpy(row->last_name, start_field, len);
                    break;
                case ID:
                    sscanf(start_field ,"%d", &row->id);
                    break;
                case PHONE:
                    strncpy(row->phone, start_field, len);
                    break;
                case DEBT:
                    sscanf(start_field ,"%d", &row->debt);
                    break;
                case DATE:
                    sscanf(start_field ,"%d%*c%d%*c%d", &row->date[0], &row->date[1],&row->date[2]);
                    break;
           }
            active_field++;
            start_field = p + 1;
            len = -1;
        }

        if (*p == '\n')
        {
            break;
        }
    }
    check_name (row->first_name, strlen(row->first_name));
    check_name (row->last_name, strlen(row->last_name));
    check_id(row->id);
    check_phone(row->phone, strlen(row->phone));
    check_date(row->date);
    
    return row;

err:
    free(row);
    puts("Error. Too few arguments"); // debug 
    return NULL;
}