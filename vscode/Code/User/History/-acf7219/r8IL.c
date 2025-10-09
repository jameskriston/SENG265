/* survey.c */

/*

James Kriston V00993475
Assignment 1 - survey.c
10/8/2025

Note: I made this a bit more complex than it needed to be by using structs.
      I made the structure using a typical nodal linked list format as is common in C
      However I went with the first version of this structure which in hindsight could have 
      been better, I'm not too happy with how and where I defined things like the 
      different answer options and the number of them, as well as the questions and answers.
      It did end up working just fine but just didn't end up looking as clean as I'd hoped.
      Fortunately Assignment 2 looks very similar and is specifically asking to use structures
      so it looks like I saved myself lots of work on Assignment 2 by overengineering Assignment 1
      I did my best to clean up and format using the Prettier extension on VScode, and used what
      I think is a healthy amount of helper functions to split the tasks somewhat evenly. 

      Lastly, there's a function in here which is not one of my own, it is from a user on github. 
      There is a citation to go with it and the user's policy of adding his copyright statement 
      right above the function.

      

*/




#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct q_node
    QNode; // make question node struct, each node holds one question in string
           // format and an array of integers to hold the count for each
           // possible answer
struct q_node
{
    char *question;     // one question as a string
    int *answer_counts; // int array [1,2,3...] where array[i] represents the
                        // amount of one specific answer (agree,disagree etc.) in
                        // regard to the question
    QNode *next;        // ptr to next node
};
typedef struct
{
    QNode *front;          // front of survey list
    char **answer_options; // an array of strings to hold each possible answer
                           // (agree,disagree etc.)
    int total_options;     // int for amount of different possible answers (disagree,
                           // agree, = 2) or (disagree,partly agree, agree = 3)
    int total_questions;   // int for total amount of questions
} Survey_list;             // will be of type "Survey_list"

/* Function Descriptions are described in each respective function def below
 * main()  */

QNode *create_list_node(Survey_list *list, char *question, int *answer_counts,
                        QNode *next); // create node prototype

Survey_list create_list(); // create survey list prototype

void list_insert_back(Survey_list *list, char *question,
                      int *answer_counts); // insert back prototype

void free_list(Survey_list *list); // free memory of list prototype

char *strdup(const char *s); // strdup prototype *** not my own function, check comments
                             // in function description below for details and citation!

int *reading(Survey_list *list); //reading() prototype

void read_questions(Survey_list *list,
                    char *buffer); // read_questions prototype

void read_answer_type(Survey_list *list,
                      char *buffer); // read_answer_type prototype

void read_answers(Survey_list *list, char *buffer); // read_answers prototype

void sum_answers(Survey_list *list, int question_num,
                 int answer_index); // sum_answers prototype

void read_answer_type_helper(Survey_list *list,
                             char *buffer); // read_answer_type_helper prototype
char *trim(char *s); // trim prototype



int main()
{

    Survey_list list = create_list(); // make list
    Survey_list *list_ptr = &list;    // make pointer to list
    int *format_arr;                  //array to hold the # responses as well as the 2 test bits
    format_arr = reading(list_ptr);   // pass reading() function the list and the array described above will return to this format array pointer


    int respondents = format_arr[2];
    if (format_arr[2] == 0 || (format_arr[0] == 0 && format_arr[1] == 0))     // Check if either no responses, or no bits found, in which case return as
                                                                              // there would be nothing for my program to do.        
    {
        return 0;
    }

    printf("ECS Student Survey\nSURVEY RESPONSE STATISTICS\n\nNUMBER OF "   //print header of file
           "RESPONDENTS: %d\n",
           format_arr[2]);

    if (format_arr[0] == 1) //if 1st bit set to on
    {
        printf("\n#####\nFOR EACH QUESTION/ASSERTION BELOW, RELATIVE PERCENTUAL " //print another header
               "FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");

        QNode *current2 = list_ptr->front; 
        int question_index = 1;
        while (current2 != NULL) //basic looping through my linked list
        {
            int sum = 0;  //sum for computing %

            for (int p = 0; p < list_ptr->total_options; p++) //iterate through each question's answer array where elements 0,1,2,3 represent one of four possible answers
            {
                sum += current2->answer_counts[p]; //sum those answers
            }

            printf("%d. %s\n", question_index, current2->question);
            for (int p = 0; p < list_ptr->total_options; p++) //nested list for the computation of  percentages
            {
                double percent = (current2->answer_counts[p] * 100.0) / (double)sum;
                printf("%.2f: %s\n", percent, list_ptr->answer_options[p]);
            }
            if (question_index != 12) //this is to add a \n between questions, but do not add a new line if last question
            {
                printf("\n");
            }
            current2 = current2->next; 
            question_index++;
        }
    }
    if (format_arr[1] == 1) //if 2nd bit set to on
    {
        double avg = 0; 
        double sum2 = 0;

        printf("\n#####\nFOR EACH QUESTION/ASSERTION BELOW, THE AVERAGE RESPONSE " //header
               "IS SHOWN (FROM 1-DISAGREEMENT TO 4-AGREEMENT)\n\n");
        QNode *current3 = list_ptr->front;
        int z = 0;
        while (current3 != NULL && z < list_ptr->total_questions) //iterate through questions like before with current3 as list front
        {

            for (int y = 1; y < list_ptr->total_options + 1; y++) //iterate through each type of answer
            {
                sum2 += current3->answer_counts[y - 1] * y; //because index y=1 we must use y-1, to begin at index 0
             }                                              // then multiply by y as that is the weight of each answer, 1 - disagree, 2 - partial disagree, etc.

            avg = sum2 / respondents; 
            printf("%d. %s - %.2f\n", z + 1, current3->question, avg); //compute then print average reponse

            avg = 0;
            sum2 = 0;
            current3 = current3->next;
            z++;
        }
    }
    free(format_arr); //free the array above as it was dynamically allocated in reading() below
    free_list(list_ptr); // free memory of everything else

    return 0;
}

int *reading(Survey_list *list)
{
    int *format_arr = malloc(3 * sizeof(int)); //allocate space for our format array 
    if (format_arr == NULL) //if allocation fails exit program
    {
        exit(69);
    }
    int flag1 = 0; //flag 1 for bit 1, flag 2 for bit 2, and flag 3 is used to check if answer counts have been allocated space in memory
    int flag2 = 0;
    int flag3 = 0;
    int respondents = 0; //# of students answering survey
    char buffer[2000];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    { // loop through every line in document until we reach EOF

        if (buffer[0] == '#') //if line begins with # skip the line
        {
            continue;
        }
        if (sscanf(buffer, "%d,%d", &flag1, &flag2) == 2) //check for bits in a,b format where a,b are 1 or 0
        {
            format_arr[0] = flag1; 
            format_arr[1] = flag2;
            continue; //
        }
        else if (strchr(buffer, ',') == NULL) // Assuming a strict format on survey data, we can check if a line has questions or answers
        {                                     // by checking if it has a comma or semi colon

            read_questions(list, buffer); //if no comma found, it must be that these are questions so call the read questions function 
        }
        else if (strchr(buffer, ';') == NULL && list->total_options == 0) //if no semicolon foun AND we have no answer options yet, it must be the types of answers
        {

            read_answer_type(list, buffer); //call read answer type function
        }
        else
        {
            if (flag3 == 0) //if flag 3 is false we have yet to allocate space for answer counts array 
            {
                QNode *current = list->front; 
                while (current != NULL)
                {
                    current->answer_counts = calloc(list->total_options, sizeof(int)); //use calloc to initialize empty int array for as many elements as there are answer types
                    if (current->answer_counts == NULL)
                    {
                        exit(69); //exit is allocation fails
                    }
                    current = current->next;
                }
                flag3 = 1; //now set flag to 1 so we don't allocate again
            }
            read_answers(list, buffer); //call read answers function
            respondents++; //after we read 1 line of answers, that correlates to one student's data/answers
        }
    }
    format_arr[2] = respondents; 
    return format_arr; //return our formatting array to main
}


char *trim(char *s)
{

    while (isspace(*s)) //while there's leading spaces move pointer forward by 1
        s++;
    if (*s == 0)
        return s;

    char *end = s + strlen(s) - 1; //while there's spaces at the end and end > s, set the character after the last proper character to a terminator
    while (end > s && isspace(*end))
        end--;
    end[1] = '\0';
    return s;
}
void read_questions(Survey_list *list, char *buffer) 
{

    char *question_ptr; // tempoary pointer for using strtok 
    int num = 0;        // variable to count # of questions
    question_ptr =
        strtok(buffer,";"); // set question ptr to the new token, this will be question 1

    while (question_ptr != NULL)
    { // until question ptr becomes NULL (or end of
      // the line of questions)
        num++;
        list_insert_back(list, (trim(question_ptr)),
                         NULL); // add a new question to the list

        question_ptr =
            strtok(NULL, ";"); // new token with strtok, advancing to next question
    }
    list->total_questions = num; //store num in list
}

void read_answer_type_helper(Survey_list *list, char *buffer) //helper function for the function below this
{                                                             // we need to find amount of different answers "i" to store in list, and allocate memory for it

    char temp[1024]; 
    strcpy(temp, buffer); //store a copy of buffer into temp to not alter buffer
    char *str_ptr;

    int i = 0;
    str_ptr = strtok(temp, ","); //tokenize everytime comma is reached

    while (str_ptr != NULL)
    {
        i++;
        str_ptr = strtok(NULL, ",");
    }
    list->answer_options = malloc(i * sizeof(char *)); //make room for i amount of strings (theses are our types of answers) into memory
    list->total_options = i; //store i 
    return;
}

void read_answer_type(Survey_list *list, char *buffer)
{

    char *str_ptr; // tempoary pointer for using strtok
    char temp[1024]; //same idea as above, don't want to alter buffer
    strcpy(temp, buffer);
    read_answer_type_helper(list, buffer); //call helper function

    int j = 0;
    str_ptr = strtok(temp, ","); //tokenize each time a comma is reached
    while (str_ptr != NULL && j < list->total_options) //now we know total options of answers, we can easily cycle through our array 
    {

        list->answer_options[j] = strdup(trim(str_ptr)); //duplicate a trimmed string into answer_options array at j element
        str_ptr = strtok(NULL, ",");
        j++;
    }
}

void read_answers(Survey_list *list, char *buffer)
{

    char *answer_ptr; // tempoary pointer for using strtok

    int question_index = 0;             //keep track of question
    answer_ptr = strtok(buffer, ",");
    while (answer_ptr != NULL)  //iterate through each student's answers
    {

        question_index++;
        answer_ptr = trim(answer_ptr); //trim the answer of any leading/trailing whitespace

        for (int i = 0; i < list->total_options; i++) //cycle through the 4 answer options
        {

            if (strcmp(answer_ptr, list->answer_options[i]) == 0) //if the tokenized pointer is equal to answer_option [i] call sum_answers
            {
                sum_answers(list, question_index, i); //pass our question index, the "i"th answer option, and the list
                break; //if we correctly sum an answer break the loop, no point in checking i+1, i+2 etc.
            }
        }
        answer_ptr = strtok(NULL, ",");
    }
}
void sum_answers(Survey_list *list, int question_num, int answer_index)
{
    QNode *current_node = list->front; // begin at front of list with current node

    for (int i = 1; (i < question_num && current_node != NULL); i++) //cycle through nodes/questions until we get to our desired question number
    {

        current_node = current_node->next;
    }

    if (current_node == NULL) //if we hit a null node, something probably went wrong much earlier in the program
    {
        return;
    }

    current_node->answer_counts[answer_index]++; //incremenet the interger held at the "i"th element in the answer count array
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


This function is a implementation of string.h strdup(). strdup is not part of
c11 std and is meant for linux systems, below is this open source implementation
of strdup for C11 from Travis Geiselbrecht, the link for the github source is
above.

*/

char *strdup(const char *str) // This function duplicates a the string input
                              // paramater and returns a pointer to the
                              // duplicated memory allocated string
{
    size_t len;
    char *copy;

    len = strlen(str) + 1;
    copy = malloc(len);
    if (copy == NULL)
        return NULL;
    memcpy(copy, str, len);
    return copy;
} // Once again, not my function but is an open source free to use function with
  // citation above.

QNode *create_list_node(Survey_list *list, char *question, int *answer_counts,
                        QNode *next)
{

    QNode *node = malloc(sizeof(QNode)); // allocate memory for new node
    if (node == NULL)
    {

        exit(1); // exit if malloc doesnt work
    }

    node->question = strdup(question); // give node the question using strdup (i
                                       // got strdup from citation above)
    if (node->question == NULL)
    {

        exit(1); // exit if strdup doesnt work (memory leaks are bad)
    }

    node->next = next; // go to next node

    return node;
}

Survey_list create_list()
{
    Survey_list list; // make a new empty list with everything set to null or 0
    list.front = NULL;
    list.total_options = 0;
    list.total_questions = 0;

    return list;
}

void list_insert_back(Survey_list *list, char *question, int *answer_counts) //basic linked list insert function
{
    if (list->front == NULL)
    {
        list->front = create_list_node(list, question, answer_counts,NULL); // if front of list is NULL, then list is empty,
                                    // and the new node is set to front of list
    }
    else
    {
        QNode *current_node = list->front; // create placeholder current_node to iterate through list
                         // until NULL is reached (back of list)
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next =
            create_list_node(list, question, answer_counts, NULL); // once the "next" points to nothing, we can
                                                                     // insert a new node at this location with our create node helper
    }
}

void free_list(Survey_list *list_ptr) //function to free all allocated memeory, avoids memory leaks.
{
    QNode *current_node =
        list_ptr->front;       // begin at front of list with current node
    QNode *tmp = current_node; // temp node for navigating list

    while (current_node != NULL)
    { // while() loop to iterate through the list
        tmp = current_node;
        current_node = current_node->next;
        free(tmp->question);      // free question string
        free(tmp->answer_counts); // free counts array
        free(tmp);                // free node
    }
    if (list_ptr->answer_options !=
        NULL)
    { // check if answer_options string array is NULL, if not then there
      // is memory and it must be freed

        for (int i = 0; i < list_ptr->total_options;
             i++)
        {                                      // loop through string array
            free(list_ptr->answer_options[i]); // free every element [i]
        }
        free(list_ptr->answer_options); // free the array itself
    }

    list_ptr->front = NULL;          // safety measure for ensuring memory is free and
                                     // nothing weird happens
    list_ptr->answer_options = NULL; // same as line above
}

