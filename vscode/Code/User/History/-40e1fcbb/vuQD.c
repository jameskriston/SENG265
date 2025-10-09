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
    if(argc!=2){
        printf("You entered too many integers, or zero, terminating program");
        return 0;
    }
    if(atoi(argv[1])==0){
        printf("You entered an argument that is not a number.");
        return 0;

    }
  
    
    /*
     * Takes the command line input and converts it into int.
     */
    int num = atoi(argv[1]);
   // printf("%d\n", num);

  if(num==1||num==0){
    printf("1\n");
    exit(0);
  }
       
        for(long int i=num; i>0; i--){
            factorial *= i;
        }
     

    printf("%d\n", factorial);
}
