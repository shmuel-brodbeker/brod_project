#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_operations.h"
#include "input_processing.h"

void print_list(List *head)
{
    if (!head)
        return;
    printf("%s, %s, %d\n", head->last_name, head->phone, head->id);
    print_list (head->next);
}

void add_to_list (List *row, List **head, List **tail)
{
    if (*tail)
    {
        (*tail)->next = row;
    }
    *tail = row;
    if ((*head) == NULL)
    {
        *head = *tail;
    }
}

void read_file (FILE *file, List **head, List **tail)
{
    char input[200];
    List *row = NULL;

    while (fgets(input, sizeof(input), file))
    {
        row = processing_file(input, sizeof(input));
        add_to_list (row, head, tail);
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

    // prompt();

    // list_to_file(head, argv[1]);
    // free_list(head);   
    
    return 0;
}