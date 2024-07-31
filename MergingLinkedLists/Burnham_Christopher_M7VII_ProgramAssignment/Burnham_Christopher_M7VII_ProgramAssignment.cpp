// Burnham_Christopher_M7VII_ProgramAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node* next;
};

/* new function create new */
Node* newNode(int data)
{
    Node* new_node = new Node();
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/*function to insert a node at the beginning of the linked list */
void push(Node** head_ref, int new_data)
{
    /* allocate node */
    Node* new_node = newNode(new_data);

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

/*function to add two lists together*/
Node* addLists(Node* first, Node* second)
{
    Node* result = NULL;
    Node* temp = NULL , * prev = NULL;
    int y = 0;
    int sum;

    /*while the list exists for both*/
    while (first != NULL || second != NULL)
    {
        sum = y + (first ? first->data : 0) + (second ? second->data : 0);

        y = (sum >= 10) ? 1 : 0;

        /*update sum if it is greater than 10*/
        sum = sum % 10;
              
        temp = newNode(sum);
        if (result == NULL)
        {
            result = temp;
        }
        else
        {
            prev->next = temp;
        }

        prev = temp;

        /*moving pointers to the next in list*/
        if (first)
        {
            first = first->next;
        }
        if (second)
        {
            second = second->next;
        }
    }
    if (y > 0)
    {
        temp->next = newNode(y);
    }
    /*return the head of the list*/
    return result;
}

/*reverse function*/
Node* reverse(Node* x)
{
    if (x == NULL || x->next == NULL)
    {
        return x;
    }
    /* reverse the rest of the list*/

    Node* rest = reverse(x->next);
    x->next->next = x;

    x->next = NULL;

    return rest;
}

/*printing linked list function*/
void printList(Node* node)
{
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}


/* main code */
int main()
{
    Node* result = NULL;
    Node* first = NULL;
    Node* second = NULL;

    /*create the first list here*/
    push(&first, 1);
    push(&first, 2);
    push(&first, 3);
    push(&first, 4);
    push(&first, 5);
    printf("The first linked list is: ");
    printList(first);

    /*create a second list*/
    push(&second, 7);
    push(&second, 2);
    push(&second, 1);
    push(&second, 6);
    push(&second, 3);
    cout << "The second linked list is: ";
    printList(second);

    /*reverse both the lists*/
    first = reverse(first);
    second = reverse(second);

    result = addLists(first, second);

    /*reverse result to get the sum*/
    result = reverse(result);
    cout << "The resulting list is: ";
    printList(result);

    return 0;
}