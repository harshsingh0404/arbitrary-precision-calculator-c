/*
-----------------------------------------------------------
Name        : Harsh Singh
Project     : Arbitrary Precision Calculator (APC)
File Name   : main.c
Description   : Entry point of the Arbitrary Precision Calculator.
                It validates command line arguments, converts the
                operands into doubly linked lists, performs the
                requested arithmetic operation (+, -, *, /) and
                prints the result.
-----------------------------------------------------------
*/

#include "apc.h"

int cla_validation(int argc, char *argv[]);   // function declaration

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL;   // operand1 list
    node *head2 = NULL, *tail2 = NULL;   // operand2 list
    node *headR = NULL, *tailR = NULL;   // result list

    // validate command line arguments
    if (cla_validation(argc, argv) == FAILURE)
    {
        printf("Invalid input\n");
        return FAILURE;
    }

    char sign1 = '+';
    char sign2 = '+';

    // check sign of operand1
    if(argv[1][0] == '-')
    {
        sign1 = '-';
        argv[1]++;
    }

    // check sign of operand2
    if(argv[3][0] == '-')
    {
        sign2 = '-';
        argv[3]++;
    }

    // create linked lists for operands
    create_list(argv[1], &head1, &tail1);
    create_list(argv[3], &head2, &tail2);

    char oper = argv[2][0];   // operator

    switch (oper)
    {

    // -------- ADDITION --------
    case '+':
    {
        if(sign1 == sign2)
        {
            addition(tail1, tail2, &headR, &tailR);

            if(sign1 == '-')
                printf("-");
        }
        else
        {
            int cmp = compare_list(head1, head2);

            if(cmp == OPERAND1)
            {
                subtraction(tail1, tail2, &headR, &tailR);

                if(sign1 == '-')
                    printf("-");
            }
            else
            {
                subtraction(tail2, tail1, &headR, &tailR);

                if(sign2 == '-')
                    printf("-");
            }
        }

        remove_pre_zeros(&headR);
        break;
    }

    // -------- SUBTRACTION --------
    case '-':
    {
        if(sign2 == '-')
        {
            addition(tail1, tail2, &headR, &tailR);

            if(sign1 == '-')
                printf("-");
        }
        else if(sign1 == '-')
        {
            addition(tail1, tail2, &headR, &tailR);
            printf("-");
        }
        else
        {
            int cmp = compare_list(head1, head2);

            if(cmp == SAME)
            {
                printf("0\n");
                return SUCCESS;
            }
            else if(cmp == OPERAND1)
            {
                subtraction(tail1, tail2, &headR, &tailR);
            }
            else
            {
                subtraction(tail2, tail1, &headR, &tailR);
                printf("-");
            }
        }

        remove_pre_zeros(&headR);
        break;
    }

    // -------- MULTIPLICATION --------
    case 'x':
    case 'X':
    {
        multiplication(tail1, tail2, &headR, &tailR);

        if(sign1 != sign2)
            printf("-");

        remove_pre_zeros(&headR);
        break;
    }

    // -------- DIVISION --------
    case '/':
    {
        division(head1, head2, tail2, &headR, &tailR);

        if(sign1 != sign2)
            printf("-");

        remove_pre_zeros(&headR);
        break;
    }

    default:
        printf("Invalid operator\n");
        return FAILURE;
    }

    // -------- COMMON OUTPUT FORMAT --------
    printf("operand1 = ");
    print_number(head1);

    printf("operator = %c\n", oper);

    printf("operand2 = ");
    print_number(head2);

    printf("result = ");
    print_number(headR);

    return SUCCESS;
}