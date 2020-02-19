/*
 * Program to implement a basic version of Caesar's cipher. The objective is 
 * to replace each letter in the alphabet with another letter that is 'X'
 * offset away from it in order to scramble the message. 
 ************************************************************************
 * Author       Dept.              Date              History
 ************************************************************************
 * Arneet K     Software Eng      Feb 16, 2020       Initial Version
 * Arneet K	Software Eng 	  Feb 17, 2020       Capture input implemented
 * Arneet K     Software Eng      Feb 18, 2020       Final Version
*/ 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	//Temp vaiable used for later
	int wrapchar;

	//Verify offset argument is passed
	if (argc != 2) {
		printf("Error: usage is caesarcipher <offset>\n");
		return 1;
	}
	
	//Get offset value
	int offset = atoi(argv[1]);

	//Get original char input
	int input = getchar();
	
	//Work while not end of file
	while(input != EOF){	
		//Char is between a-z
		if (input >= 97 && input <= 122){
			//Check if input + offset is a-z with offset
			if (input + offset < 122 && input + offset > 97){
				putchar(input + offset); //Print just offset and input
			}
			//Need to wrap around
			else { 
				//Set wrapchar initially
				wrapchar = input + offset;
				
				//Reduced by 26 if offset increases over z
				while (wrapchar >= 123) {
					wrapchar = input + offset - 26;
				}
				
				//Increase by 26 if offset decreases below a
				while (wrapchar <= 96) {
					wrapchar = input + offset + 26;
				}
				
				putchar (wrapchar); 
			}
		}
		
		//Input not between a-z, just print original
		else {
			putchar(input);
		}

		//Get next character
		input = getchar();
    }
}
