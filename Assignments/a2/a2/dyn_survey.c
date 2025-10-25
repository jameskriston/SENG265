/* dyn_survey.c */

// James Kriston V00993475 SENG265 Assignment 2 

/*
READ BELOW!!!!!!! *****
Had some issues with gitlabs remote repository so it may show like I am doing this all in 1 commit but I have been making commits locally as I go.
I made a repository through gitlabs website but you're apparently not allowed to push to it if you do that (weird gitlab permissions). 
In an attempt to troubleshoot that issue I rebased, force pushed, new branches. Once the ECS helpdesk deleted it (it only got deleted on day of submission)
I just decided to start fresh and delete my local a2 repo (I had backups of all the .c and .h files on my personal github) then 
make a new local repository and reclone it to the properly made a2 repo. 
I made many commits and did communicate this with both the ECS helpdesk and my instructor (Roberto).  please don't take marks off :( 

If if helps, I do have a commit log I saved for troubleshooting so here it is. 


0000000000000000000000000000000000000000 364937fd9f0253cc20967e3bbf0da39f358af690 jameskriston <jameskriston03@gmail.com> 1760658531 -0700	clone: from https://gitlab.csc.uvic.ca/courses/2025091/SENG265_COSI/course_code/a2.git
364937fd9f0253cc20967e3bbf0da39f358af690 dc40632b807ab7fe9703dadba42c2841db3c4067 
jameskriston <jameskriston03@gmail.com> 1760697174 -0700	commit: Changed structs to accomodate new data requirements,
slightly modified all memory allocations, and split everything into different files. Need to fix some poorly written algorithms for processing the percents,weights etc. 
Very sleep and can't think how to do basic math and looping. Reused my Assignment 1 structures hence the minimal amount of rewriting everything I had to do.
Did have to add a function to read and write the citizenship status and undergrad program. Time for bed :D

READ ABOVE!!!!!!! *****
Some things to note about this project:
There is one function that is open source and not my own code, that is the strdup() function in input_handling.c.
I have included the correct citation for this as per the author's instructions.
I put free() function in input_handling to handle all memory deallocation but I would have liked for it to be a seperate file, although for the 
instructions of the assignment I kept it to just the files requested. 

This program is essentially my assignment 1 (which I conviently used a list type structure for) so I already had a majority of the
program structure completed, or just needing slight modifications to accommodate the Respondent, Undergrad Program, and Citizenship/Immigration Status. 
Not much else to include here, I probably spent more time troubleshooting gitlabs and spending hours in a git bash terminal than I did actually coding the project.

Thanks for coming to my TED talk :)

*/

#include "dyn_survey.h"
#include "input_handling.h"
#include "output.h"
#include "processing.h"


int main(){

Survey_list list = create_list();  //make dynamic list
Survey_list* list_ptr = &list; //list ptr
int* format = reading(list_ptr); //read input and get an array to hold the test bits
header(list_ptr,format); //print header
test1(list_ptr,format); //run test 1
test2(list_ptr,format); //run test 2
test3(list_ptr,format); //run test 3
free(format); //free all memory
free_list(list_ptr); 
return 0;
}