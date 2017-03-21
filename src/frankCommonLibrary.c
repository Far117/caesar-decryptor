#include "frankCommonLibrary.h"
#include <stdio.h>
#include <string.h>

int askCharQuestion(char *question)
{
    char answer = 0;
    printf("%s\n> ", question);
    scanf(" %c", &answer); // Space included to flush buffer
    fflush(stdin);

    return answer;
}

int askIntQuestion(char *question)
{
    int answer = 0;
    printf("%s\n> ", question);
    scanf(" %i", &answer);
    fflush(stdin);

    return answer;
}

float askFloatQuestion(char *question)
{
    float answer = 0;
    printf("%s\n> ", question);
    scanf(" %f", &answer);
    fflush(stdin);

    return answer;
}

short askBoolQuestion(char *question)
{
    int response = -1;

    do
    {
        printf("%s\n> ", question);
        scanf(" %i", &response);
        fflush(stdin);

        if (response < 0 || response > 1)
        {
            printf("\t\tERROR: Input must be either a 0 (false) or 1 (true)!\n");
        }

    } while (response < 0 || response > 1);

    return response;
}

char *askStringQuestion(char *question, int maxLength)
{
    char *answer = calloc(maxLength + 1, sizeof(char));
    printf("%s\n> ", question);
    fgets(answer, maxLength, stdin);

    fflush(stdin);
    return answer;
}

void error(char *err)
{
    printf("ERROR: %s!\n", err);
    PAUSE;

    return;
}

int multiprobabilisticRand(int probabilities[], int arraySize)
{

	int i, winner = -1, total = 0, choice = 0, currentTick = 0;

	// Total all probabilities
	for (i = 0; i < arraySize; i++)
	{
		total += probabilities[i];
	}

    // Select winning number
	choice = rand() % total;

	// Match number with index
	for (i = 0; i < arraySize; i++)
	{
		currentTick += probabilities[i];

		if (choice < currentTick)
		{
			winner = i;
			break;
		}
	}

	return winner;
}

int randMinMax(int minimum, int maximum)
{
    return (rand() % (maximum - minimum)) + minimum;
}
