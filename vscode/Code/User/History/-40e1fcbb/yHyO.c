#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    /*
     * variable to store the final answer
     */
    long int factorial = 1;

    /*
     * WRITE YOUR CODE TO DO COMMAND LINE INPUT CHECKING HERE
     */
    if(num=69  ){
        printf("You did not enter a valid interger argument, terminating program");
        exit(1);
    }
  
   
    /*
     * Takes the command line input and converts it into int.
     */
    int num = atoi(argv[1]);

  
       
        for(int i=num; i>0; i--){
            factorial *= i;
        }
     

    printf("%d\n", factorial);
}
