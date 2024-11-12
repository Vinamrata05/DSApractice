#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* createnode(int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

int findmax(struct node* head) {
    int max = head->data;
    while (head != NULL) {
        if (head->data > max)
            max = head->data;
        head = head->next;
    }
    return max;
}

int getDigit(int number, int digitPlace) {
    return (number / digitPlace) % 10;
}
void insert(struct node** head, struct node* newnode) {
    if (*head == NULL) {
        *head = newnode;
    } else {
        struct node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

struct node* countingSort(struct node* head, int digitPlace) {
    struct node* buckets[10] = {NULL};

    struct node* current = head;
    while (current != NULL) {
        int digit = getDigit(current->data, digitPlace);
        struct node* nextnode = current->next;
        current->next = NULL;
        insert(&buckets[digit], current);
        current = nextnode;
    }

    struct node* newhead = NULL;
    struct node* tail = NULL;
    for (int i = 0; i < 10; i++) {
        if (buckets[i] != NULL) {
            if (newhead == NULL) {
                newhead = buckets[i];
            } else {
                tail->next = buckets[i];
            }

            tail = buckets[i];
            while (tail->next != NULL) {
                tail = tail->next;
            }
        }
    }
    return newhead;
}

void radixSort(struct node** head) {
    int max = findmax(*head);
    int digitPlace = 1;

    while (max / digitPlace > 0) {
        *head = countingSort(*head, digitPlace);
        digitPlace *= 10;
    }
}

void printList(struct node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct node* head = createnode(136);
    insert(&head, createnode(48));
    insert(&head, createnode(358));
    insert(&head, createnode(46));
    insert(&head, createnode(70));
    insert(&head, createnode(247));
    insert(&head, createnode(205));
    insert(&head, createnode(609));

    printf("Original List:\n");
    printList(head);

    radixSort(&head); 

    printf("\nSorted List:\n");
    printList(head);

    return 0;
}
