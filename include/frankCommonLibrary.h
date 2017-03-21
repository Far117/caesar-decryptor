#ifndef FRANKCOMMONLIBRARY_H
#define FRANKCOMMONLIBRARY_H

#define CLS system("cls")
#define PAUSE system("pause")

/*
    Input:          A pointer to a sequence of characters representing the question to ask the user.
    Description:    Prompts a user for a boolean value of 1 or 0. Repeats the question if invalid user input
                    is given.
    Output:         The validated value the user entered.
*/
short askBoolQuestion(char *question);

/*
    Input:          A pointer to a string of characters representing the prompt.
    Description:    Displays a prompt, then waits for the user to reply to it.
    Output:         A char representing the user's response.
*/
int askCharQuestion(char *question);

/*
    Input:          A pointer to a string of characters representing the prompt.
    Description:    Displays a prompt, then waits for the user to reply to it.
    Output:         A float representing the user's response.
*/
float askFloatQuestion(char *question);

/*
    Input:          A pointer to a string of characters representing the prompt.
    Description:    Displays a prompt, then waits for the user to reply to it.
    Output:         An int representing the user's response.
*/
int askIntQuestion(char *question);

/*
    Input:          A pointer to a string of characters representing the prompt.
    Description:    Displays a prompt, then waits for the user to reply to it.
    Output:         A cstring containing the user's response.
*/
char *askStringQuestion(char *question, int maxLength);

/*
    Input:          A pointer to a string of characters containing the error message.
    Description:    Displays a formatted error message, then waits for user input.
    Output:         void.
*/
void error(char *err);

/*
    Input:          An array of ints representing the probabilities to be chosen from, and
                    another int containing the size of the array.

    Description:    Picks a random number between 0 and the total of all probabilities chosen.
                    Iterates over the probability array, subtracting each index from the total.
                    If the total is less than the random number, that index was chosen.

    Example:        If probabilities = {50, 20, 30}, the first index has a 50% chance of being chosen,
                    the second has a 20% chance, and the third a 30% chance.

    Output:         The number of the chosen index.
*/
int multiprobabilisticRand(int probabilities[], int arraySize);

/*
    Input:          An int containing the minimum number to return, and an int containing the maximum.
    Description:    Pulls a random value between zero and the difference between the maximum and
                    minimum values, then adds the minimum value to this number.
    Output:         The previously calculated int.
*/
int randMinMax(int minimum, int maximum);

#endif // FRANKCOMMONLIBRARY_H
