#ifndef _DYN_SURVEY_H_
#define _DYN_SURVEY_H_

/* add your library includes, constants and typedefs here*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



 
typedef struct Respondent
{
    char* program;     // their school program as a string
    char* status;      // their citizenship/immigration status
} Respondent;

typedef struct Response 
{
    int *answers;      // int array to hold a value between 1-4 for their answer to a question. the index of the array represents the question number
    Respondent* respondent; // pointer to respondent struct
    struct Response* next; // pointer to next response in linked list
} Response;

 typedef struct Survey_list
{
    Response *front;          // front of survey list
    char ** questions;     // arary of strings to hold each question
    char **question_options; // an array of strings to hold each possible answer
    char ** programs;    // array of strings to hold each possible program
    char **citizenship;     // array of strings to hold each possible citizenship status
    int total_programs; // int for amount of different possible programs
    int total_citizenships; // int for amount of different possible citizenships                        
    int total_options;     // int for amount of different possible answers (disagree,                                  
    int total_questions;   // int for total amount of questions 
} Survey_list;



#endif
