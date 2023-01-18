#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_operations.h"

#define MIN_OF(_a, _b) ((_a < _b) ? _a : _b)

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
    if (d < 0 || d > 31 || m < 0 || m > 12 || y < 1900 || y > 2200)
    {
        // for invalid date i reset it NULL
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
    if (!row)
    {
        return NULL;
    }

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
                    if (len != 9)
                    {
                        printf("Warning! wrong ID %d, This row cannot be accepted.\n", row->id);
                        goto err;
                    }
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
    check_phone(row->phone, strlen(row->phone));
    check_date(row->date);
    
    return row;

err:
    free(row);
    return NULL;
}

int found_filed (char **p)
{
    char *fields[] = {"first name", "last name", "id", "phone", "debt", "date"};
    int len = 0;
    char field[11] = {0};
    char *np = *p;

    while ((*np >= 'a' && *np <= 'z') || *np == ' ')
    {
        np++; len++;
    }

    if (*np == '\n' || *np == ',')
        return -1;

    strncpy(field, *p, MIN_OF(len, sizeof(field)));
    *p = np;

    if (!strncmp(field, fields[0], strlen(fields[0])))
        return 0;
    else if (!strncmp(field, fields[1], strlen(fields[1])) 
        || !strcmp(field, "second name"))
        return 1;
    else if (!strncmp(field, fields[2], strlen(fields[2])))
        return 2;
    else if (!strncmp(field, fields[3], strlen(fields[3])))
        return 3;
    else if (!strncmp(field, fields[4], strlen(fields[4])))
        return 4;
    else if (!strncmp(field, fields[5], strlen(fields[5])))
        return 5;
    else
        return -1;
}

Select *check_select_query (char *input)
{
    Select *s_query = calloc(1, sizeof(Select));
    if (!s_query)
    {
        return NULL; // err msg
    }
    
    char *p = input;
    s_query->field = found_filed(&p);
    s_query->parameter = *p;
    
    if (*p == '!')
        p++;    
    do {
        p++;
    } while (*p == ' ');

    switch(s_query->field)
    {
        case FIRST_N:
            sscanf(p, "%19[^\t\n]", s_query->to_test_str);
            check_name(s_query->to_test_str, strlen(s_query->to_test_str));
            break;
        case LAST_N:
            sscanf(p, "%19[^\t\n]", s_query->to_test_str);
            check_name(s_query->to_test_str, strlen(s_query->to_test_str));
            break;
        case ID:
            sscanf(p, "%d", &s_query->to_test_num[0]);
            break;
        case PHONE:
            sscanf(p, "%19[^\t\n]", s_query->to_test_str);
            break;
        case DEBT:
            sscanf(p, "%d", &s_query->to_test_num[0]);
            break;
        case DATE:
            sscanf(p, "%d%*c%d%*c%d", &s_query->to_test_num[0], 
                    &s_query->to_test_num[1], &s_query->to_test_num[2]);
            break;
        default:
            goto err;
    }

    return s_query;

err:
    puts("Error. usage: <field name> <parameter (<, >, =, !=)> <your selection>");
    free(s_query);
    return NULL;
}

List *add_new_row (char *input)
{
    List *new = calloc(1, sizeof(List));
    if (!new)
    {
        puts("Error");
        return NULL;
    }
    char *p = input;
    char *start = input;
    int sum_fields = 6;
    int field = 0;
    int len = 0;

    for (int i = 0; i < sum_fields; i++, field++, p++)
    {
        while(*p == ' ')
        {
            p++;
        }
        field = found_filed(&p);
        // p point now to '='
        do {
            p++;
        } while (*p == ' ');

        start = p;
        len = 0;
        while (*p && *p != ',') 
        {
            if (*p == '\n' && sum_fields == 5)
                goto err;
            p++; len++;
        }
        if (len == 0) 
        {
            goto err;
        }
        switch (field)
        {
            case FIRST_N:
                strncpy(new->first_name, start, len);
                printf("f= %s\n", new->first_name); //
                break;
            case LAST_N:
                strncpy(new->last_name, start, len);
                printf("l= %s\n", new->last_name); // 
                break;
            case ID:
                sscanf(start ,"%d", &new->id);
                if (len != 9)
                {
                    printf("Wrong ID %d, This row cannot be accepted.\n", new->id);
                    goto err;
                }
                printf("id: %d\n", new->id); //
                break;
            case PHONE:
                strncpy(new->phone, start, len);
                printf("phone= %s\n", new->phone); // 
                break;
            case DEBT:
                new->debt = atoi(start);
                printf("debt: %d\n", new->debt); //
                break;
            case DATE:
                sscanf(start ,"%d%*c%d%*c%d", &new->date[0], &new->date[1],&new->date[2]);
                printf("date: %d/%d/%d\n",new->date[0], new->date[1],new->date[2]); //
                break;
        }
        start = p+1;

    check_name (new->first_name, strlen(new->first_name));
    check_name (new->last_name, strlen(new->last_name));
    check_phone(new->phone, strlen(new->phone));
    check_date(new->date);
    
    }
    return new;
err:
    puts("Error"); // err msg
    free(new);
    return NULL;
}