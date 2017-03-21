#include "Decode.h"
#include <stdlib.h>
#include <stdio.h>
#include "RawTextProcessing.h"
#include "stdbool.h"
#include "ctype.h"
#include "frankCommonLibrary.h"

int barbaricAnalysis(Dictionary *cipher, Dictionary *dict)
{
    int i, j, cycle,
        key = 0,
        mostHits = 0;
    int *hits = calloc(26, sizeof(int));

    for (cycle = 0; cycle < 26; cycle++)
    {
        for (i = 0; i < cipher->numberOfWords; i++)
        {
            for (j = 0; j < strlen(cipher->words[i]); j++)
            {
                cipher->words[i][j] = cycleChar(cipher->words[i][j], 1);
            }
        }

        for (i = 0; i < cipher->numberOfWords; i++)
        {
            for (j = 0; j < dict->numberOfWords ; j++)
            {
                if (!strcmp(cipher->words[i], dict->words[j]))
                {
                    hits[cycle] = hits[cycle] + 1;
                }
            }
        }
    }

    mostHits = hits[0];
    for (i = 0; i < 26; i++)
    {
        if (hits[i] > mostHits)
        {
            key = i + 1;
            mostHits = hits[i];
        }
    }

    return key;
}

void capitalizeString(char *string)
{
    int i;

    for (i = 0; i < strlen(string); i++)
    {
        string[i] = toupper(string[i]);
    }

    return;
}

char cycleChar(char original, int ticks)
{
    char alphabet[26] = MUTABLE_CHARACTERS;
    int min = alphabet[0];
    int max = alphabet[25];

    if (isMutable(original))
        return min + ((original + ticks - min) % 26);

    return original;
}

void decryptFile(char *fileName, int key)
{
    char *buffer = loadFileToDecode(fileName);
    int i;

    capitalizeString(buffer);

    for (i = 0; i < strlen(buffer); i++)
    {
        buffer[i] = cycleChar(buffer[i], key);
    }

    writeAnswer(buffer);

    return;
}

bool isMutable(char c)
{
    int i;
    char mutables[26] = MUTABLE_CHARACTERS;

    for (i = 0; i < 26; i++)
    {
        if (mutables[i] == c)
            return true;
    }

    return false;
}

void loadDictionary(char *fileName, char *dictionaryName)
{
    Dictionary *dict = calloc(1, sizeof(Dictionary));
    Dictionary *cipher = NULL;
    FILE *dictFile = fopen(dictionaryName, "rb");
    char *buffer = NULL;

    int i,
        key = 0;

    if (dictFile)
    {
        fread(&dict->numberOfWords, 1, sizeof(int), dictFile);

        dict->wordSizes = calloc(dict->numberOfWords, sizeof(int));
        fread(dict->wordSizes, dict->numberOfWords, sizeof(int), dictFile);

        dict->words = calloc(dict->numberOfWords, sizeof(char*));
        for (i = 0; i < dict->numberOfWords; i++)
        {
            dict->words[i] = calloc(dict->wordSizes[i], sizeof(char));
            fread(dict->words[i], dict->wordSizes[i], sizeof(char), dictFile);
        }

        fclose(dictFile);
    }
    else
    {
        error("Couldn't load dictionary");
    }

    buffer = loadFileToDecode(fileName);

    cipher = processInput(buffer);
    for (i = 0; i < cipher->numberOfWords; i++)
        capitalizeString(cipher->words[i]);

    key = barbaricAnalysis(cipher, dict);
    decryptFile(fileName, key);

    return;
}

char *loadFileToDecode(char *fileName)
{
    int length = 0;
    FILE *file = fopen(fileName, "rb");
    char *buffer = NULL;

    if (file)
    {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = calloc(length + 1, sizeof(char));
        fread(buffer, 1, length, file);
        fclose(file);

        return buffer;
    }
    else
    {
        error("Couldn't read input file");
    }

    return NULL;
}

void printDictionary(Dictionary *dict)
{
    int i;
    printf("Number of words: %i\n", dict->numberOfWords);
    for (i = 0; i < dict->numberOfWords; i++)
    {
        printf("%i\t%s\n", dict->wordSizes[i], dict->words[i]);
    }

    return;
}

void writeAnswer(char *buffer)
{
    FILE *file = fopen("decoded.txt", "wb");

    if (file)
    {
        fwrite(buffer, 1, strlen(buffer) + 1, file);
        fclose(file);

        printf("Solved successfully\n");
    }
    else
    {
        error("Couldn't open output file");
    }

    return;
}
