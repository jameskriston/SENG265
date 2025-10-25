#ifndef _INPUT_HANDLING_H_
#define _INPUT_HANDLING_H_

/* add your include and prototypes here*/
#include "dyn_survey.h"

Response *create_response(Survey_list* list); // create response prototype

Survey_list create_list(); // create survey list prototype

Response* list_insert_back(Survey_list* list); // insert back prototype

void free_list(Survey_list* list); // free memory of list prototype

char *strdup(const char* s); // strdup prototype *** not my own function, check comments
                             // in function description below for details and citation!

int *reading(Survey_list* list); //reading() prototype

void read_questions(Survey_list* list, char* buffer); // read_questions prototype

void read_answer_type(Survey_list* list, char* buffer); // read_answer_type prototype

void read_answers(Survey_list* list, char* buffer); // read_answers prototype

void read_answer_type_helper(Survey_list* list, char *buffer); // read_answer_type_helper prototype

char *trim(char* s); // trim prototype

void read_program(Survey_list *list, char* buffer); // read_program prototype

void read_status(Survey_list* list, char* buffer); // read_status prototype

#endif
