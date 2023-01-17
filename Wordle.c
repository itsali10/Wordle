#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <MMSystem.h>

#define maxnumwords 5757

struct Player
{
	char name[50];
	int score;
};

void green() {
	printf("\033[0;32m");
}

void yellow()
{
	printf("\033[1;33m");
}

void red() {
	printf("\033[1;31m");
}

void blue() {
	printf("\033[0;34m");
}

void reset() {
	printf("\033[0m");
}

int guess_check(char* answer, char* guess)
{
	char clue[6] = { '_', '_', '_', '_', '_','\0' }, c;
	int correctletters = 0, duplicatecounter = 0;
	for (int l = 0;l < 5;l++)
	{
		for (int p = 1;p < 5;p++)
		{
			if (answer[l] == answer[p])
				duplicatecounter++;
		}
	}
	for (int i = 0;i < 5;i++)
	{
		if (guess[i] == answer[i])
		{
			clue[i] = 'G';
			correctletters++;
		}
	}
	for (int j = 0;j < 5;j++)
	{
		if (clue[j] == '_')
		{
			for (int h = 0;h < 5;h++)
			{
				if (guess[j] == answer[h] && clue[h] != 'G' && duplicatecounter > 0)
				{
					clue[j] = 'Y';
				}
			}
		}
	}
	for (int k = 0;k < 5;k++)
	{
		c = guess[k];
		if (clue[k] == 'G')
		{
			green();
			printf("%c", c);
			reset();
		}
		if (clue[k] == 'Y')
		{
			yellow();
			printf("%c", c);
			reset();
		}
		if (clue[k] == '_')
		{
			red();
			printf("%c", c);
			reset();
		}
	}
	printf("\n\n");

	if (correctletters == 5)
		return 1;
	else
		return 0;
}

void main()
{
	PlaySound(TEXT("C:\\Users\\ItsAl\\Desktop\\test.wav"), NULL, SND_ASYNC);
	//load in the words
	char** wordslist = calloc(maxnumwords, sizeof(char*));
	int wordcount = 0;
	char* fiveword = malloc(6 * sizeof(char));
	FILE* wordsfile = fopen("C:\\Users\\ItsAl\\Desktop\\words.txt", "r");
	while (fscanf(wordsfile, "%s", fiveword) != EOF && wordcount < maxnumwords)
	{
		wordslist[wordcount] = fiveword;
		wordcount++;
		fiveword = malloc(6 * sizeof(char));
	}
	fclose(wordsfile);

	//pick a random word
	srand(time(NULL));
	char* answer = wordslist[rand() % wordcount];

	//start game
	int guessnum = 0, x = 0, score = 6;
	char* guess = malloc(6 * sizeof(char));
	char* name = malloc(51 * sizeof(char));
	while (guessnum < 6 && x != 1)
	{
		printf("Enter 5 letter word and press enter: ");
		scanf("%s", guess);
		printf("\nYou guessed the word: %s\n\n", guess);
		guessnum++;
		x = guess_check(answer, guess);
		score--;
	}
	if (x == 1)
	{
		score += 5;
		printf("\nYou have correctly guessed the word!\n", guessnum);
	}
	else
	{
		printf("\nYou ran out of guesses, the word was ");
		blue();
		printf("%s.\n", answer);
		reset();
	}
	struct Player player1;
	printf("Please enter your name to save your score:");
	scanf("%s", name);
	strcpy(player1.name, name);
	player1.score = score;
	printf("Name: %s | Score: %d", player1.name, player1.score);
	for (int i = 0;i < wordcount;i++)
	{
		free(wordslist[i]);
	}
	free(wordslist);
	free(fiveword);
	free(guess);
}