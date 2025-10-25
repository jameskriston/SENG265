#ifndef _PROCESSING_H_
#define _PROCESSING_H_

/* add your include and prototypes here*/
#include "dyn_survey.h"

double agreement_percent(Survey_list* list, int question_num,int answer_index); // prototype
double average_response(Survey_list* list, int question_num); // prototype
double  program_percent(Survey_list* list, int program_index); // prototype
double  status_percent(Survey_list* list, int status_index); // prototype


#endif
