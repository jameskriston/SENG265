#include <stdio.h>
#include <stdlib.h>
int rotate(int input[],int num);

int main(int argc, char *argv[]){
 int num = atoi(argv[1]);
 int array[] = {1,2,3,4,5,6,7,8,9};
rotate(array,num);
return 0;

}

int rotate(int input[], int num) {
    int size = size(input)-1;
    for(int i = 0; i<num; i++){

    int temp = input[size];
    for(int j = size; i>0; i--){
        input[j]=input[size-j];


    }
    input[0]=temp;
    }
for(int k = size; k>0; k--){
    printf("%d\n",input[k]);
}
return 0;
}