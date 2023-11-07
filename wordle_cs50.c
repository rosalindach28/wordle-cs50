// command-line program that is similar to wordle
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

// each text file contains 1000 words
#define LISTSIZE 1000

// values for colors and score
// EXACT == right letter, right place
// CLOSE == right letter, wrong place; WRONG == wrong letter
#define EXACT 2 // green
#define CLOSE 1 // yellow
#define WRONG 0 // red

// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m" // resets color settings; no colorful background

bool isAlphabetical(const char *guess);
char *get_guess(int length);
char *get_target_word(const char *filename);
int get_score(char *userGuess, int length, int *wordStatus, char *target);
void print_word(char *userGuess, int length, int *wordStatus);

int main(int argc, char *argv[])
{
    int wordSize = atoi(argv[1]); // length of words user will guess; integer input as CLA
    char *targetWord;             // stores target word trying to be guessed
    int wordStatus[wordSize];     // stores scores for individual letters of each word guessed
    bool won = false;

    if (argc != 2)
    {
        printf("Usage error: exactly 2 command-line arguments needed");
        return 1; // indicates error
    }
    // user provides a command-line argument: the length of the word they want to guess
    // must be between 5 and 8 letters
    else if (wordSize < 5 || wordSize > 8)
    {
        printf("Error: length entered must be 5, 6, 7, or 8");
        return 1;
    }
    else
    {
        printf("\t" GREEN "This is WORDLE50" RESET);
        printf("\n\n\tRed letters are not in word.");
        printf("\n\tYellow letters are in word, but not in the right spot.");
        printf("\n\tGreen letters are in word and in correct spot.\n\n");
        printf("You have 6 tries to guess the %i-letter word I'm thinking of\n", wordSize);
        // establish word trying to be guessed before guessing
        if (wordSize == 5)
        {
            targetWord = get_target_word("5letterRandom.txt");
        }
        else if (wordSize == 6)
        {
            targetWord = get_target_word("6letterWords.txt");
        }
        else if (wordSize == 7)
        {
            targetWord = get_target_word("7letterWords.txt");
        }
        else if (wordSize == 8)
        {
            targetWord = get_target_word("8letterWords.txt");
        }

        for (int guessCount = 0; guessCount < 6; guessCount++)
        {
            // in c cannot initialize/ assign value to variable-sized array
            // wordStatus keeps track of scores
            // all elements in wordStatus array set to zero initially for every guess
            for (int j = 0; j < wordSize; j++)
            {
                wordStatus[j] = 0;
            }
            char *guessResult = get_guess(wordSize);
            printf("Guess %i: %s\n", guessCount + 1, guessResult);
            int totalScore = get_score(guessResult, wordSize, wordStatus, targetWord);
            print_word(guessResult, wordSize, wordStatus);
            free(guessResult);
            if (totalScore == EXACT * wordSize)
            {
                won = true;
                printf("You won!");
                break;
            }
            if (guessCount == 5 && won == false)
            {
                printf("Out of guesses, you lost.\n");
                printf("The word was: %s\n", targetWord);
            }
        }
        free(targetWord);
    }
} // end of main

// ensures user input consists of only alphabetical characters
bool isAlphabetical(const char *guess)
{
    while (*guess)
    {
        if (!isalpha(*guess))
        {
            return false;
        }
        guess++;
    }
    return true;
}
// make sure guess string is the correct length
char *get_guess(int length)
{
    char *wordGuess = malloc(10);
    char userGuess[10];
    printf("Input a %i letter word: ", length);
    scanf("%s", &userGuess);
    while (strlen(userGuess) != length)
    {
        printf(RED "Word is wrong length." RESET "\nInput a %i letter word: ", length);
        scanf("%s", &userGuess);
    }

    // makes sure user's guess is correct format
    // lowercase and all alphabetical characters
    for (int i = 0; i < length; i++)
    {
        if (!islower(userGuess[i]))
        {
            userGuess[i] = tolower(userGuess[i]);
        }
        else if (!isAlphabetical(userGuess))
        {
            printf(RED "Error: one or more characters is not a letter." RESET "\n");
            printf("Input a %i letter word: ", length);
            scanf("%s", &userGuess);
            while (strlen(userGuess) != length)
            {
                printf(RED "Word is wrong length." RESET "\nInput a %i letter word: ", length);
                scanf("%s", &userGuess);
            }
            if (!islower(userGuess[i]))
            {
                userGuess[i] = tolower(userGuess[i]);
            }
        }
    }
        strcpy(wordGuess, userGuess);
        return wordGuess;
} // end of function

    // read file and get word that user will be guessing
    char *get_target_word(const char *filename)
    {
        FILE *filePtr;

        // content is an an array of strings (2d array) where each element contains a word
        char content[LISTSIZE][10];
        char *target = malloc(10);

        // randomizes the list of words (array of strings)
        srand(time(NULL));
        int random = rand() % 1000;

        filePtr = fopen(filename, "r");
        if (filePtr != NULL)
        {
            for (int i = 0; i < LISTSIZE; i++)
            {
                fgets(content[i], LISTSIZE, filePtr); // read whole list of words
            }
            strcpy(target, content[random]); // assign random word as target word
                                             // printf("%s\n", target); // for testing purposes
            return target;
        }
        else
        {
            printf("Error, could not read file."); // could not read file
        }
    } // end of function

    /*
    get score based on letter position in GET_SCORE function
    check if character being guessed exists in the target word trying to be guessed
    if it exists, check whether it is in the correct/same position as in the target word
    score according to position and existence
    2 points if letter is in target word and correct position
    1 point if letter is in target word but wrong position
    no points if not in word
    store the scores for each letter in wordStatus array
    */
    int get_score(char *userGuess, int length, int *wordStatus, char *target)
    {
        int score = 0;
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                if (userGuess[i] == target[j]) // guess char is in target
                {

                    if (i == j) // same index/positon
                    {
                        score += EXACT;
                        wordStatus[i] = EXACT;
                        break; // once matching character in exact position found, moves onto the next
                    }
                    else // guess character is in different position
                    {
                        score += CLOSE;
                        wordStatus[i] = CLOSE;
                    }
                }
                else // guess char not in target
                {
                    score += WRONG;
                }
            } // end of inner for loop
        }
        return score;
    } // end of function

    /*
    print letters of guess in different colors according to their scores (stored in wordStatus[])
    letter is green if it is in the target word and in the correct position, worth 2 points
    letter is yellow if it is in the target word but wrong position, worth 1 point
    letter is red if not in the target word, worth 0 points
    */

    void print_word(char *userGuess, int length, int *wordStatus)
    {
        for (int i = 0; i < length; i++)
        {
            if (wordStatus[i] == 2)
            {
                printf(GREEN "%c" RESET, userGuess[i]);
            }
            else if (wordStatus[i] == 1)
            {
                printf(YELLOW "%c" RESET, userGuess[i]);
            }
            else
            {
                printf(RED "%c" RESET, userGuess[i]);
            }
        }
        printf("\n");
    }