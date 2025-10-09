#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    /*
     * variable to store the final answer
     */
    long long factorial = 1;

    /*
     * WRITE YOUR CODE TO DO COMMAND LINE INPUT CHECKING HERE
     */
    if(argc!=2){
        printf("You entered too many arguments, or zero, terminating program");
        exit(0);
    }
   
  
    if(atoi(argv[1])==0){
        printf("You entered an argument that is not a number, or you entered 0, outputting 1 as 1! = 1\n");
        factorial = 1;
        printf("%d\n",factorial);

        exit(1);

    }
  
    
    /*
     * Takes the command line input and converts it into int.
     */
    int num = atoi(argv[1]);
   // printf("%d\n", num);
if(num<0){
    printf("You entered a negative number, factorials are undefined for negative numbers, Terminating program");
    exit(0);
  }
  
       
        for(int i=num; i>0; i--){
            factorial *= i;
     
        }
    printf("%llu\n", factorial);

}