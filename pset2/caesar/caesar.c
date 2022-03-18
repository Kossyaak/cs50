#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool key(string s);

void crypt(string plaintext, string ciphertext, int k);

int main(int argc, string argv[])
{
    if (argc != 2 || !key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int k = atoi(argv[1]);
    string s = get_string("plaintext: ");
    int n = strlen(s);
    char ciphertext[n + 1];
    crypt(s, ciphertext, k);
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}








void crypt(string plaintext, string ciphertext, int k)
{
    int i = 0;
    for (i = 0; i < strlen(plaintext); i++)
    {
        char ch = plaintext[i];
        if (isalpha(ch))
        {
            char tm = tolower(ch);
            int pi = tm - 'a';
            char ci = ((pi + k) % 26) + 'a';
            ciphertext[i] = islower(ch) ? ci : toupper(ci);//тернальный оператор (если islower = true, выполняется toupper)
        }
        else
        {
            ciphertext[i] = ch;
        }
    }
    ciphertext[i] = '\0';
}


bool key(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        char ch = s[i];
        if (!isdigit(ch))
        {
            return false;
        }

    }
    return true;

}
