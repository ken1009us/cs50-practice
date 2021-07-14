#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number, size, container, container_two, digit, digit_two, num;
    long count = 0, sum = 0, sum_two = 0, digit_x = 0, digit_y = 0;
    int start_digit, start_digit_two;

    //Get the number from user
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    //Sum of the number’s second-to-last digit
    container = number;
    for (long i = 100 ; i <= number * 10 ; i *= 100)
    {
        digit = (container % 100) / 10;
        container = number / i;
        if ((digit * 2) >= 10)
        {
            digit_x += (digit * 2) / 10;
            digit_y += (digit * 2) % 10;
        }
        else
        {
            sum += (digit * 2);
        }
    }
    long db_sum = sum + digit_x + digit_y;

    //Sum digits that weren’t multiplied by 2
    container_two = number;
    for (long j = 100 ; j <= number * 10 ; j *= 100)
    {
        digit_two = (container_two % 10);
        container_two = number / j;
        sum_two += digit_two;
        if (container_two < 10)
        {
            sum_two += container_two;
            break;
        }
        else
        {
            continue;
        }
    }

    long total = db_sum + sum_two;

    //Count the size of the number
    size = number;
    while (size != 0)
    {
        size /= 10;
        count ++;
        if (size < 100 && size > 10)
        {
            start_digit = size;
        }
        if (size < 10 && size > 0)
        {
            start_digit_two = size;
        }
    }

    //Validating credit card numbers
    if (total % 10 == 0)
    {
        if (count == 15 && start_digit == 34 || start_digit == 37)
        {
            printf("AMEX\n");
        }
        else if (count == 16 && start_digit == 51 || start_digit == 52 || start_digit == 53 || start_digit == 54 || start_digit == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (count == 13 || count == 16 && start_digit_two == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}