# wordle-cs50
 A command-line word-guessing game that emulates a simplified version of Wordle from scratch. Following prompt from Harvard's CS50 course.

 ## Prerequisites

To play Wordle50, you need to have the following installed:

- `gcc` compiler

## Getting Started

1. Clone the repository or download the source code and text files.
2. Compile the code using the `gcc` compiler with the following command(s):
```
make wordle_cs50
```
or
```
gcc -o outputFile wordle_cs50.c
```
3. Run the game by executing the executable file:
```
./wordle_cs50 <wordsize>
```
Replace `<wordsize>` with the desired single number representing the length of the word that will be guessed (5, 6, 7, or 8).

## How to Play
1. You will be given 6 attempts to guess the target word that is trying to be guessed.
2. When asked by program, enter a word of the specified length (wordsize, established previously).
3. After each valid guess, the program will provide feedback by outputting the color-coded letters of the word you guess.
- A letter is green if it is in the target word and in the correct position (EXACT).
- A letter is yellow if it is in the target word but in the wrong position (CLOSE).
- A letter is red if it is not in the target word (WRONG).
  Using this feedback given you can narrow down potential guesses and get closer to target word.
4. Keep guessing until the 6th attempt is reached.
5. If you guess the target word within the given number of attempts, you win the game.
  Otherwise, you lose and the target word will be revealed to you.
- **target word** refers to the word that you are trying to guess in order to win the game.

## Custom Word Lists

The game uses word lists stored in text files (`5letterRandom.txt`, `6letterWords.txt`, `7letterWords.txt`, `8letterWords.txt`) that contain 1000 words each.
You can modify or replace these files to use your own word lists. 
Each word should be on a separate line, and the number of words in each file should remain the same.
Also make sure that each file contains only words of the specified length. (5, 6, 7, 8). 

## ANSI color codes
The program uses ANSI color codes of green, red, and yellow to color-code the letters.
Ensure that your terminal supports ANSI escape sequences for proper color rendering.

## Additional notes
I followed the prompt from Harvard's CS50 course, but I implemented what was required from scratch (including the text file handling) using C programming without the use of the CS50 library. 
- I implemented an improved form of input validation than what was asked.
- In the original prompt: if the user enters an invalid guess (wrong length or input is not a letter), the program will simply prompt the user to enter a
 word of the specified length again, without letting the user know why it did not accept the previous submission.
- In my version, if the user enters a word that is the wrong length, the program will let them know by outputting a message with a red background (for better visibility) and then the program will prompt the user again. This adjustment makes the game more user-friendly since the user will know what to correct when inputting a guess.

