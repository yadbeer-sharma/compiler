//Importing the Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Global Variables Declaration
FILE *fp;
int BUFSIZE = 128;


//Driver code
int main(int argc, char *argv[]){

    char *filename;                                                 

    if(argc <= 2){
        printf("Too less arguments! Please provide buffer size and filename\n");
        exit(0);
    }
    else if(argc == 3){
        BUFSIZE = atoi(argv[1]);
        filename = (char *) malloc(strlen(argv[2]));
        strcpy(filename, argv[2]);
    }
    else{
        printf("Too many arguments!\n");
        exit(0);
    }

    fp = fopen(filename, "r");
    
    if(fp == NULL){
        printf("File does not exist\n");
        exit(0);
    }

}
    



