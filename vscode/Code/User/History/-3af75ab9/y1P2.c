#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    /*

    declare some variables like max word length etc.
    make some variables to hold questions and answers when scanning, however do not hardcode these, empty string arrays
    questions are separated by semi colons

    open input file with fopen 
        check if file is null, terminate if so


    if input file is valid, begin to read 
     if there is a # at the beginning of a line, ignore that line
        scan for questions and story in string array, they will be separated by semi colon.
        scan for answers after, these are separated by cvommas and there is 2 lines to an answer, first is demographic data, second is respondent's answers to the survey questions.
        make some variables to hold total amount of answers and then update each individual answer so we can get percentages AND MAKE NUMBER OF RESPONDANTS?
        if we find an "agree" add +1 to the variable agree and then store "agree" into a string
        keep iterarting over whole document until we hit EOF and then by this point everything should be stored somewhere so we can write

        for writing, check format of the tests for exact formatting, but find the first question asked, write it, write the average response, then begin new line
            repeat this process until there's no more questions left to write,

            close the file fclose, and return 0; !

            