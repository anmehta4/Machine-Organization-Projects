////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      sendsig.c
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
int number_of_seconds = 3;// interval for the alarm
int count_sig_sur1 = 0; // counter for number of SIGSUR1 signals handled

void handler_SIGALRM(){ //handler method for SIGALRM
        time_t curtime; // to obtain time in desired format
        time(&curtime);
	if (time(&curtime) == (time_t)-1){
		printf("Error in obtaining time");
		exit(1);
	}
	if(ctime(&curtime) == NULL){
		printf("Error in obtaining time");
		exit(1);
	}
        printf("%s%d%s%s", "PID: ",getpid()," CURRENT TIME: ",ctime(&curtime));
        alarm(number_of_seconds); // re-arm the alarm to go off in 3 seconds
        return;
}

void handler_SIGINT(){
	printf("\nSIGINT handled.\n"); // printing desired messages
	printf("%s%i%s", "SIGSUR1 was handled ",count_sig_sur1, " times. Exiting now.\n");
	exit(1); // terminate the code
}

void handler_SIGUSR1(){
	count_sig_sur1 = count_sig_sur1 + 1; // updating the counter
	printf("SIGUSR1 handled and counted!\n"); // printing desired messages
}

int main(){
	printf("PID and time print every 3 seconds\n"); // printing the desired messages
        printf("Type CTRL-C to end the program. \n");	
	alarm(number_of_seconds); // sending the first alarm signal 
	struct sigaction sa; // initilaizing the handler for SIGALRM
	memset (&sa, 0, sizeof(sa));
        sa.sa_handler = handler_SIGALRM;

	if(sigaction(SIGALRM,&sa, NULL)!=0){ // ensure handler has been assigned 
		printf("Error binding SIGALRM handler.\n");
		exit(1);
	}

	struct sigaction sa1; // initializing the handler for SIGINT
        memset (&sa1, 0, sizeof(sa1));
        sa1.sa_handler = handler_SIGINT;

	if(sigaction(SIGINT,&sa1, NULL)!=0){ // ensure handler has been assigned 
		printf("Error binding SIGINT handler.\n");
		exit(1);
	}

	struct sigaction sa2; // initializing the handler for SIGSUR1
        memset (&sa2, 0, sizeof(sa2));
        sa2.sa_handler = handler_SIGUSR1;

        if(sigaction(SIGUSR1,&sa2, NULL)!=0){ // ensure handler has been assigned
                printf("Error binding SIGUSR1 handler.\n");
                exit(1);
        }


	while(1){
	}
}




