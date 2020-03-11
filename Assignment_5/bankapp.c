/*
 * Program to implement a simple banking application. There are 3 capabilities.
 * You can add an account number, make a deposit, and make a withdrawal.
 * Data is stored in a CSV file: bankdata.csv 
 ************************************************************************
 * Author       Dept.              Date              History
 ************************************************************************
 * Arneet K     Software Eng      March 5, 2020       Initial Version
 * Arneet K     Software Eng      March 10, 2020      Balance Check Left to Do
 * Arneet K     Software Eng      March 11, 2020      Completed Assignment
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int addAccount(char *acctNum, char *name, FILE *appendFile, FILE *readFile);
int deposit(char *acctNum, char *date, char *amount, FILE *appendFile, FILE *readFile);
int withdraw(char *acctNum, char *date, char *amount, FILE *appendFile, FILE *readFile);
int i = 0; //Counter Variable
int isInteger(char *s);
int isDate(char *s);
char array[100];
char c = 0;
char *transaction;
float transactionFloat;
char *lastComma;
float balance;

int main(int argc, char *argv[]){ 
        char *arg1 = argv[1];
        char *acctNum = argv[2];
	char *name = argv[3];
	char *date = argv[3];
	char *amount = argv [4];

	//No file exists
	FILE *readFile = fopen("bankdata.csv", "r");
        if (readFile == NULL) {
                fprintf(stderr,"Error, unable to locate the data file bankdata.csv\n");
                exit(100);
        }       
        fclose(readFile);

	//No arguments passed OR not -a,-d,-w	
	if ( argc == 1 ||  (strcmp(arg1,"-a") != 0 && strcmp(arg1,"-d") != 0 && strcmp(arg1,"-w") != 0)) {
		fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
		exit(1);
	}

	//**************************** "-a" is first argument
        if (strcmp(arg1,"-a")==0) {
                //Not enough arguments OR acctnum is not integers OR 
                if (argc < 4 || isInteger(acctNum) != 1) {
                        fprintf(stderr,"Error, incorrect usage!\n-a ACCTNUM NAME\n");
                exit(1);
                }
  		
		FILE *appendFile = fopen("bankdata.csv", "a");
        	FILE *readFile = fopen("bankdata.csv", "r");
		addAccount(acctNum, name, appendFile, readFile);
		fclose(appendFile);		
		fclose(readFile);
        }

        //**************************** "-d" is first argument
        if (strcmp(arg1,"-d")==0) {
                if (argc < 5 || isDate(date) != 1) {
                        fprintf(stderr,"Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n");
                exit(1);
                }
		
		FILE *appendFile = fopen("bankdata.csv", "a");
                FILE *readFile = fopen("bankdata.csv", "r");
		
		deposit(acctNum, date, amount, appendFile, readFile);
		
		fclose(appendFile);
                fclose(readFile);
	}


        //**************************** "-w" is first argument
        if (strcmp(arg1,"-w")==0) {
                if (argc < 5 || isDate(date) != 1) {
                        fprintf(stderr,"Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n");
                exit(1);
                }
        
	
		FILE *appendFile = fopen("bankdata.csv", "a");
                FILE *readFile = fopen("bankdata.csv", "r");

                withdraw(acctNum, date, amount, appendFile, readFile);

                fclose(appendFile);
                fclose(readFile);
	
	}
}

int isInteger(char *s) {
        while (*s) {
                if (isdigit(*s++) == 0)
                return 0;
        }
    return 1;
}

int isDate(char *s) {
	for (i = 0; i <= 3; i++) {
		if (s[i] < '0' || s[i] > '9') return 0; //Not a number
	}

	if (s[4] != '-' && s[7] != '-') return 0;
	
	for (i = 5; i <= 6; i++) {
                if (s[i] < '0' || s[i] > '9') return 0; //Not a number
        }
	
	for (i = 8; i <= 9; i++) {
                if (s[i] < '0' || s[i] > '9') return 0; //Not a number
        }


	return 1; //Otherwise it is a valid date
}

int addAccount(char *acctNum, char *name, FILE *appendFile, FILE *readFile) {
	//Check if AC acctnum already exists
	fgets(array,99,readFile);
	while(!feof(readFile)) {
		if (strstr(array,"AC,") != 0) { //Search in the rows that are AC rows
			if(strstr(array,acctNum) != 0){//Search if account nummber is present
				fprintf(stderr,"Error, account number %s already exists\n",acctNum);
				exit(50);
			}
		}	
		fgets(array,99,readFile);
	}	
	//AC does not exist, can create it 		
	fprintf(appendFile,"AC,%s,%s\n", acctNum,name);
	return 0;
}

int deposit(char *acctNum, char *date, char *amount, FILE *appendFile, FILE *readFile){
	//Check if AC acctnum already exists
        fgets(array,99,readFile);
	while(!feof(readFile)) {
                if (strstr(array,"AC,") != 0) { //Search in the rows that are AC rows
                        if(strstr(array,acctNum) != 0){ //Search if account number is present
                 		//Exists so add in transaction               
				fprintf(appendFile,"TX,%s,%s,%s\n", acctNum,date,amount);
			        return 0;
                        }
                }
		fgets(array,99,readFile);
        }
	//TX does not exist Error              
        fprintf(stderr,"Error, account number %s does not exists\n",acctNum);
        exit(50);
}

int withdraw(char *acctNum, char *date, char *amount, FILE *appendFile, FILE *readFile) {
	//Reset transaction value to 0
	transaction = 0;
	
	fgets(array,99,readFile);
	while(!feof(readFile)){	
		if (strstr(array,"TX,") != 0) { //Search only in the TX rows- can't withdraw w/o deposit
                        if(strstr(array,acctNum) != 0){ //If account nummber is present
                                //Exists so add in transaction               
                	        lastComma = strstr(array,"-"); //Detect the hyphen in the date value
				transaction = lastComma + 7; //Add 7 to get Amount
				transactionFloat = atof(transaction); //Convert to a float
				balance += transactionFloat;//Add transaction to balance
                        	//printf("The balance is %.2f inside the loop\n",balance);
			}
                }
		//Verify if AC exists
		if (strstr(array,"AC,") != 0) { //Search in the rows that are AC rows
                        if(strstr(array,acctNum) != 0){ //Search if account number is present
				transactionFloat = -1; //Flag AC exists but no deposits
			}
		}
		fgets(array,99,readFile);
        }

	//Account exists
        if (transactionFloat != 0) {
		//Withdrawal wont reduce funds below $0
		if ((balance - atof(amount)) >= 0) {
			//printf("Sum with transaction is %.2f\n",balance-atof(amount));
			fprintf(appendFile,"TX,%s,%s,-%s\n", acctNum,date,amount);
			return 0;
		}
		//Not enough funds in the account
		else {
			fprintf(stderr,"Error, account number %s has only %.2f\n",acctNum,balance);
			exit(60);

		}
	}
	else {
		//TX does not exist Error              
        	fprintf(stderr,"Error, account number %s does not exists\n",acctNum);
        	exit(50);
	}
}
