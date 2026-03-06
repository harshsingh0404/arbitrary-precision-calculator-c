#include "apc.h"

/*
Function : multiplication
Purpose  : Performs multiplication of two large numbers stored as
           doubly linked lists and stores the result in another list.
*/

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp2 = tail2;      // pointer to traverse second operand
    node *headAR = NULL;      // head for accumulated result
    node *tailAR = NULL;      // tail for accumulated result

    int count = 0;            // keeps track of shifting (place value)
    
    while (temp2 != NULL)
    {
        node *temp1 = tail1;  // pointer to traverse first operand
        node *headR2 = NULL;  // head for partial result
        node *tailR2 = NULL;  // tail for partial result

        int carry = 0;        // carry during multiplication

        // shifting partial result by adding zeros
        for (int i = 0; i < count; i++)
        {
            insert_first(&headR2, &tailR2, 0);
        }

        // multiply digits of operand1 with current digit of operand2
        while (temp1 != NULL)
        {
            int mul = (temp1->data * temp2->data) + carry;
            int last_digit = mul % 10;
            carry = mul / 10;

            insert_first(&headR2, &tailR2, last_digit);

            temp1 = temp1->prev;   // move to next digit
        }

        // insert remaining carry if present
        if (carry)
        {
            insert_first(&headR2, &tailR2, carry);
        }

        // add partial result to accumulated result
        if (*headR == NULL)
        {
            *headR = headR2;
            *tailR = tailR2;
        }
        else
        {
            addition(*tailR, tailR2, &headAR, &tailAR);

            delete_list(headR, tailR);
            delete_list(&headR2, &tailR2);

            *headR = headAR;
            *tailR = tailAR;

            headAR = NULL;
            tailAR = NULL;
        }

        count++;              // increase shift count
        temp2 = temp2->prev;  // move to next digit of operand2
    }
}