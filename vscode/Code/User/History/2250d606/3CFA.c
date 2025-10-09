#include <stdlib.h>
#include <stdio.h>




    int main(){
    int a = 0;
    int b = 0;
    int result = 0;
    int remainder = 0;   

    printf("Enter M for multiplication or D for division\n");
    
        char ch = getchar();
        if(ch =='m' || ch =='M'){
            printf("Enter two integers in format: a,b\n");
            
            scanf("%d,%d",&a,&b);
                result = b;
                for(int i = a; i>0; i--){
                    result += b;
                }
            printf("Result of multiplication of %d * %d = %d", a,b,result);
            exit(0);

        }
        if (ch == 'd' || ch == 'D'){
            printf("Enter two integers in format a,b - Where a is your numerator and b is the denominator\n");
            scanf("%d,%d",&a,&b);
                if(b==0){
                    printf("Division by zero is undefined");
                    exit(0);
                }
                int i = a;
                    while(i>=b){
                    result++;
                    i = i-b;    
                }
                remainder = i;
                printf("Quotient is %d with remainder of %d",result,remainder);
                exit(0);

        }
        else{
            printf(" one of m,M,d,D was not entered, exiting.\n");
            exit(0);
        }
        }

    