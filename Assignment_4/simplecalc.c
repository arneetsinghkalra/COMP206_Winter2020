/*
 * Program to implement a simple calculator.
 ************************************************************************
 * Author       Dept.              Date               Notes
 ************************************************************************
 * Arneet K     Software Eng      Feb 17, 2020       Initial Version
 * Arneet K	Software Eng 	  Feb 18, 2020       Final Version
*/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	

	 //Check if number of arguments passed aren't exactly 4 including program name
        if (argc != 4) {
                printf("Error: usage is simplecalc <x> <op> <y>\n");
                return 1;
        }	
	
	//Store first parameter as int
	int a = atoi(argv[1]);
	
	//Store second  parameter as char
	char *operator = argv[2];	

	//Store third parameter as int
	int b = atoi(argv[3]);
		
	int result;	


	switch (*operator) {
		case '+': 
			result = a+b;
			printf("%d\n",result);
			return 0;
			break;
		case '-': 
			result = a-b;
			printf("%d\n",result);
			return 0;
			break;
		case '*': 
			result = a*b;
		 	printf("%d\n",result);	
			return 0;
			break;
		case '/': 
			result = a/b;
			printf("%d\n",result);
			return 0;
			break;
		default:
			printf("%s is not a valid operator\n",operator);
			return 2;
			break;
	
	}
}

