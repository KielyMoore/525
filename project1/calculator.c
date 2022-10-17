#include <stdio.h>
#include <stdlib.h>

void printMenu(int options);

int main(int argc, char const *argv[])
{
    int total = 0;
    int input = 0;
    char control = 'i';

    while (control != 'e' && control != 'E')
    {
        system("clear");
        printMenu(0);
        scanf(" %c", &control);
        if (control == 'b' || control == 'B')
        {
            printf("Enter Starting Number: ");
            scanf("%d", &input);
            total = input;
            while (control != 'f' && control != 'F')
            {
                system("clear");
                printf("Current total: %d\n", total);
                printMenu(1);
                scanf(" %c", &control);
                if(control == 'f' || control == 'F')
                {
                    printf("Finale Total: %d", total);
                    break; 
                }
                printf("Enter Number: ");
                scanf("%d", &input);
                switch (control)
                {
                case 'a':
                case 'A':
                    total += input;
                    break;
                case 's':
                case 'S':
                    total -= input;
                    break;
                case 'm':
                case 'M':
                    total *= input;
                    break;
                case 'd':
                case 'D':
                    total /= input;
                    break;
                default:
                    break;
                }
            }
        }
    }

    printf("Total at Exit: %d\n", total);
    return 0;
}

void printMenu(int options)
{
    printf("==== CALCULATOR ====\n");
    printf("Operations:\n");
    switch (options)
    {
    case 0:
        printf("* B - Begin a Calculation\n");
        printf("* E - End Program\n");
        break;
    case 1:
        printf("* F - Finish a Calculation\n");
        printf("* A - Add next number\n");
        printf("* S - Subtract next number\n");
        printf("* M - Multiply by next number\n");
        printf("* D - Divide by next number\n");
        break;
    default:
        break;
    }
    printf("====================\n");
    printf("Enter Operation: ");
}