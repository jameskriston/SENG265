/* survey.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct q_node QNode; //make question node struct, each node holds one question in string format and an array of integers to hold the count for each possible answer
    struct q_node {
        char* question;  // one question as a string
        int* answer_counts; //int array [1,2,3...] where array[i] represents the amount of one specific answer (agree,disagree etc.) in regard to the question
        QNode* next; //ptr to next node
    };
    typedef struct {
        QNode* front; //front of survey list
        char** answer_options; //an array of strings to hold each possible answer (agree,disagree etc.)
        int total_options; //int for amount of different possible answers (disagree, agree, = 2) or (disagree,partly agree, agree = 3)
        int total_questions; //int for total amount of questions
    } Survey_list; //will be of type "Survey_list"
    
/* Function Descriptions are described in each respective function def below main()  */

QNode* create_list_node(Survey_list* list, char* question, int* answer_counts, QNode* next);  //create node prototype

Survey_list create_list(); //create survey list prototype

void list_insert_back(Survey_list* list,char* question, int* answer_counts); //insert back prototype

void free_list(Survey_list* list); //free memory of list prototype

char* strdup(const char* s); //strdup prototype *** not my own function, check comments in function description below for details and citation!

int* reading(Survey_list* list);

void read_questions(Survey_list* list, char* buffer); //read_questions prototype

void read_answer_type(Survey_list* list,char* buffer); //read_answer_type prototype

void read_answers(Survey_list* list, char* buffer); //read_answers prototype

void sum_answers(Survey_list* list, int question_num, int answer_index); //sum_answers prototype

void read_answer_type_helper(Survey_list* list, char* buffer); //read_answer_type_helper prototype

char* remove_trailing_char(char* str_ptr); //remove_trailing_char prototype 

char* trim(char* s); //trim prototype

int main(){
    
     Survey_list list = create_list(); //make list
     Survey_list* list_ptr = &list; //make pointer to list
     int* int_ptr; 
     int_ptr = reading(list_ptr);
     int respondents = int_ptr[2];
     if(int_ptr[2]==0|| (int_ptr[0]==0 && int_ptr[1]==0)){
        return 1;
     }

   printf("ECS Student Survey\nSURVEY RESPONSE STATISTICS\n\nNUMBER OF RESPONDENTS: %d\n", int_ptr[2]);

     if(int_ptr[0]==1){
    printf("\n####\nFOR EACH QUESTION/ASSERTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");
    QNode* current2 = list_ptr->front;
    int question_index = 1;
    while (current2 != NULL) {
         int sum = 0;
  
         for (int p = 0; p < list_ptr->total_options; p++) {
              sum += current2->answer_counts[p];
             }

    printf("%d. %s\n", question_index, current2->question);

        for (int p = 0; p < list_ptr->total_options; p++) {
        double percent = (sum > 0) ? (current2->answer_counts[p] * 100.0) / (double)sum : 0.0;
        printf("%.2f: %s\n", percent, list_ptr->answer_options[p]);
         }
    printf("\n");

    current2 = current2->next;
    question_index++;
    }
}

    if(int_ptr[1]==1){
    double avg = 0;
    double sum2 = 0;

    printf("\n####\nFOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT\n\n");
     QNode* current3=list_ptr->front;
     int z = 0;
     while(current3!=NULL && z<list_ptr->total_questions){
    
                for(int y = 1; y<list_ptr->total_options+1; y++){
                    sum2 += current3->answer_counts[y-1]*y;

                }
                avg=sum2/respondents;
                 printf("%d. %s - %.2f\n",z+1,current3->question,avg);
                 avg=0;
                 sum2=0;
                 current3=current3->next;
    }
}

            free_list(list_ptr); //free memory

       return 0; 
       
    }

/*
Function:       read_questions()
Description:    reads the survey questions from input file, then stores them in nodes in the Survey list, utilizing other helper functions
Parameters:     Survey_list* list - input the empty list to add questions to
Return:         no return


*/
int* reading(Survey_list* list){
    int* format_arr = malloc(3*sizeof(int));
    int flag1=0; //flag 1 and flag2 are used to hold the on/off values from .txt values for testing
    int flag2=0;
    int flag3=0;
    int respondents = 0;
    char buffer[2000];
    while(fgets(buffer, sizeof(buffer), stdin)!=NULL){ //loop through every line in document until we reach EOF
     
        if(buffer[0]=='#'){
            continue;
        }
        if(sscanf(buffer, "%d,%d", &flag1, &flag2)==2){ 
            format_arr[0]=flag1;
            format_arr[1]=flag2;
            continue;//
        }
        else if(strchr(buffer, ',')==NULL)  {
           
            read_questions(list,buffer);
          
        }
        else if(strchr(buffer, ';')==NULL && list->total_options==0){
         
            read_answer_type(list,buffer);
        }
        else {
            if(flag3==0){


            QNode* current = list->front;
                while(current!=NULL){
                    current->answer_counts = calloc(list->total_options, sizeof(int));
                    if(current->answer_counts==NULL){
                        exit(69);
                    }
                    current = current->next;
                    
                }
                flag3=1;
                
                }
                
            read_answers(list,buffer);
            respondents++;
        
        }
    }
    format_arr[2]=respondents;
    return format_arr;
}
char* remove_trailing_char(char* str){
    char* str_ptr = str;
    for(int k = strlen(str_ptr); k>0; k--){
        if(str_ptr[k-1] == '\n' || str_ptr[k-1] == '\r'){
            str_ptr[k-1] = '\0';
        }
    }
    return str_ptr;
}
char* trim(char* s) {
    // remove leading whitespace
    while (isspace((unsigned char)*s)) s++;
    if (*s == 0) return s;
    // remove trailing whitespace
    char* end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return s;
}
void read_questions(Survey_list* list, char* buffer){
   
     char* question_ptr; //tempoary pointer for using strtok
     int num = 0; //variable to count # of questions
            question_ptr = strtok(buffer, ";"); //set question ptr to the new token, this will be question 1
            
                while(question_ptr!=NULL){ //until question ptr becomes NULL (or end of the line of questions)
                    num++;
                    list_insert_back(list,(question_ptr),NULL); //add a new question to the list

                    question_ptr=strtok(NULL, ";"); //new token with strtok, advancing to next question
                  
             }
            
            list->total_questions=num;
            
           }
/*
Function:
Description:
Parameters:
Return:

*/
void read_answer_type_helper(Survey_list* list, char* buffer){

char temp[1024];
strcpy(temp,buffer);
char* str_ptr;

 int i = 0;
    str_ptr = strtok(temp, ",");
           
            while(str_ptr!=NULL){
                i++;   
                str_ptr=strtok(NULL, ",");
                }
list->answer_options = malloc(i*sizeof(char*));
    list->total_options = i;
return;
}
 

void read_answer_type(Survey_list* list, char* buffer){
   
    char* str_ptr; //tempoary pointer for using strtok
    char temp[1024];  
    strcpy(temp,buffer);
    read_answer_type_helper(list,buffer);

    int j = 0;
    str_ptr = strtok(temp,",");
            while(str_ptr!=NULL&& j<list->total_options){
                

                list->answer_options[j] = strdup(remove_trailing_char(str_ptr));
                    str_ptr=strtok(NULL,",");
                    j++;
            }
    }    
  

void read_answers(Survey_list* list, char* buffer){
     
    char* answer_ptr; //tempoary pointer for using strtok
    
    int question_index = 0;
    answer_ptr = strtok(buffer, ",");
        while(answer_ptr!=NULL){
            
                question_index++;
                answer_ptr = trim(answer_ptr);

                    for( int i = 0; i<list->total_options; i++){
                      
                        if(strcmp(answer_ptr,list->answer_options[i])==0){
                            sum_answers(list,question_index,i);
                            break;
                         }
                       }
                       answer_ptr = strtok(NULL, ",");
                       
                    }
          
}
void sum_answers(Survey_list* list, int question_num, int answer_index){
    QNode* current_node = list->front; //begin at front of list with current node
       
    for(int i = 1; (i<question_num && current_node!=NULL); i++){
    
                   current_node=current_node->next;
                 }
            
    if(current_node == NULL){
         return;
    }

    current_node->answer_counts[answer_index]++;
}


/*
** Copyright 2001-2004, Travis Geiselbrecht.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions, and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions, and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

https://github.com/travisg/newos/blob/master/lib/libc/string/strdup.c 


This function is a implementation of string.h strdup(). strdup is not part of c11 std and is meant for linux systems, 
below is this open source implementation of strdup for C11 from Travis Geiselbrecht, the link for the github source is above.

*/
            
char* strdup(const char* str) //This function duplicates a the string input paramater and returns a pointer to the duplicated memory allocated string 
{
	size_t len;
	char *copy;
	
	len = strlen(str) + 1;    
	copy = malloc(len);
	if (copy == NULL)
		return NULL;
	memcpy(copy, str, len);
	return copy; 
} //Once again, not my function but is an open source free to use function with citation above.

/*
Function:       create_list_node
Description:    creates an element of type QNode* with dynamic memory and returns a pointer to use with the Survey_list
Parameters:     char* question      (one survey question as a string)
                int*  answer_counts (int array to store the # of answers for each possible answer to question)
                Qnode* next         (pointer to next node)
Returns:        QNode* node         (Returns a node address)   
*/

QNode* create_list_node(Survey_list* list, char* question, int* answer_counts, QNode* next){ 

    QNode*  node = malloc(sizeof(QNode)); //allocate memory for new node
   if(node==NULL){
    // printf("Error in memory allocation.\n"); 
    exit(1); //exit if malloc doesnt work
   }
   
    node->question =  strdup(question);//give node the question using strdup (utilizies dynamic memory) from string.h,strdup duplicates string and returns pointer to the duplicated string (needs to be freed)
    if(node->question==NULL){
       // printf("Error in memory allocation.\n");
        exit(1); //exit if strdup doesnt work (memory leaks are bad)
    }

    node-> next = next;  //go to next node

    return node; 
}

/*
Function:    create_list
Description: creates our previously defined Survey_list struct with no elements (NULL)
Returns:     Survey_list list 
*/

Survey_list create_list(){
    Survey_list list; //make a new empty list with everything set to null or 0
    list.front = NULL; 
    list.total_options = 0;
    list.total_questions=0;
    
    return list; 
}

/*
Function:        list_insert_back
Description:     Calls create_list_node to create a new node with required parameters and then inserts this node at the back of list (or front if list empty)
Parameters:      Survey_list* list (pointer to list), char* question (one survey question as a string), int* answer_counts (int array to store the # of answers for each possible answer to question)), int num (used to update # of questions)
Returns:         n/a

*/

void list_insert_back(Survey_list* list, char* question, int* answer_counts){
    if (list->front == NULL){
        list->front = create_list_node(list,question,answer_counts, NULL);  //if front of list is NULL, then list is empty, and the new node is set to front of list
    } else {
        QNode* current_node = list->front; //create placeholder current_node to iterate through list until NULL is reached (back of list)
        while (current_node->next != NULL) { 
            current_node = current_node->next; 
        }
        current_node->next = create_list_node(list,question,answer_counts, NULL); //once the "next" points to nothing, we can insert a new node at this location
    }
}

/*
Function:       free_list
Description:    Function to ensure all allocated memory used in program is freed, preventing memory leaks
Parameters:     Survey_list* list_ptr  (a pointer to the survey list) 
Returns:        n/a

*/
void free_list(Survey_list* list_ptr) {
    QNode* current_node = list_ptr->front; //begin at front of list with current node
    QNode* tmp = current_node; //temp node for navigating list

    while (current_node != NULL) { //while() loop to iterate through the list
        tmp = current_node;
        current_node = current_node->next;
        free(tmp->question); //free question string
        free(tmp->answer_counts); //free counts array
        free(tmp); //free node
    }
    if(list_ptr->answer_options!=NULL){ //check if answer_options string array is NULL, if not then there is memory and it must be freed

        for(int i=0; i<list_ptr->total_options; i++){ //loop through string array
            free(list_ptr->answer_options[i]); //free every element [i]
        }
        free(list_ptr->answer_options); //free the array itself
    }

    list_ptr->front = NULL; //safety measure for ensuring memory is free and nothing weird happens
    list_ptr->answer_options = NULL; //same as line above
}

