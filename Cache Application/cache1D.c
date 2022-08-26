////////////////////////////////////////////////////////////////////////////////
// Main File:        cache1D.c
// This File:        cache1D.c
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

#define ROWS 100000
int arr[ROWS];

int main(){
	for(int i=0;i<ROWS;i++){
		*(arr+i) = i;
	}
	return 0;
}

