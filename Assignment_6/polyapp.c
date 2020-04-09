/*
 * Main file which will recieve a textfile as input. Program is invoked in
 * this file. 
 ************************************************************************
 * Author       Dept.              Date              History
 ************************************************************************
 * Arneet K     Software Eng      April 9, 2020      Initial Version
*/ 

#include <stdio.h>

int main(int argc, char *argv[]) {

    //Verify argument is provided
    if (argc < 1) {
        fprintf(stderr,"Error: Input File Name\n");
        exit(-1);
    }
}