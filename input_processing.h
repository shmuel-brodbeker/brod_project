#ifndef _INPUT_PROCESSING_H_
#define _INPUT_PROCESSING_H_

List *processing_file (char *input, int size);
List *check_double_id(List *row, List *head);
Select * check_select_query (char *input);
List *add_new_row (char *input);

#endif

