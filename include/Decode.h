#ifndef DECODE_H
#define DECODE_H

#include <stdbool.h>

#include "RawTextProcessing.h"

#define MUTABLE_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*
    Input:          Two pointers to dictionaries. The first is the code to break, the second
                    is the dictionary to use to confirm a crack.
    Description:    Cycles through all 26 possibilities like a heathen, and counts how many
                    words in each permutation of the cipher match with a word in the dictionary
                    like a savage. The key is found by checking which cycle had the most hits.
    Output:         The key discovered.
*/
int barbaricAnalysis(Dictionary *cipher, Dictionary *dict);

/*
    Input:          A pointer to a string to capitalize.
    Description:    Iterates over all characters, capitalizing each.
    Output:         void.
*/
void capitalizeString(char *string);

/*
    Input:          The character to cycle, and the ticks to cycle it by.
    Description:    Checks if the character is legal to cycle, then cycles it, ensuring that
                    the last letter in the set (MUTABLE_CHARACTERS) wraps back around to the
                    first.
    Output:         The cycled character.
*/
char cycleChar(char original, int ticks);

/*
    Input:          A cstring containing the name of the file being cracked, and the key
                    in which it was encoded in.
    Description:    Iterates over each character in the input file. If it isMutable(), cycles it
                    by the key, which decrypts it. Calls writeAnswer afterwards.
    Output:         void.
*/
void decryptFile(char *fileName, int key);

/*
    Input:          A character to check.
    Description:    Checks if the character is in the list set by MUTABLE_CHARACTERS.
    Output:         True if it is, false otherwise.
*/
bool isMutable(char c);

/*
    Input:          A cstring containing the name of the file to load, and another containing the
                    name of the dictionary to load.
    Description:    Reads the dictionary from the .dict file into a Dictionary struct pointer. Loads the
                    encrypted file via loadFileToDecode() and capitalizes it with capitalizeString(). Then,
                    calls barbaricAnalysis() on these dictionaries and calls decryptKey().
                    Non-specific functions are bad :)
    Output:         void.
*/
void loadDictionary(char *fileName, char *dictionaryName);

/*
    Input:          A cstring containing the name of the file to load.
    Description:    Dynamically allocates a cstring to be large enough to hold the contents
                    of the file.
    Output:         A cstring containing the file's contents.
*/
char *loadFileToDecode(char *fileName);

/*
    Input:          A pointer to a dictionary struct.
    Description:    Displays all information contained in the dictionary.
    Output:         void.
*/
void printDictionary(Dictionary *dict);

/*
    Input:          Cstring to write.
    Description:    Writes the input to decoded.txt.
    Output:         void.
*/
void writeAnswer(char *buffer);

#endif // DECODE_H
