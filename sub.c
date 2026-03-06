#include "apc.h"

/*
Function : subtraction
Purpose  : Performs subtraction of two large numbers stored as
           doubly linked lists and stores the result in a result list.
*/

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int borrow_flag = 0;   // indicates if borrow is required
    int sub;

    node *temp1 = tail1;   // pointer to traverse first operand
    node *temp2 = tail2;   // pointer to traverse second operand

    // loop until both lists are fully traversed
    while (temp1 != NULL || temp2 != NULL)
    {
        int digit1 = 0;
        int digit2 = 0;
        
        // fetch digit from first operand
        if (temp1 != NULL)
        {
            digit1 = temp1->data;
        }

        // fetch digit from second operand
        if (temp2 != NULL)
        {
            digit2 = temp2->data;
        }

        // apply previous borrow
        if (borrow_flag)
        {
            digit1 = digit1 - 1;
            borrow_flag = 0;
        }

        // check if borrow is needed
        if (digit1 < digit2)
        {
            digit1 = digit1 + 10;
            borrow_flag = 1;
        }

        sub = digit1 - digit2;   // compute subtraction

        insert_first(headR, tailR, sub);   // store result digit

        // move to previous digit of operand1
        if (temp1)
        {
            temp1 = temp1->prev;
        }

        // move to previous digit of operand2
        if (temp2)
        {
            temp2 = temp2->prev;
        }
    }
}