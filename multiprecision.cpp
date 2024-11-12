#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the front of a linked list
struct Node* insertAtFront(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// Function to add two numbers represented by linked lists
struct Node* addTwoNumbers(struct Node* first, struct Node* second) {
    struct Node* result = NULL;
    int carry = 0;

    // Traverse both lists
    while (first != NULL || second != NULL || carry != 0) {
        int sum = carry;
        
        if (first != NULL) {
            sum += first->data;
            first = first->next;
        }
        
        if (second != NULL) {
            sum += second->data;
            second = second->next;
        }

        // Update carry for the next position
        carry = sum / 10;

        // Insert the sum of current digits at the front of the result list
        result = insertAtFront(result, sum % 10);
    }

    return result;
}

// Function to create a linked list from a string
struct Node* createListFromString(char* str) {
    struct Node* head = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        head = insertAtFront(head, str[i] - '0');  // Convert character to integer
    }
    return head;
}


// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    char num1[100], num2[100];
    
    // Input two long integers as strings
    printf("Enter the first long integer: ");
    scanf("%s", num1);
    printf("Enter the second long integer: ");
    scanf("%s", num2);

    // Create linked lists from the input strings
    struct Node* first = createListFromString(num1);
    struct Node* second = createListFromString(num2);

    // Add the two numbers
    struct Node* result = addTwoNumbers(first, second);

    // Print the resultant sum
    printf("Sum: ");
    printList(result);

    return 0;
}

