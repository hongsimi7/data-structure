#include <sstream>
#include <iostream>
#include <string>
using namespace std;

struct Node {      
    int value;
    Node* next;
    Node* pre;
};

void insert_node(Node** head, int value) {
    Node* element = new Node;
    element->value = value;
    element->next = NULL;
    element->pre = NULL;

    if (*head == NULL) {
        *head = element;
        return;
    }

    Node* finder = *head;

    while(finder->next != NULL)
    {
        finder= finder->next;
    }
    finder->next = element;
    element->pre = finder;
}

void delete_node(Node** head, int value) {
    if (*head == NULL) {
        return;
    }

    Node* finder = *head;

    if (finder->value == value) {
        *head = finder->next;
        delete finder;
        return;
    }

    while (finder->next != NULL) {
        if (value == finder->next->value) {
            Node* temp = finder->next;
            finder->next = temp->next;
            delete temp;
            return;
        } else {
            finder = finder->next;
        }
    }
}
