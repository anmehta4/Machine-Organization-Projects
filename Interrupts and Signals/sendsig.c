////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
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
//
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc,char *argv[]){
	char sigusr1[] = "-u"; // default signals to compare to
	char sigint[] = "-i";
	if(argc != 3){ // if argc is not the desired value
		printf("Usage: sendsig <signal type> <pid>\n"); // print error message
		exit(1);// terminate 
	}

	if(strcmp(argv[1],sigusr1) == 0){ // checking if argv[1] is -u
		if(kill(atoi(argv[2]),SIGUSR1) != 0){
			printf("Error in kill command"); // sending appropriate signal
			exit(1);
		}
	}
	else if (strcmp(argv[1],sigint) == 0){ // checking if arvv[1] is -i
		if(kill(atoi(argv[2]),SIGINT) != 0){
			printf("Error in kill command"); // sending appropriate signal
		        exit(1);
		}	
	}
}


