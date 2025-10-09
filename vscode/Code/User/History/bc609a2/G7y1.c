#include <stdio.h>
#include <stdlib.h>
int rotate(int input[],int arraysize, int num);

int main(int argc, char *argv[]){
 int num = atoi(argv[1]);
 if(atoi(argv[1])<=0 || argc!=2){
    printf("You didn't properly enter an argument");
    exit(0);
 }

 int array[] = {1,2,3,4,5,6,7,8,9};
 int size = sizeof(array)/sizeof(array[0]);
 printf("%d\n",size);
 printf("Input array is ");
 for(int x=0; x<size; x++){
    printf("%d ",array[x]);
 }
 printf("\n");
rotate(array,size,num);


    return 0;
}



int rotate(int input[], int arraysize, int num) {
    int size = arraysize;
    for(int i = 0; i<num; i++){
   int temp = input[0];
    for(int j = 0; i<size; i++){
        
    }
    printf("Rotated array is : ");
    for(int k = 0; k<size; k++){
        printf("%d ",input[k]);
    }
}
   return 0;
}