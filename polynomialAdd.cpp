#include <stdio.h>
#include <stdlib.h>

// Node structure to store each term of the polynomial
struct Node {
    int coeff;      // Coefficient
    int exp;        // Exponent
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
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

    if (temp->exp == exp) {
        temp->coeff += coeff; // Add the coefficients if exponents are the same
        free(newNode);        // No need to add a new node
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }

    return head;
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
    struct Node* polynomial = NULL;
    int n1, n2, coeff, exp;

    // Taking input for the first polynomial
    printf("Enter the number of terms in Polynomial A: ");
    scanf("%d", &n1);
    printf("Enter the terms for Polynomial A (coefficient and exponent):\n");
    for (int i = 0; i < n1; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        polynomial = insertTermSorted(polynomial, coeff, exp);
    }

    // Taking input for the second polynomial and adding directly to the existing list
    printf("Enter the number of terms in Polynomial B: ");
    scanf("%d", &n2);
    printf("Enter the terms for Polynomial B (coefficient and exponent):\n");
    for (int i = 0; i < n2; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        polynomial = insertTermSorted(polynomial, coeff, exp);
    }

    // Displaying the resultant polynomial
    printf("Resultant Polynomial: ");
    displayPolynomial(polynomial);

    return 0;
}

