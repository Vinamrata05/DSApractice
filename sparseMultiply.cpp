#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node into the doubly linked list
void insertNode(struct Node** head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
    
    // If the list is empty, insert the node at the beginning
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        
        // Traverse to find the correct position (row and col) or combine if same
        while (current != NULL) {
            if (current->row == row && current->col == col) {
                current->value += value; // Combine if same position
                free(newNode);
                return;
            } else if (current->row > row || (current->row == row && current->col > col)) {
                break;
            }
            current = current->next;
        }
        
        if (current == *head) {
            // Insert at the beginning
            newNode->next = *head;
            (*head)->prev = newNode;
            *head = newNode;
        } else if (current == NULL) {
            // Insert at the end
            struct Node* last = *head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newNode;
            newNode->prev = last;
        } else {
            // Insert in between
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev != NULL) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
        }
    }
}

// Function to multiply two sparse matrices
struct Node* multiplySparseMatrices(struct Node* mat1, struct Node* mat2, int n) {
    struct Node* result = NULL;
    struct Node* ptr1 = mat1;

    // Traverse through each non-zero element of the first matrix
    while (ptr1 != NULL) {
        struct Node* ptr2 = mat2;

        // For each element in mat1, find corresponding elements in mat2
        while (ptr2 != NULL) {
            if (ptr1->col == ptr2->row) {
                int row = ptr1->row;
                int col = ptr2->col;
                int value = ptr1->value * ptr2->value;
                insertNode(&result, row, col, value);
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

    return result;
}

// Function to print the sparse matrix
void printSparseMatrix(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("Row: %d, Col: %d, Value: %d\n", current->row, current->col, current->value);
        current = current->next;
    }
}

int main() {
    // Example matrices represented using doubly linked lists
    // First matrix (3x3) - Sparse Matrix 1
    struct Node* mat1 = NULL;
    insertNode(&mat1, 0, 0, 1);
    insertNode(&mat1, 0, 2, 2);
    insertNode(&mat1, 1, 1, 3);
    insertNode(&mat1, 2, 0, 4);
    insertNode(&mat1, 2, 2, 5);

    // Second matrix (3x3) - Sparse Matrix 2
    struct Node* mat2 = NULL;
    insertNode(&mat2, 0, 0, 6);
    insertNode(&mat2, 0, 1, 7);
    insertNode(&mat2, 1, 1, 8);
    insertNode(&mat2, 2, 0, 9);
    insertNode(&mat2, 2, 2, 10);

    printf("Matrix 1:\n");
    printSparseMatrix(mat1);

    printf("\nMatrix 2:\n");
    printSparseMatrix(mat2);

    // Multiply the two sparse matrices
    struct Node* result = multiplySparseMatrices(mat1, mat2, 3);

    printf("\nResultant Matrix:\n");
    printSparseMatrix(result);

    return 0;
}

