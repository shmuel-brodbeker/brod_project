#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_operations.h"

enum FIELDS {
    FIRST_N,
    LAST_N,
    ID,
    PHONE,
    DEBT,
    DATE
};

List *processing_file (char *input, int size)
{
    List *row;
    char *start_field = input;
    char *p = input;
    int active_field = FIRST_N;
    int len = 0;

    // if (size < 0);
    
    row = calloc(1, sizeof(List));

    for (int i = 0; i < size; i++, p++, len++)
    {
        if (*p == ',')
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
                    sscanf(start_field ,"%d/%d/%d", &row->date[0], &row->date[1],&row->date[3]);
                    break;
                // default:
            }
            active_field++;
            start_field = p + 1;
            len = -1;
        }
        else if (len == 0) 
        {
            // switch (active_field)
            // {
            //     case FIRST_N:
            //     case LAST_N:
            //         check_name(start_field);
            //         break;
            //     case ID:
            //         check_id(start_field);
            //         break;
            //     case PHONE:
            //         check_phone(start_field);
            //         break;
            //     case DEBT:
            //         check_debt(start_field);
            //         break;
            //     case DATE:
            //         check_date(start_field);
            //         break;
            //     // default:
            // }

            

        }
    }

    // printf("%s\n%s\n%d\n", row->first_name, row->last_name, row->id);

    return row;
}