#include <stdio.h>
#include <stdlib.h>

// Node structure to store each term of the polynomial
struct Node {
    int coeff;      // Coefficient
    int exp;        // Exponent
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new term into the polynomial in a sorted manner
struct Node* insertTermSorted(struct Node* head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (head == NULL || head->exp < exp) {
        newNode->next = head;
        return newNode;
    }

    struct Node* temp = head;
    while (temp->next != NULL && temp->next->exp >= exp) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

// Function to combine like terms in a polynomial
struct Node* combineLikeTerms(struct Node* head) {
    if (head == NULL) return NULL;

    struct Node* result = NULL;
    struct Node* temp = head;

    while (temp != NULL) {
        int coeffSum = temp->coeff;
        int exp = temp->exp;
        struct Node* next = temp->next;
        
        while (next != NULL && next->exp == exp) {
            coeffSum += next->coeff;
            next = next->next;
        }
        
        if (coeffSum != 0) {
            result = insertTermSorted(result, coeffSum, exp);
        }
        
        temp = next;
    }

    return result;
}

// Function to add two polynomials and simplify the result
struct Node* addAndSimplifyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp1 = poly1;
    struct Node* temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->exp > temp2->exp) {
            result = insertTermSorted(result, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            result = insertTermSorted(result, temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        } else {
            int sum = temp1->coeff + temp2->coeff;
            if (sum != 0) {
                result = insertTermSorted(result, sum, temp1->exp);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        result = insertTermSorted(result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        result = insertTermSorted(result, temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    }

    // Combine like terms in the result
    result = combineLikeTerms(result);

    return result;
}

// Function to display the polynomial
void displayPolynomial(struct Node* poly) {
    struct Node* temp = poly;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->exp);
        temp = temp->next;
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Main function
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;
    int n1, n2, coeff, exp;

    // Taking input for the first polynomial
    printf("Enter the number of terms in Polynomial A: ");
    scanf("%d", &n1);
    printf("Enter the terms for Polynomial A (coefficient and exponent):\n");
    for (int i = 0; i < n1; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        poly1 = insertTermSorted(poly1, coeff, exp);
    }
    poly1 = combineLikeTerms(poly1);

    // Taking input for the second polynomial
    printf("Enter the number of terms in Polynomial B: ");
    scanf("%d", &n2);
    printf("Enter the terms for Polynomial B (coefficient and exponent):\n");
    for (int i = 0; i < n2; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        poly2 = insertTermSorted(poly2, coeff, exp);
    }
    poly2 = combineLikeTerms(poly2);

    // Adding and simplifying the two polynomials
    result = addAndSimplifyPolynomials(poly1, poly2);

    // Displaying the polynomials
    printf("First Polynomial: ");
    displayPolynomial(poly1);
    printf("Second Polynomial: ");
    displayPolynomial(poly2);
    printf("Resultant Polynomial: ");
    displayPolynomial(result);

    return 0;
}

