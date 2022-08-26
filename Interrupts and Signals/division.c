////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
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

int MAX = 100; // max buffer as stated in question
int count_divisions = 0; // counter for number of divisions

/* Method to handle the SIGINT signal
 * exits the code
 */
void handler_SIGINT(){ // handler method for SIGINT
	printf("%s%i%s", "\nTotal number of operations completed successfully: ",count_divisions-1,"\n"); // print desired messages
        printf("The program will be terminated.\n");
	exit(1); //terminate the program 
}

/* Method to hangle the SIGFPE signal
 * prints the necessary statements
 * exits the code
 */
void handler_SIGFPE(){ //handler method for SIGFPE
        printf("Error: a division by 0 operation was attempted.\n"); // print desired messages
	printf("%s%i%s", "Total number of operations completed successfully: ",count_divisions-1,"\n");
	printf("The program will be terminated.\n");
	exit(1); // terminate the program
}

int main(){
	
	struct sigaction sa; //initialize sigaction struct
        memset (&sa, 0, sizeof(sa));
        sa.sa_handler = handler_SIGFPE;
        if(sigaction(SIGFPE,&sa, NULL)!=0){// assign appropriate handler
                printf("Error binding SIGFPE handler.\n");
                exit(1);
        }

	struct sigaction sa1; // initialize sigaction struct
        memset (&sa1, 0, sizeof(sa1));
        sa1.sa_handler = handler_SIGINT;
        if(sigaction(SIGINT,&sa1, NULL)!=0){// assign appropriate handler
                printf("Error binding SIGINT handler.\n");
                exit(1);
        }


	while(1){ //infinite loop
		count_divisions = count_divisions + 1;//updating counter
		char buf[MAX];
	
		printf("Enter first integer: "); //obtaining the first integer
		if(fgets(buf,MAX,stdin)==NULL){
			printf("Error while reading input");
			exit(1);
		}
		int num1 = atoi(buf); // converting the string to an int
	
		printf("Enter second integer: "); // obtaining the second integer
		if(fgets(buf,MAX,stdin)==NULL){
			printf("Error while reading input");
		}
		int num2 = atoi(buf); // converting the string to an int
		
		int quotient = num1 / num2; // obtaining the quotient
		int remainder = num1 % num2; // obtaining the remainder

		printf("%i%s%i%s%i%s%i%s",num1,"/",num2," is ",quotient," with a remainder of ",remainder,"\n"); // printing the result
	}
}

