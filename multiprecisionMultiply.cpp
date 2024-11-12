#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int digit;           
    struct Node *next;   
} Node;

Node* createNode(int digit) {
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

Node* initList(const char *number) {
    Node *head = NULL;

   
    for (int i = 0; number[i] != '\0'; i++) {
        int digit = number[i] - '0'; // Convert character to integer
        Node *newNode = createNode(digit);
        
       
        newNode->next = head;
        head = newNode; 
    }

    return head;
}
void appendNode(Node** head, int digit) {
    Node* newNode = createNode(digit);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d", current->digit);
        current = current->next;
    }
    printf("\n");
}


Node* reverseList(Node *head) {
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;   
        current->next = prev;   
        prev = current;         
        current = next;         
    }

    return prev; 
}


Node* addLists(Node *l1, Node *l2) {
    Node *result = NULL, *tail = NULL;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->digit;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->digit;
            l2 = l2->next;
        }
        carry = sum / 10;
        sum = sum % 10;

        Node *newNode = createNode(sum);
        if (result == NULL) {
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return result;
}
Node* multiply(Node* num1, Node* num2) {
    if (!num1 || !num2) {
        return NULL;
    }

    Node* result = NULL;  // To store the final result
    Node* num2_ptr = num2;
    Node* tempResult = NULL;  // To store intermediate results
    int shift = 0;

    // Outer loop: For each digit in num1
    while (num1 != NULL) {
        Node* num2_ptr = num2;
        tempResult = NULL;

        // Add zeros for the current position shift (like multiplying by 10, 100, etc.)
        for (int i = 0; i < shift; i++) {
            appendNode(&tempResult, 0);
        }

        int carry = 0;
        // Inner loop: For each digit in num2
        while (num2_ptr != NULL) {
            int product = num1->digit * num2_ptr->digit + carry;
            carry = product / 10;
            product = product % 10;

            appendNode(&tempResult, product);
            num2_ptr = num2_ptr->next;
        }

        // If there's any carry left after the inner loop, add it as a new node
        if (carry > 0) {
            appendNode(&tempResult, carry);
        }

        // Add intermediate product to the final result
        result = addLists(result, tempResult);

        // Move to the next digit in num1
        num1 = num1->next;
        shift++;  // Increase shift for next position
    }

    return result;
}

void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *num1 = initList("12");
    Node *num2 = initList("5");
    
    printf("Number 1: ");
    printList(num1);
    printf("Number 2: ");
    printList(num2);
    
    Node *sum = addLists(num1, num2);
    printf("Sum: ");
    Node *correctordersum=reverseList(sum);
    printList(correctordersum);
    printf("mul");
    Node* mul=multiply(num1,num2);
     Node *correctordermul=reverseList(mul);
    printList(correctordermul);
    freeList(num1);
    freeList(num2);
    freeList(sum);

    return 0;
}
