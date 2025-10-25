/* processing.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dyn_survey.h"
#include "processing.h"

double agreement_percent(Survey_list* list, int question_num, int answer_index){
    
 double percent = 0;
 int count = 0;
 int sum = 0;
    Response* current = list->front;
    while(current!=NULL){ // iterate through linked list
         
        if((current->answers[question_num])==answer_index){ // if the answer at question_num matches answer_index
            sum++;
        }
        count++;   
        current=current->next;
            }
            percent = (sum/(double)count)*100; // calculate percent
            return percent;
    
    }

double average_response(Survey_list* list, int question_num){ // question num is index of question to calculate average for
    double average = 0;
    int sum = 0;
            int i = 0;
            Response* current = list->front;
            while(current!=NULL){
                sum += current->answers[question_num]+1; // add 1 to answer to convert from 0-3 to 1-4 scale
                current = current->next;  
                i++;

            }
            average = sum/(double)i;
            return average;

}

double  program_percent(Survey_list* list,int program_index){ // program index is index of program to calculate percent for
    double percent = 0; // percent for program
    int count = 0; // total respondents
    int sum = 0; // sum of matches
        Response* current = list->front;
        while(current!=NULL){
            if(strcmp(current->respondent->program,list->programs[program_index])==0){ //compare strings
                sum++; // increment sum if match
            }
            count++;
            current = current->next;
        }
        percent = (sum/(double)count)*100;
        return percent;

        }
    
double  status_percent(Survey_list* list, int status_index){
    double percent = 0; // percent for status
    int count = 0; // total respondents
    int sum = 0; // sum of matches
      
            Response* current = list->front;

            while(current!=NULL){
            if(strcmp(current->respondent->status,list->citizenship[status_index])==0){ //compare strings
                sum++; // increment sum if match
            }
            count++;
            current = current->next;
            }
        percent = (sum/(double)count)*100; // calculate percent
        return percent;

        }
    