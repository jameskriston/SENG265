/*In the survey questionnaire, there are 12 statements. Each item is answered in a Likert scale with four levels of
agreement to the statements: disagree, partially disagree, partially agree and agree. From each answer, researchers
convert the answers into numbers in scale from 1 to 4. In doing so, they can easily compute both frequencies for each
level and the average response for each question (a real number between 1 and 4).
Researchers asked the software developers to generate some statistics as output:
1. The relative frequency (percentage) of each level of agreement for each question;
2. The average response for each question. */


/* survey.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*Simple code to just read the contents of file and print to terminal*/

int main(){
    char buffer[1024];
  
    while(fgets(buffer, sizeof(buffer), stdin)) {
     
            printf("%s",buffer);
            
        
    }
return 0;
}