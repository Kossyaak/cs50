//Реализует функциональность словаря

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


//Представляет узел в хеш-таблице
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Количество сегментов в хеш-таблице
const unsigned int N = 46 * 122;//макс число букв(учитывая 0 символ) * ascii значение 'z'
int wordcount = 0;

//Хеш-таблица
node *table[N];

//Возвращает true, если слово находится в словаре, иначе false
bool check(const char *word)
{
    int s = strlen(word);
    char tmpword[LENGTH + 1];
    for (int i = 0; i < s; i++)
    {
        tmpword[i] = tolower(word[i]);
    }
    tmpword[s] = '\0';
    int index = hash(tmpword);
    node *cursor = table[index];
    for(;cursor != NULL;)
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

//Хеширует слово в число
unsigned int hash(const char *word)
{
    int summ = 0;
    int k = strlen(word);
    int f = 0;
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < k; j++)
        {
            f = word[i];
        }
        summ = summ + f;
    }
    return summ % N;
}

//Загружает словарь в память, возвращая true в случае успеха иначе false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *opendict = fopen(dictionary, "r");
    if(opendict == NULL)
    {
        return false;
    }
    for(;fscanf(opendict, "%s", word) != EOF;)
    {
        node *node1 = malloc(sizeof(node));
        if(node1 == NULL)
        {
            return false;
        }
        strcpy(node1->word, word);
        node1->next = NULL;
        int index = hash(word);
        if(table[index] == NULL)
        {
            table[index] = node1;
        }
        else
        {
            node1->next = table[index];
            table[index] = node1;
        }
        wordcount++;
    }
    fclose(opendict);
    return true;
}

//Возвращает количество слов в словаре, если загружено, иначе 0, если еще не загружено
unsigned int size(void)
{
   return wordcount;
}

//Выгружает словарь из памяти, возвращая true в случае успеха иначе false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        for(;cursor != NULL;)
        {
             cursor = cursor->next;
             free(tmp);
             tmp = cursor;
        }

    }
    return true;
}
