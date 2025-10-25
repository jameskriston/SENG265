/* input_handling.c */
#include "input_handling.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read bits, program, status, questions, question answers, # responses, then
// repondent answers with in format : program, status, answer1,answer2,answer3...

int *reading(Survey_list *list) {
  int *format_arr =
      malloc(4 * sizeof(int)); // allocate space for our format array
  if (format_arr == NULL)      // if allocation fails exit program
  {
    printf("Memory error\n");
    exit(69);
  }
  int flag = 0; // flag to check if questions have been read
  int flag0 =
      0; // flag 0 for bit 0, flag 1 for bit 1, flag 2 for bit 2, and flag 3 is
         // used to check if answer counts have been allocated space in memory
  int flag1 = 0; // flag 1 for bit 1, flag 2 for bit 2, and flag 3 is used to
                 // check if answer counts have been allocated space in memory
  int flag2 = 0;

  int responses = 0; //# of students answering surveys
  char buffer[2000]; // buffer to hold each line of input
  while (fgets(buffer, sizeof(buffer), stdin) !=NULL) { // loop through every line in document until we reach EOF

    if (buffer[0] == '#') // if line begins with # skip the line
    {
      continue;
    }
    if (sscanf(buffer, "%d,%d,%d", &flag0, &flag1, &flag2) ==
        3) // check for bits in a,b format where a,b are 1 or 0
    {

      format_arr[0] = flag0;
      format_arr[1] = flag1;
      format_arr[2] = flag2;
      continue; //
    }

    else if (list->programs == NULL) { // if programs havent been read yet, read them first

      read_program(list, buffer);
    }

    else if (list->citizenship == NULL) { // if status havent been read yet, read them second

      read_status(list, buffer);
    }

    else if (list->questions == NULL && flag == 0) { // if questions havent been read yet, read them third

      read_questions(list, buffer);
      flag =
          1; // set flag to 1 so we dont mistakenly read any answers asquestions

    } else if (list->total_options == 0) { // if answer types havent been read yet, read them fourth
      read_answer_type(list, buffer);
    }

    else if (sscanf(buffer, "%d", &responses) == 1) { // if we can read an integer from the line, this is the # of
                  // responses
      format_arr[3] = responses;
    }

    else {

      read_answers(list, buffer); // finally read each respondents answers
    }
  }
  return format_arr;
}

Response *
list_insert_back(Survey_list *list) // basic linked list insert function
{
  if (list->front == NULL) {
    list->front = create_response(list);
    return list->front;
  } else {
    Response *current_response =
        list->front; // create placeholder current_response to iterate through
                     // list until NULL is reached (back of list)
    while (current_response->next != NULL) {
      current_response = current_response->next;
    }
    current_response->next =
        create_response(list);     // once the "next" points to nothing, we can
    return current_response->next; // insert a new node at this location with
                                   // our create node helper
  }
}

void free_list(Survey_list *list_ptr) // function to free all allocated memeory,
                                      // avoids memory leaks.
{
  Response *current =
      list_ptr->front;      // begin at front of list with current node
  Response *temp = current; // temp node for navigating list

  while (current != NULL) { // while() loop to iterate through the list
    temp = current;
    current = current->next;
    free(temp->respondent->program); // free program string
    free(temp->respondent->status);  // free status string
    free(temp->respondent);          // free question string
    free(temp->answers);             // free counts array
    free(temp);                      // free node
  }
  if (list_ptr->question_options != NULL) { // check if answer_options string array is NULL, if not then there
              // is memory and it must be freed

    for (int i = 0; i < list_ptr->total_options;
         i++) {                            // loop through string array
      free(list_ptr->question_options[i]); // free every element [i]
    }
    free(list_ptr->question_options); // free the array itself
  }
  if (list_ptr->programs != NULL) { // check if answer_options string array is NULL, if not then there
              // is memory and it must be freed

    for (int i = 0; i < list_ptr->total_programs;
         i++) {                    // loop through string array
      free(list_ptr->programs[i]); // free every element [i]
    }
    free(list_ptr->programs); // free the array itself
  }
  if (list_ptr->citizenship != NULL) { // check if answer_options string array is NULL, if not then there
              // is memory and it must be freed

    for (int i = 0; i < list_ptr->total_citizenships; i++) {                       // loop through string array
      free(list_ptr->citizenship[i]); // free every element [i]
    }
    free(list_ptr->citizenship); // free the array itself
  }

  if (list_ptr->questions != NULL) { // check if answer_options string array is NULL, if not then there
              // is memory and it must be freed

    for (int i = 0; i < list_ptr->total_questions; i++) {                     // loop through string array
      free(list_ptr->questions[i]); // free every element [i]
    }
    free(list_ptr->questions); // free the array itself
  }

  list_ptr->programs = NULL;
  list_ptr->citizenship = NULL;
  list_ptr->questions = NULL;
  list_ptr->question_options = NULL;
  list_ptr->front = NULL; // set all this to null as a precaution
}

Survey_list create_list() {
  Survey_list list; // make a new empty list with everything set to null or 0
  list.front = NULL;
  list.questions = NULL;
  list.question_options = NULL;
  list.programs = NULL;
  list.citizenship = NULL;
  list.total_options = 0;
  list.total_questions = 0;
  list.total_programs = 0;
  list.total_citizenships = 0;
  return list;
}

Response *create_response(Survey_list *list) {

  Response *response = malloc(sizeof(Response)); // allocate memory for new node
  if (response == NULL) {
    printf("Memory error\n");

    exit(1); // exit if malloc doesnt work
  }
  response->respondent = malloc(sizeof(Respondent));
  if (response->respondent == NULL) {
    printf("Memory error\n");

    exit(69);
  }
  response->respondent->program = NULL; //
  response->respondent->status = NULL;  //
  response->answers = NULL;
  response->next = NULL; //
  return response;
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

void read_answers(Survey_list *list, char *buffer) {

  char *temp_ptr; // tempoary pointer for using strtok

  temp_ptr = strtok(buffer, ","); // tokenize each time a comma is reached
  Response *response = list_insert_back(
      list); // insert new response node at back of list and get pointer to it
  response->respondent->program =
      strdup(temp_ptr); // duplicate program string into respondent struct
  temp_ptr = strtok(NULL, ",");
  response->respondent->status =
      strdup(temp_ptr); // duplicate status string into respondent struct
  temp_ptr = strtok(NULL, ",");
  int num = 0;
  response->answers = calloc(
      list->total_questions,
      sizeof(int)); // allocate space for answers array in response struct
  if (response->answers == NULL) {
    printf("Memory error\n");

    exit(69);
  }
  while (temp_ptr != NULL) // iterate through each student's answers
  {
    temp_ptr = trim(temp_ptr);
    for (int i = 0; i < list->total_options;
         i++) { // iterate through each possible answer

      if (strcmp(temp_ptr, list->question_options[i]) ==
          0) { // if the string in temp matches some question answer

        response->answers[num] = i;
        num++;
        break;
      }
    }
    temp_ptr = (strtok(NULL, ","));
  }
}

char *trim(char *s) {

  while (isspace(*s)) // while there's leading spaces move pointer forward by 1
    s++;
  if (*s == 0)
    return s;

  char *end = s + strlen(s) -
              1; // while there's spaces at the end and end > s, set the
                 // character after the last proper character to a terminator
  while (end > s && isspace(*end))
    end--;
  end[1] = '\0';
  return s;
}
void read_questions(Survey_list *list, char *buffer) {

  char *question_ptr; // tempoary pointer for using strtok
  int num = 0;        // variable to count # of questions
  question_ptr =
      strtok(buffer,
             ";"); // set question ptr to the new token, this will be question 1
  char **question_array = NULL;

  while (question_ptr != NULL) {
    char **temp =
        realloc(question_array,
                (num + 1) * sizeof(char *)); // reallocate memory for question
                                             // array to hold num+1 strings
    if (temp == NULL) {
      printf("Memory error\n");

      exit(69);
    }
    question_array = temp;
    question_array[num] =
        strdup(trim(question_ptr)); // duplicate trimmed question string into
                                    // question array at num index
    if (question_array[num] == NULL) {
      printf("Memory error\n");

      exit(69);
    }
    num++;
    question_ptr = strtok(NULL, ";");
  }

  list->questions = question_array; // store question array in list

  list->total_questions = num; // store num in list
}

void read_answer_type_helper(Survey_list *list,char *buffer) // helper function for the function below this
{ // we need to find amount of different answers "i" to store in list, and
  // allocate memory for it

  char temp[1024];
  strcpy(temp, buffer); // store a copy of buffer into temp to not alter buffer
  char *str_ptr;

  int i = 0;
  str_ptr = strtok(temp, ","); // tokenize everytime comma is reached

  while (str_ptr != NULL) {
    i++;
    str_ptr = strtok(NULL, ",");
  }
  list->question_options = malloc(i * sizeof(char *));
  if (list->question_options == NULL) {
    printf("Memory error\n");
    exit(69);
  }
  // make room for i amount of strings (theses are our types of answers) into
  // memory
  list->total_options = i; // store i
  return;
}

void read_answer_type(Survey_list *list, char *buffer) {

  char *str_ptr;   // tempoary pointer for using strtok
  char temp[1024]; // same idea as above, don't want to alter buffer
  strcpy(temp, buffer);
  read_answer_type_helper(list, buffer); // call helper function

  int j = 0;
  str_ptr = strtok(temp, ","); // tokenize each time a comma is reached
  while (str_ptr != NULL &&
         j < list->total_options) // now we know total options of answers, we
                                  // can easily cycle through our array
  {
    list->question_options[j] =
        strdup(trim(str_ptr)); // duplicate a trimmed string into answer_options
                               // array at j element
    str_ptr = strtok(NULL, ",");
    j++;
  }
}

void read_program(Survey_list *list, char *buffer) {

  int num = 0; // variable to count # of programs
  char *program_ptr = strtok(buffer, ",");
  char **program_array = NULL;

  while (program_ptr != NULL) {
    char **temp =
        realloc(program_array,(num + 1) * sizeof(char *)); // reallocate memory for program
                                             // array to hold num+1 strings
    if (temp == NULL) {
      printf("Memory error\n");

      exit(69);
    }
    program_array = temp;
    program_array[num] = strdup(trim(program_ptr)); // duplicate trimmed program string 
    if (program_array[num] == NULL) {
      printf("Memory error\n");

      exit(69);
    }
    num++;
    program_ptr = strtok(NULL, ",");
  }
  list->programs = program_array; // store program array in list
  list->total_programs = num;     // store num in list
}

void read_status(Survey_list *list, char *buffer) {

  int num = 0; // variable to count # of statuses
  char *status_ptr = strtok(buffer, ",");
  char **status_array = NULL;

  while (status_ptr != NULL) {
    char **temp =
        realloc(status_array, (num + 1) * sizeof(char *)); // reallocate memory for status
                                             // array to hold num+1 strings
    if (temp == NULL) {
      printf("Memory error\n");

      exit(69);
    }
    status_array = temp;
    status_array[num] =
        (strdup(trim(status_ptr))); // duplicate trimmed status string into
                                    // status array at num index
    if (status_array[num] == NULL) {
      printf("Memory error\n");

      exit(69);
    }
    num++;
    status_ptr = strtok(NULL, ",");
  }

  list->citizenship = status_array; // store status array in list
  list->total_citizenships = num;   // store num in list
}
