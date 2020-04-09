/*
 * File contains a linked list that can be used to store a polynomial of arbitrary length.
 ************************************************************************
 * Author       Dept.              Date              History
 ************************************************************************
 * Arneet K     Software Eng      April 9, 2020      Initial Version
*/ 
#include <stdio.h>

int addPolyTerm(int coefficient, int exponent);
void displayPolynomial();
int evaluatePolynomial(int x);

struct PolyTerm{
    int coeff;
    int expo;
    struct PolyTerm *next;
};

int main() { 
    printf("Hello World");
}

