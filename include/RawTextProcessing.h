#ifndef RAWTEXTPROCESSING_H
#define RAWTEXTPROCESSING_H

#define SIZE_INCREMENT 1000
#define LARGEST_WORD 50

typedef struct Dictionary
{
    char **words;
    int *wordSizes;
    int numberOfWords;
}Dictionary;

/*
    Input:          A double pointer of ints and a triple pointer of characters, and an int containing
                    the current size of both.
    Description:    Reallocates the arrays to hold an additional SIZE_INCREMENT-sized chunk of data.
    Output:         void.
*/
void growArray(int **intArray, char ***charArray, int currentSize);

/*
    Input:          A string of characters representing the input to tokenize.
    Description:    Initializes a pointer to a Dictionary struct. Then, strtok() is
                    repeatedly called to split the input into its individual words.
                    The pointers to each word are shrunk so that they're just large
                    enough to hold their data and conserve space. After processing,
                    all fields of the Dictionary will be filled.
    Output:         A pointer to a fully-filled Dictionary struct.
*/
Dictionary *processInput(char *buffer);

/*
    Input:          A pointer to a string of characters containing the name of the file to operate on.
    Description:    Opens the file contained in fileName, and discerns its size. Then, allocates
                    a char pointer with enough space to hold the entire file. Finally, reads the
                    contents of the file into the pointer. Calls processInput() and writeDictionary()
                    afterwards.
    Output:         void.
*/
void processListOfWordsFile(char *fileName);

/*
    Input:          A double pointer to the string to shrink.
    Description:    Reallocates the string to be of size strlen(*word) + 1.
    Output:         void.
*/
void shrinkWord(char **word);

/*
    Input:          A pointer to a dictionary.
    Description:    Writes the dictionary's contents to a binary file in the following order:
                    numberOfWords -> wordSizes -> words
                    Done for ease-of-use.
    Output:         void.
*/
void writeDictionary(Dictionary *dict);

#endif // RAWTEXTPROCESSING_H
