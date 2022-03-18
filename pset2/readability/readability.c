#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


int main(void)
{
    string text = get_string("Text: ");
    int wordc = 0, sentc = 0, letc = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        char ch = text[i];
        if (isalpha(ch))
        {
            letc++;
        }
        if (isspace(ch))
        {
            wordc++;
        }
        if (ch == '.' || ch == '!' || ch == '?')
        {
            sentc++;
        }
    }
    wordc++;

    float L = (letc * 100.0f) / wordc;
    float S = (sentc * 100.0f) / wordc;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}