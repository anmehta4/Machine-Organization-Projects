////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Dclash.c
// This File:        cache2Dclash.c
// Other Files:      None
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
//////////////////////////// 80 columns wide //////////////////////////////////

#define ROWS 128
#define COLS 8
#define ITERATIONS 100
int arr2D[ROWS][COLS];

int main(){
	for(int iteration=1;iteration<=ITERATIONS;iteration++){
		for(int row=0;row<ROWS;row+=64){
			for(int col=0;col<COLS;col++){
				*(*(arr2D + row)+col) = iteration + row + col;
			}
		}
	}
	return 0;
}
