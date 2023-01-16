#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_operations.h"
#include "input_processing.h"


void get_query (List *head)
{
    char menu[] = {"Enter a query <quit for exit>"};
    char query[200];
    char command[20];

    while(1)
    {
        printf("\n%s\n-->", menu);
        fgets(query, sizeof(query), stdin);
        sscanf(query, "%s", command);
        if (!strcmp(command, "select"))
        {
            Select *pro_query = check_select_query (query + strlen(command) + 1);
            if (!pro_query)
            {
                puts("Error");
                continue;
            }
            print_query (pro_query, head);
        }
        else if (!strcmp(command, "set"))
        {
            // add_new_client(query + strlen(command) + 1);
        }
        else if (!strcmp(command, "print"))
        {
            print_list(head);
        }
        else if (!strcmp(command, "quit"))
        {
            break;
        }
        else
        {
            puts("Error query word");
            puts("Usage: select, set, print, quit.");
        }
    }
}

void read_file (FILE *file, List **head, List **tail)
{
    char input[200];
    List *row = NULL;

    while (fgets(input, sizeof(input), file))
    {
        row = processing_file(input, sizeof(input));
        if (row)
        {
            row = is_id_exist(row, head);
            add_to_list (row, head);
        }
    }
}

int main (int argc, char **argv)
{
    List *head = NULL, *tail = NULL;

    if (argc < 2)
    {
        puts("Error. no database file name.");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    read_file(file, &head, &tail);
    fclose(file);

    print_list(head);

    get_query(head);

    // list_to_file(head, argv[1]);
    // free_list(head);   
    
    return 0;
}