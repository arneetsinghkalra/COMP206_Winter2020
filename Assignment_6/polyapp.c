/*
 * Main file which will recieve a textfile as input. Program is invoked in
 * this file. 
 ************************************************************************
 * Author       Dept.              Date              History
 ************************************************************************
 * Arneet K     Software Eng      April 9, 2020      Initial Version
 * Arneet K     Software Eng      April 11, 2020     Final Done
*/ 

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "poly.h"

char array[100];

int main(int argc, char *argv[]) {

    int coeff, exp;

    //Verify argument is provided
    if (argc != 2) {
        fprintf(stderr,"Error: Input File Name\n");
        exit(-1);
    }

    //Check if file does not  exist
    FILE *readFile = fopen(argv[1], "r");
    if (readFile == NULL) {
	fprintf(stderr,"Error, unable to locate the data file %s\n",argv[1]);
	exit(100);
    }
    
    //Traverse through each line of file
    fgets(array,99,readFile);
    while(!feof(readFile)){
	//Parse through each line and store numbers
	parse(array,&coeff,&exp);
	
	//In the added case of an error, exit
	if (addPolyTerm(coeff,exp) == -1){
		fprintf(stderr,"Error: Out of Memory\n");
		exit(-500);
	}
	//Get next line
	fgets(array,99,readFile);
    }
    //Finally display the final polymonial, and evalute for all require cases
    displayPolynomial();
    printf("for x=-2, y=%d\n",evaluatePolynomial(-2));
    printf("for x=-1, y=%d\n",evaluatePolynomial(-1));
    printf("for x=0, y=%d\n",evaluatePolynomial(0));
    printf("for x=1, y=%d\n",evaluatePolynomial(1));
    printf("for x=2, y=%d\n",evaluatePolynomial(2));
}
