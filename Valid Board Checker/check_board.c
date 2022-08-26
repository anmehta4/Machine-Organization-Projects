///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      board1.txt, board2.txt, board3.txt
// 		     board4.txt, board5.txt, board6.txt
// 		     board1solution.txt, board2solution.txt
// Semester:         CS 354 Spring 2021
//
// Author:           Arnav Mehta
// Email:            anmehta4@wisc.edu
// CS Login:         amehta
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
// Online sources:   None
//
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 */
void get_board_size(FILE *fptr, int *size) {      
    char *line1 = NULL;
    size_t len = 0;
    if ( getline(&line1, &len, fptr) == -1 ) {
        printf("Error reading the input file.\n");
        exit(1);
    }

    char *size_chars = NULL;
    size_chars = strtok(line1, DELIM);
    *size = atoi(size_chars);
}



/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {

	if(size<=0 || size>9){
		printf("Inavlid board size.");
		exit(1);
	}

	for(int x=0;x<size;x++){
		for(int y=0;y<size;y++){
			if(*(*(board+x)+y)<0 || *(*(board +x)+y)>size){
				printf("Value not in the range of 1-size");
				exit(1);
			}
		}
	}

	for(int i=0;i<size;i++){ // for loop to iterate through rows and cols
		for(int j=0;j<size;j++){ // for loop for row iteration
			for(int k=j+1;k<size;k++){ // for loop to compare each col value with col j
				if(*(*(board + i)+k) == *(*(board + i)+j) && *(*(board + i)+k)!=0) // checking for non zero equality
					return 0;
			}
		}

		for(int m=0;m<size;m++){ // for loop for col iteration
			for(int n=m+1;n<size;n++){ // for loop to compare each row value with row m
				if(*(*(board + m)+i) == *(*(board + n)+i) && *(*(board + m)+i)!=0) // checking for non zero equality
					return 0;
			}
		}
	}
	return 1;
}
  
 
   
/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * argc: CLA count
 * argv: CLA value
 */
int main( int argc, char *argv[] ) {              
     
    // TODO: Check if number of command-line arguments is correct.

	if(argc!=2){
		printf("Usage: ./check_board <input_filename> \n");
		exit(1);
	}
    // Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    // Declare local variables.
    int size;
    
    // TODO: Call get_board_size to read first line of file as the board size.
    get_board_size(fp, &size);

    // TODO: Dynamically allocate a 2D array for given board size.

    int **m = malloc(sizeof(int *)*size);
    if(m==NULL){
	    printf("Error! Memory has not been allocated");
	    exit(1);
    }

    for(int r=0;r<size;r++){
	    *(m+r) = malloc(sizeof(int)*size);
	    if(*(m+r)==NULL){
		    printf("Error! Memory has not been allocated");
		    exit(1);
	    }
    }

    // Read the rest of the file line by line.
    // Tokenize each line wrt the delimiter character 
    // and store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading line %i of the file.\n", i+2);
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            // TODO: Complete the line of code below
            // to initialize your 2D array.
            *(*(m+i)+j) = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }

    // TODO: Call the function valid_board and print the appropriate
    //       output depending on the function's return value.

    if(valid_board(m, size)==0)
	    printf("%s\n", "invalid");
    else
	    printf("%s\n", " valid");

    // TODO: Free all dynamically allocated memory.
    
    for(int i=0;i<size;i++){
	    free(*(m+i));
    }
    free(m);

    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       

// s21

