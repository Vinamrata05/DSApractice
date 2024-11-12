#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
struct Node {
    int row, col, value;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
struct Node* insertNode(struct Node* head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
    if (head == NULL) {
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Function to display the sparse matrix
void displayMatrix(struct Node* head, int rows, int cols) {
    struct Node* temp = head;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (temp != NULL && temp->row == i && temp->col == j) {
                printf("%d ", temp->value);
                temp = temp->next;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// Function to add two sparse matrices
struct Node* addMatrices(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->row < head2->row || 
           (head1->row == head2->row && head1->col < head2->col)) {
            result = insertNode(result, head1->row, head1->col, head1->value);
            head1 = head1->next;
        } else if (head2->row < head1->row || 
                  (head2->row == head1->row && head2->col < head1->col)) {
            result = insertNode(result, head2->row, head2->col, head2->value);
            head2 = head2->next;
        } else {
            int sum = head1->value + head2->value;
            if (sum != 0) {
                result = insertNode(result, head1->row, head1->col, sum);
            }
            head1 = head1->next;
            head2 = head2->next;
        }
    }

    // If any elements are left in either matrix
    while (head1 != NULL) {
        result = insertNode(result, head1->row, head1->col, head1->value);
        head1 = head1->next;
    }

    while (head2 != NULL) {
        result = insertNode(result, head2->row, head2->col, head2->value);
        head2 = head2->next;
    }

    return result;
}

// Driver function
int main() {
    struct Node* matrix1 = NULL;
    struct Node* matrix2 = NULL;

    // Example: Sparse Matrix 1 (3x3)
    matrix1 = insertNode(matrix1, 0, 0, 5);
    matrix1 = insertNode(matrix1, 1, 1, 8);
    matrix1 = insertNode(matrix1, 2, 2, 3);

    // Example: Sparse Matrix 2 (3x3)
    matrix2 = insertNode(matrix2, 0, 0, 2);
    matrix2 = insertNode(matrix2, 1, 2, 7);
    matrix2 = insertNode(matrix2, 2, 2, 4);

    // Display both matrices
    printf("Matrix 1:\n");
    displayMatrix(matrix1, 3, 3);
    printf("\nMatrix 2:\n");
    displayMatrix(matrix2, 3, 3);

    // Add the two matrices
    struct Node* resultMatrix = addMatrices(matrix1, matrix2);

    // Display the result
    printf("\nResultant Matrix:\n");
    displayMatrix(resultMatrix, 3, 3);

    return 0;
}

