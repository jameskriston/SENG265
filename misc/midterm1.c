#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

char source[100]="I am in Seng265";

char buffer[100];

strcpy(buffer,source);

    int size = strlen(source);
    int num = 0;
// A E I O U Y
        for(int i = 0; i<size; i++){
            int flag = 1;
            if((source[i] == 'A') || (source[i] == 'E') || (source[i] == 'I') || (source[i] == 'O') || (source[i] == 'U') || (source[i] == 'Y')
            || (source[i]=='a') || (source[i]=='e') || (source[i]=='i') || (source[i]=='o') || (source[i]=='u') || (source[i]=='y')){
                flag = 0;

            }
            if(flag==1){

                buffer[num]=source[i];
                num++;
            }

        }
        buffer[num]='\0';
        int k;
for(k = 0; k<num;k++){

    source[k]=buffer[k];
}
source[k]='\0';
printf("%s\n",source);

char* str2 = "abcd12312312";
printf("sizeof=%02d \n", sizeof(str2));
return 0;
}