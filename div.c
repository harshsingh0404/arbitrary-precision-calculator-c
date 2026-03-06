#include "apc.h"

/*
Function : division
Purpose  : Performs division of two large numbers stored as doubly linked lists
Input    : headL1 -> dividend list
           head_opr2, tail_opr2 -> divisor list
Output   : headR, tailR -> result (quotient) list
*/

void division(node *headL1, node *head_opr2, node *tail_opr2,
              node **headR, node **tailR)
{
    // Check if operands exist
    if (headL1 == NULL || head_opr2 == NULL)
    {
        return;
    }

    // Check divide by zero
    if (head_opr2->data == 0 && head_opr2->next == NULL)
    {
        printf("Error: Divide by zero");
        return;
    }

    node *head_opr1 = NULL;
    node *tail_opr1 = NULL;
    node *temp_l1   = headL1;

    int sub_count = 0;   // Stores quotient digit

    // Insert first digit of dividend
    insert_last(&head_opr1, &tail_opr1, temp_l1->data);

    // Expand dividend until it becomes >= divisor
    while (temp_l1->next &&
           compare_list(head_opr1, head_opr2) == OPERAND2)
    {
        temp_l1 = temp_l1->next;
        insert_last(&head_opr1, &tail_opr1, temp_l1->data);
    }

    // Main division loop
    while (temp_l1 != NULL)
    {
        node *head_sr = NULL;
        node *tail_sr = NULL;

        // Repeated subtraction to get quotient digit
        while (compare_list(head_opr1, head_opr2) != OPERAND2)
        {
            subtraction(tail_opr1, tail_opr2, &head_sr, &tail_sr);

            delete_list(&head_opr1, &tail_opr1);

            head_opr1 = head_sr;
            tail_opr1 = tail_sr;
            head_sr = tail_sr = NULL;

            remove_pre_zeros(&head_opr1);

            sub_count++;   // Count subtraction
        }

        insert_last(headR, tailR, sub_count); // Store quotient digit
        sub_count = 0;

        temp_l1 = temp_l1->next;

        // Bring down next digit
        if (temp_l1)
        {
            insert_last(&head_opr1, &tail_opr1, temp_l1->data);
        }
    }
}