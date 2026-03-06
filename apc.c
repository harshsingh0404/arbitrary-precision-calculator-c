#include "apc.h"
#include <ctype.h>

/*

Function Name : cla_validation
Description   : Validates command line arguments. Checks whether
                the number of arguments is correct, the operator
                is valid, and both operands contain only digits
                (allowing a negative sign at the beginning).
Parameters    :
    argc -> argument count
    argv -> argument vector
Return Value  :
    SUCCESS if valid input
    FAILURE if invalid input

*/
int cla_validation(int argc, char *argv[])
{
    if (argc != 4)               // check number of arguments
        return FAILURE;

    /* operator validation */
    if (!(argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == 'x' ||
          argv[2][0] == 'X' || argv[2][0] == '/'))
        return FAILURE;

    /* operand1 validation */
    int i = 0;
    if (argv[1][0] == '-')      // allow negative sign
        i = 1;

    for (; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))   // check digit
            return FAILURE;
    }

    /* operand2 validation */
    i = 0;
    if (argv[3][0] == '-')
        i = 1;

    for (; argv[3][i] != '\0'; i++)
    {
        if (!isdigit(argv[3][i]))   // check digit
            return FAILURE;
    }

    return SUCCESS;
}

/*

Function Name : create_list
Description   : Creates a doubly linked list from the operand
                string where each node stores one digit.
Parameters    :
    opr  -> operand string
    head -> pointer to head pointer
    tail -> pointer to tail pointer
Return Value  : None

*/
void create_list(char *opr, node **head, node **tail)
{
    while (*opr)                         // traverse operand string
    {
        node *new = malloc(sizeof(node));  // allocate new node
        if (new == NULL)
            return;

        new->data = *opr - '0';           // convert char to digit
        new->prev = NULL;
        new->next = NULL;

        if (*head == NULL)                // first node
        {
            *head = *tail = new;
        }
        else                              // append node at end
        {
            (*tail)->next = new;
            new->prev = *tail;
            *tail = new;
        }

        opr++;                            // move to next character
    }
}

/*

Function Name : insert_first
Description   : Inserts a new node at the beginning of the list.
Parameters    :
    head -> pointer to head pointer
    tail -> pointer to tail pointer
    data -> digit to insert
Return Value  :
    SUCCESS if inserted
    FAILURE if memory allocation fails

*/
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));     // allocate new node
    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)                    // if list empty
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else                                  // insert at beginning
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
        return SUCCESS;
    }
}

/*

Function Name : insert_last
Description   : Inserts a new node at the end of the list.

*/
int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));   // allocate new node
    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    if (*head == NULL)                  // empty list
    {
        *head = *tail = new;
        return SUCCESS;
    }

    (*tail)->next = new;                // attach to tail
    new->prev = *tail;
    *tail = new;

    return SUCCESS;
}

/*

Function Name : delete_list
Description   : Frees all nodes of the linked list.

*/
int delete_list(node **head, node **tail)
{
    if (*head == NULL)
        return FAILURE;

    node *temp;

    while (*head != NULL)               // traverse and delete nodes
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
    return SUCCESS;
}

/*

Function Name : compare_list
Description   : Compares two operand lists and determines which
                operand is larger.
Return Value  :
    OPERAND1 if first is larger
    OPERAND2 if second is larger
    SAME     if both are equal

*/
int compare_list(node *head1, node *head2)
{
    int list1 = list_len(head1);
    int list2 = list_len(head2);

    if(list1 > list2)
        return OPERAND1;

    else if(list1 < list2)
        return OPERAND2;

    else
    {
        node *temp1 = head1;
        node *temp2 = head2;

        while(temp1 != NULL)            // compare digit by digit
        {
            if(temp1->data > temp2->data)
                return OPERAND1;

            else if(temp1->data < temp2->data)
                return OPERAND2;

            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return SAME;
    }
}

/*

Function Name : list_len
Description   : Counts the number of nodes in the list.

*/
int list_len(node *head)
{
    int count = 0;

    while(head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

/*

Function Name : remove_pre_zeros
Description   : Removes leading zeros from the result list.

*/
void remove_pre_zeros(node **head)
{
    if (*head == NULL)
        return;

    node *temp = *head;

    while (temp->data == 0 && temp->next != NULL)
    {
        *head = temp->next;
        (*head)->prev = NULL;
        free(temp);
        temp = *head;
    }
}

/*
Function Name : print_number
Description   : Prints the number stored in the linked list.
*/
void print_number(node *head)
{
    while (head)
    {
        printf("%d", head->data);   // print each digit
        head = head->next;
    }
    printf("\n");
}