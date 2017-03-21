#include "RawTextProcessing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Decode.h"

void growArray(int **intArray, char ***charArray, int currentSize)
{
    int i;
    if (intArray)
    {
        *intArray = realloc(*intArray, (currentSize + SIZE_INCREMENT + 1) * sizeof(int));
    }

    if (charArray)
    {
        *charArray = realloc(*charArray, (currentSize + SIZE_INCREMENT + 1) * sizeof(char*));

        for (i = currentSize + 1; i < currentSize + SIZE_INCREMENT + 1; i++)
        {
            charArray[0][i] = calloc(LARGEST_WORD, sizeof(char));
            if (!charArray[0][i])
            {
                error("String arrays filled");
            }
        }
    }

    if (!*intArray)
    {
        error("Int array filled");
    }
    else if (!*charArray)
    {
        error("Char array filled");
    }

    return;
}

Dictionary *processInput(char *buffer)
{
    int i,
        processedWords = 0;
    char *temp;

    Dictionary *dict = calloc(1, sizeof(Dictionary));

    // Initialize word array
    dict->words = calloc(SIZE_INCREMENT, sizeof(int));
    for (i = 0; i < SIZE_INCREMENT; i++)
    {
        dict->words[i] = calloc(LARGEST_WORD, sizeof(char));
    }

    dict->wordSizes = calloc(SIZE_INCREMENT, sizeof(char*));

    // Split continuous stream of characters into individual words
    for (temp = strtok(buffer, " \r\n.,?!\""); temp; temp = strtok(NULL, " \r\n.,?!\""), dict->numberOfWords++)
    {
        if ((dict->numberOfWords + 1) % SIZE_INCREMENT == 0)
        {
            growArray(&dict->wordSizes, &dict->words, dict->numberOfWords);
        }

        strcpy(dict->words[dict->numberOfWords], temp);

        shrinkWord(&dict->words[dict->numberOfWords]);

        // +1 for null-termination
        dict->wordSizes[dict->numberOfWords] = strlen(dict->words[dict->numberOfWords]) + 1;
    }

    return dict;
}

void processListOfWordsFile(char *fileName)
{
    FILE *wordListFile = NULL;
    char *buffer = NULL;
    int fileSize = 0;

    printf("Processing file...\n");

    wordListFile = fopen(fileName, "rb");

    if (wordListFile)
    {
        fseek(wordListFile, 0, SEEK_END);
        fileSize = ftell(wordListFile);
        fseek(wordListFile, 0, SEEK_SET);

        // +1 for null-termination
        buffer = calloc(fileSize + 1, sizeof(char));

        fread(buffer, 1, fileSize, wordListFile);

        fclose(wordListFile);

        Dictionary *dict = processInput(buffer);
        writeDictionary(dict);
    }
    else
    {
        error("Error opening dictionary text for processing");
    }
}

void shrinkWord(char **word)
{
    *word = realloc(*word, strlen(*word) + 1);
    return;
}

void writeDictionary(Dictionary *dict)
{
    int i;
    FILE *bin = fopen("processed.dict", "wb+");

    if (bin)
    {
        fwrite(&dict->numberOfWords, 1, sizeof(int), bin);
        fwrite(dict->wordSizes, dict->numberOfWords, sizeof(int), bin);

        for (i = 0; i < dict->numberOfWords; i++)
        {
            capitalizeString(dict->words[i]);
            fwrite(dict->words[i], 1, dict->wordSizes[i], bin);
        }

        fclose(bin);
    }
    else
    {
        error("Could not open dictionary file for output");
    }

    printf("Wrote data to bin dictionary\n");

    return;
}

