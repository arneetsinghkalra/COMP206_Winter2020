/*
 * File contains a linked list that can be used to store a polynomial of arbitrary length.
 ************************************************************************
 * Author       Dept.              Date              History
 ************************************************************************
 * Arneet K     Software Eng      April 9, 2020      Initial Version
 * Arneet K     Software Eng      April 11, 2020     Final Version Done
*/ 
#include <stdio.h>
#include <stdlib.h>
#include "utils.h" 

int addPolyTerm(int coefficient, int exponent);
void displayPolynomial();
int evaluatePolynomial(int x);

typedef struct PolyTerm{
    int coeff;
    int expo;
    struct PolyTerm *next;
}PolyTerm;

PolyTerm * createATerm(int coeff, int exp); //Helper function to create a term
void addToList(PolyTerm *term);


//Create head node
PolyTerm *head = NULL;

int addPolyTerm(int coefficient, int exponent){
	
	//Create a pointer to a node with the data for the linked list
	PolyTerm * newTerm = createATerm(coefficient, exponent);

	//If there is a failure, return -1
	if (newTerm == NULL) {
		fprintf(stderr,"\n");
		exit (-1);
	}
	//Add term to linked list at correct place
	addToList(newTerm);
	return 0;
}

void displayPolynomial(){
	PolyTerm *temp = head; //Get a copy of the head
	if (temp == NULL) return; //Print nothing if empty list
	printf("%dx%d",temp->coeff,temp->expo); //Print the head as is
	temp = temp->next; //Traverse to the next node
	while(temp != NULL){
		//Print a plus if positive coeff
		if (temp->coeff >= 0) printf("+%dx%d",temp->coeff,temp->expo);
		//If negative, print as is
		if (temp->coeff < 0) printf("%dx%d",temp->coeff,temp->expo);
		//Traverse to next node
		temp = temp->next;
	}
	//Finally print a new line
	printf("\n");
}

int evaluatePolynomial(int x){
	PolyTerm *temp = head; //Get a copy of the head
	int answer = 0;

	while (temp!= NULL){
		answer += (temp->coeff * powi(x,temp->expo));
		temp = temp->next;
	}

	return answer;
}

//Helper function which creates a new polynomial term and returns pointer to the term
PolyTerm * createATerm(int coefficient, int exponent){
        PolyTerm *aTerm = (PolyTerm *) malloc(sizeof(PolyTerm));
	
	//In case of failure
	if (aTerm == NULL) return NULL;

	//Add information to term
        aTerm->coeff = coefficient;
        aTerm->expo = exponent;
        aTerm->next = NULL;

        return aTerm;
}

//Helper function to add a newly created node to the existing list
void addToList(PolyTerm *newTerm){
	//Set a duplicate of head
	PolyTerm *temp = head;

	//If it is an empty list then add the term as the head
	if (head == NULL){
		head = newTerm;
		return;
	}

	while(temp != NULL){

		//Traverse the list until it finds the right spot

		//Check to see if any manipulation needs to be done to beginning of list
		if (temp == head){
			if(temp->expo > newTerm->expo){
                        	newTerm->next = head;
                		head = newTerm;
				return;
			}
			if (temp->expo == newTerm->expo){
				head->coeff += newTerm->coeff;
				
				//Free space used by term as it is not needed
                  	    	free(newTerm);
                        	return;
			}
                }

		//Check if the next node is null
		if (temp->next == NULL){
			//Set last node to new node
			temp->next = newTerm;
			return;
		}

		//Then Check if next node is greater. If yes then place term as the next
		else if(temp->next->expo > newTerm->expo) {
			newTerm->next = temp->next; //Set terms next to the temps next
			temp->next = newTerm; //Set next of temp to the new term
			return;
		}
	
		//Then check if next node is greater. If yes then place term as the next
		else if(temp->next->expo == newTerm->expo){
			//Add coefficient of new term to coefficient of term in list
			temp->next->coeff += newTerm->coeff;

			//Free space used by term as it is not needed
			free(newTerm);
			return;
		}

		//Otherwise we can traverse to the next node in the list
		
		temp = temp->next;		
	}
}
