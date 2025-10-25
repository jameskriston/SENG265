/* output.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dyn_survey.h"
#include "processing.h"

void header(Survey_list* list, int* format_array){
 
 printf("ECS Student Survey\nSURVEY RESPONSE STATISTICS\n\nNUMBER OF "   //print header of file
           "RESPONDENTS: %d\n",
           format_array[3]);
 }

 void test1(Survey_list* list, int* format_array ){

if (format_array[0] == 1) //if 1st bit set to on
    {
        printf("\n#####\nFOR EACH QUESTION/ASSERTION BELOW, RELATIVE PERCENTUAL " //print another header
               "FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");
        
        int i = 0;
        while(i<list->total_questions){
            printf("%d. %s\n",i+1,list->questions[i]); //print question number and text

            for(int k = 0; k<list->total_options; k++){ //iterate through each possible answer
               double ratio = agreement_percent(list,i,k); //get percent for that answer
              //  printf("ratio is %.2f\n",ratio);
                printf("%.2f: %s\n",ratio,list->question_options[k]); //print percent and answer text
            }
            if(i!=list->total_questions-1){ 
                printf("\n"); //print newline between questions except after last question
            }
            i++;
        }

    }
}
void test2(Survey_list* list, int* format_array){ 
  if (format_array[1] == 1){ //if 2nd bit set to on

        printf("\n#####\nFOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE " //header
               "IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT)\n\n");

                int i = 0;
                while(i<list->total_questions){ //iterate through each question
                    printf("%d. %s - %.2f\n", i+1,list->questions[i],average_response(list,i)); //print question number, text, and average response
                    i++;
                }

  }
}

void test3(Survey_list* list, int* format_array){

  if(format_array[2]==1){
    printf("\n#####\nFOR EACH DEMOGRAPHIC CATEGORY BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH ATTRIBUTE VALUE\n\nUNDERGRADUATE PROGRAM\n");

            int i = 0;
                while(i<list->total_programs){
                double percent = program_percent(list,i);
                printf("%.2f: %s\n", percent,list->programs[i]); //print percent and program name
                i++;
                }

                printf("\nRESIDENCE STATUS\n"); //print header for status section
                int k = 0;
                while(k<list->total_citizenships){ 
                double percent = status_percent(list,k);
                printf("%.2f: %s\n", percent,list->citizenship[k]); //print percent and status name
                k++;
                }
  }

}