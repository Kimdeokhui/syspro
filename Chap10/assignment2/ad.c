#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *rear, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));

    newNode->data = data;
    newNode->next = NULL;

    rear->next->next = newNode;
    rear->next = newNode;
}

int delete(struct node *front) {
    struct node *temp = front->next;
    int data = temp->data;

    front->next = temp->next;
    free(temp);

    return data;
}

void printQueue(struct node *front) {
    while (front->next != NULL) {
        printf("%d ", front->next->data);
        front = front->next;
    }
    printf("\n");
}

int main() {
    struct node *front = (struct node *)malloc(sizeof(struct node));
    struct node *rear = (struct node *)malloc(sizeof(struct node));

    front->next = NULL;
    rear->next = NULL;

    int value;
    while (1) {
        if (scanf("%d", &value) != 1) {
            printf("Print queue\n");
            printQueue(front);
            break;
        }

        addq(rear, value);
        if (front->next == NULL) {
            front->next = rear->next;
        }
    }

    while (front->next != NULL) {
        int deletedValue = delete(front);
        printf("%d\n", deletedValue);
    }

    free(front);
    free(rear);

    return 0;
}

