/*
 * File with extra methods to parse the file, and to perform computation
 * of the polynomials. 
 ************************************************************************
 * Author       Dept.              Date              History
 ************************************************************************
 * Arneet K     Software Eng      April 9, 2020      Initial Version
 * Arneet K     Software Eng      April 11, 2020     Final Version
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Helper function to parse line retrived using fgets to store coeff and exp
//at address provided by integer pointers
void parse (char *input, int *num1, int *num2){
    sscanf(input,"%d %d",num1,num2);        
}

//Helper function to compute the exponent
//Used a recursive function
int powi(int x, int exponent) {
    int total = x;

    if (exponent == 0){
        return 1;
    }
    if (exponent == 1){
        return x;
    }

    else {
        return x*powi(x,exponent-1);
    }
}
