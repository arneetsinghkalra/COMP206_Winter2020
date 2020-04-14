//Definition of node in linked list
typedef struct PolyTerm{
    int coeff;
    int exp;
    struct PolyTerm *next;
}term;

//Create head node
extern term *head;

//Functions
int addPolyTerm(int coefficient, int exponent);
void displayPolynomial();
int evaluatePolynomial(int x);
