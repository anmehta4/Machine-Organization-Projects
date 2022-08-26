////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      myMagicSquare*
// Semester:         CS 354 Spring 2021
// Instructor:       deppeler
// 
// Author:           Arnav Mehta
// Email:            anmehta4@wisc.edu
// CS Login:         amehta
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
// Online sources:   None
//
//////////////////////////// 80 columns wide //////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
	int num; 
       	printf("Enter magic square's size (odd integer >=3) \n");	
	scanf("%d",&num); //obtaining the value entered
	return num;
} 
   
/* TODO:
 * Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {

	MagicSquare *msptr = malloc(sizeof(MagicSquare)); // allocate memory
	(*msptr).size = n;
	if(msptr==NULL){
		printf("Memory has not been allocated! \n");
		exit(1);
	}

	int **m;
	m = malloc(sizeof(int *)*n); // allocating memory of 2D array
	if(m==NULL){
		printf("Memory has not been allocated \n");
		exit(1);
	}

	for(int r=0;r<n;r++){
		*(m+r) = malloc(sizeof(int)*n);
		if(*(m+r)==NULL){
			printf("Memory has not been allocated! \n");
			exit(1);
		}
	}

	for(int x=0;x<n;x++)
		for(int y=0;y<n;y++)
			*(*(m+x)+y)=0;
	int i = 0;
        int j = n / 2;

    for (int num = 1; num <= n * n;) { // following Siamese Algorithm
      if (i < 0 && j > n - 1) {
        i = i + 2;
        j = n - 1;
        continue;
      }
      if (j > n - 1) {
        j = 0;
        continue;
      }
      if (i < 0) {
        i = n - 1;
        continue;
      }
      if (*(*(m+i)+j)!= 0) {
        i = i + 2;
        j--;
        continue;
      }
      *(*(m+i)+j) = num++;
      i--;
      j++;

    }
	(*msptr).magic_square = m; // storing the array in the struct variable
	
	return msptr;	
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
	
       FILE *fp;
       fp = fopen(filename, "w"); // open the file
       if(fp==NULL){
	       fprintf(stderr, " Error while opening file.\n");
       }

       for(int i=0;i<magic_square->size;i++){ // outer loop for rows
			for(int j=0;j<magic_square->size;j++){ // inner loop for columns
				if(j==magic_square->size-1) // no comma after last digit of the row
					fprintf(fp,"%d",*(*((magic_square->magic_square)+i)+j));
				else{
					fprintf(fp,"%d%c",*(*((magic_square->magic_square)+i)+j),',');
				}
			}
			fprintf(fp,"%s","\n");//print new line after every row
		}
       if(fclose(fp)!=0){ // close the opened file
	       printf("Error while closing the file \n");
	       exit(1);
       }

}


/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // TODO: Check input arguments to get output filename
    
    if(argc!=2){ // checks arg count
	printf("Usage: ./myMagicSquare <output_filename> \n");
	exit(1);
    }

    char *filename = argv[1]; // taking the argument and storing the filename
    if(filename==NULL){ // if file is NULL
	   printf("Usage: ./myMagicSquare <outputfile> \n");
	   exit(1);
    }
    // TODO: Get magin square's size from user
    int size = getSize();
    if(size%2==0){ // if size is even
	    printf("Magic square size must be odd. \n");
	    exit(1);
    }else if(size<3){ // if size is <3
	    printf("Magic square size must be >= 3. \n");
	    exit(1);
    }
    // TODO: Generate the magic square
    MagicSquare *msptr = generateMagicSquare(size);
    // TODO: Output the magic square
    fileOutputMagicSquare(msptr, filename);
    
    for(int i=0;i<size;i++) // free the heap allocated memory
   	 free(msptr->magic_square[i]);
    free(msptr->magic_square);
    free(msptr);

    return 0;
} 






                                                         
//		s21		myMagicSquare.c      

