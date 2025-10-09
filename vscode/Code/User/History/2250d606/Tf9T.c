#include <stdlib.h>
#include <stdio.h>




    void main(){
    int a = 0;
    int b = 0;
    int result = 0;
    int remainder = 0;   

    printf("Enter M for multiplication or D for division\n");
    
        ch = getchar();
        if(ch =='m' || ch =='M'){
            printf("Enter two integers in format: a,b\n");
            
            scanf("%d,%d",&a,&b);
                result = b;
                for(int i = a; i>0; a--){
                    result += b;
                }
            printf("Result of multiplication of %d * %d = %d", a,b,result);
            exit();

        }
        if (ch == 'd' || ch == 'D'){
            printf("Enter two integers in format a,b - Where a is your numerator and b is the denominator\n");
            scanf("%d,%d",&a,&b);
                if(b==0){
                    printf("Division by zero is undefined");
                    exit();
                }
                for(int i = a; a>=b; i-b){
                    result++;
                }
                remainder = i;
                printf("Quotient is %d with remainder of %d");
                exit();

        }
        else{
            printf(" one of m,M,d,D was not entered, exiting.\n");
            return 0;
        }
        }

    