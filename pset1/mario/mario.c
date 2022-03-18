#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h <= 0 || h >= 9);

    for (int i = 0; i < h; i++)
    {
        for (int j = h - i - 2; j >= 0; j--)
        {
            printf(" ");
        }
        for (int d = 0; d <= i; d++)
        {
            printf("#");
        }
        printf("\n");
    }
}


