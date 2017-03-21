#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "frankCommonLibrary.h"
#include "RawTextProcessing.h"
#include "Decode.h"

void help();
long timediff(clock_t t1, clock_t t2);

/*
    Input:          An int containing the number of arguments passed to the program, and a variable
                    list containing the actual arguments.
    Description:    Iterates over all arguments, setting flags for each one. Afterwards, checks all flags,
                    performing the actions they denote.
    Output:         An integral value representing the error code. If no error, a 0 is returned.
*/
int main(int argc, char *argv[])
{
    int i;
    char *dictionary = "short.dict";
    bool    process = false,
            solve = false,
            customDictionary = false;
    int processPosition = 0,
        solvePosition = 0,
        customDictionaryPosition = 0;

    clock_t start = clock();

    if (argc <= 2)
        help();

    for (i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "/p")) {if (i < argc) {process = true; processPosition = i + 1;}}
        if (!strcmp(argv[i], "/i")) {if (i < argc) {solve = true; solvePosition = i + 1;}}
        if (!strcmp(argv[i], "/d")) {if (i < argc) {customDictionary = true; customDictionaryPosition = i + 1;}}
    }

    if (process)
    {
        processListOfWordsFile(argv[processPosition]);
    }

    if (customDictionary)
    {
        dictionary = argv[customDictionaryPosition];
    }

    if (solve)
    {
        loadDictionary(argv[solvePosition], dictionary);
    }

    printf("Completed in: %ld ms\n", (long)timediff(start, clock()));

    PAUSE;
    return 0;
}

/*
    Input:          Two clock_ts to compare.
    Description:    Subtracts the second clock value from the first, divides this by CLOCKS_PER_SECOND,
                    then multiplies by 1,000. This gets the difference between the two times in
                    milliseconds.
    Output:         The difference between the inputs in milliseconds.
*/
long timediff(clock_t t1, clock_t t2)
{
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

/*
    Input:          None.
    Description:    Displays all commands with example usage.
    Output:         void.
*/
void help()
{
    CLS;

    printf("\n\n\t\t\tFrank's Caesar Cipher Solver\n\n\n");
    printf("\tCommands:\n\n");
    printf("/p [filename]: Loads a list of words to process into a dictionary file\n");
    printf("/i [filename]: Selects the encrypted file you would like to decrypt\n");
    printf("/d [filename]: Selects the dictionary file you would like to use. short.dict is selected by default\n");
    printf("\n\tExamples:\n\n");
    printf("decode /p wordList.txt\n");
    printf("decode /i encryptedFile.txt\n");
    printf("decode /i encryptedFile.txt /d long.dict\n");

    return;
}
