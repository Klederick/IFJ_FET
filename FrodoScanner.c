// Documentation
/**                     
 * file: sum.c
 * author: you
 * description: program to find sum.
 */
  
// Link
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
    FILE *file;
    char* filename = "test.txt";
    file = fopen(filename,"r+");
    char input[3][SHRT_MAX];  // Pointer to store the input string
    int current = 0;

    int ch;
    fscanf(file,"%s",input[current]);
    if(input[current] == NULL){
        fprintf(stderr,"File is empty or incorrect.\n");
        return -1;
    }
    // Read characters from stdin until EOF is encountered
    while(input[current] != NULL){
      printf("Doing %d: %s\n",current,input[current]);
    current++;
    fscanf(file,"%s",input[current]);
    }

    fclose(file);
    return 0;
}





