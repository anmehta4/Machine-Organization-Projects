////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Drows.c
// This File:        cache2Drows.c
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

#define ROWS 3000
#define COLS 500
int arr2D[ROWS][COLS];

int main(){
	for(int row=0;row<ROWS;row++){
		for(int col=0;col<COLS;col++){
			*(*(arr2D + row)+col) = row + col;
		}
	}
	return 0;
}
