#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Number: ");
    long input;
    scanf("%li", &input);

    //Get length
    int length = 0;

    for (long i = input; i > 0; i /= 10)
    {
        length++;
    }

    //Get start
    long start = 1;

    for (long i = length; i > 2; i--)
    {
        start *= 10;
    }
    start = input / start;

    //Checksum: Variables
    long mp = 1;
    long sum = 0;
    long digit;

    //Checksum: Go through all digits
    for (long i = length; i > 0; i--)
    {

        //Checksum: Get digit
        mp = 10;

        i--;
        mp = pow(mp, i);
        i++;

        digit = (input / mp % 10);

        //Checksum: Calculate sum
        if (i % 2 == 0 && digit * 2 >= 10)
        {
            digit *= 2;
            sum += digit / 10 + digit % 10;
        }
        else if (i % 2 == 0)
        {
            sum += digit * 2;
        }
        else
        {
            sum += digit;
        }
    }

    //Detect card
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (length == 15 && (start == 34 || start == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (start >= 51 && start <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && start / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}