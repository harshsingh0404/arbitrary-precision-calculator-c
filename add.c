#include "apc.h"

/*
--------------------------------------------------------------------
Function Name : addition
Description   : Performs addition of two large numbers stored as
                doubly linked lists. Each node contains one digit.
                The addition is done from least significant digit
                (tail) to most significant digit (head).

Parameters    :
    tail1  -> tail pointer of first operand list
    tail2  -> tail pointer of second operand list
    headR  -> pointer to head pointer of result list
    tailR  -> pointer to tail pointer of result list
--------------------------------------------------------------------
*/

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry = 0;   // variable to store carry during addition

    while (tail1 != NULL || tail2 != NULL)   // continue until both lists end
    {   
        int digit1 = 0;   // digit from operand1
        int digit2 = 0;   // digit from operand2

        if(tail1 != NULL)
        {
            digit1 = tail1->data;   // fetch digit from first number
            tail1 = tail1->prev;    // move to previous node
        }

        if(tail2 != NULL)
        {
            digit2 = tail2->data;   // fetch digit from second number
            tail2 = tail2->prev;    // move to previous node
        }

        int sum = digit1 + digit2 + carry;   // add digits with carry
        int last_digit = sum % 10;           // get result digit
        carry = sum / 10;                    // update carry

        insert_first(headR, tailR, last_digit);   // insert result digit
    }

    if (carry == 1)   // if carry remains after addition
    {
        insert_first(headR, tailR, carry);   // insert carry at front
    }
}