//Dillon Janakus
//April 24 2025
//Purpose: Create a program which loads an unknown word from a file 
//and allows a user to guess letters until theentire word is guessed. 

#include <stdio.h>
#include <stdbool.h>

#define FILENAME "mystery.txt"

int getLen(char guess[]);
void convertLower(char word[]);
bool invChar(char guess[]);
bool correctGuess(char guess[], char word[]);
void checkLetter(int row, int column, char guesses[][6], char guess[], char word[]);
void checkPos(int row, int column, char guesses[][6], char word[]);
void printGuesses(int row, int column, char guesses[][6]);

int main(){

	FILE * fptr;
	
	char word[6], guess[99], guesses[12][6];
	int row = 12;
	int col = 6;
	int win = 0;
	
	fptr = fopen(FILENAME, "r");
	
	if(fptr == NULL){
		printf("File does not exist. Goodbye!\n");
		return 0;
	}
	
	fscanf(fptr, "%s", word);
	fclose(fptr);
	
	convertLower(word);

	int i = 0;
	
	while(i < 6 && win != 1){
		if(i == 5){
			printf("FINAL GUESS: ");
		}
		else{
			printf("GUESS %d! Enter your guess: ", i + 1);
		}
		scanf("%s", guess);
		
		while(getLen(guess) != 5){
			printf("Your guess must be 5 letters long.\n");
			printf("Please try again: ");
			scanf("%s", guess);
		}
		
		convertLower(guess);
		while(invChar(guess) == 1){
			printf("Your guess must contain only letters.\n");
			printf("Please try again: ");
			scanf("%s", guess);
		}
		
		printf("================================\n");
		
		if(correctGuess(guess, word) == 1){
			win = 1;
			if(i == 0){
				printf("        You won in %d guess!\n                GOATED!\n", i + 1);
			}
			else if(i == 1 || i == 2){
				printf("        You won in %d guesses!\n               AMAZING!\n", i + 1);
			}
			else{
				printf("        You won in %d guesses!\n                NICE!\n", i + 1);
			}
		}
		if(win == 0){
			checkLetter(i*2, col, guesses, guess, word);
			checkPos(i*2+1, col, guesses, word);
			printGuesses(i*2+1, col, guesses);
		}
		i++;
	}
	
	if(i == 6 && win == 0){
		printf("You lost, better luck next time!\n");
	}
	

return 0;
}

void convertLower(char word[]){
	int i = 0;
	while(word[i] != '\0'){
		if(word[i] > 64 && word[i] < 91){
			word[i] = word[i] + 32;
		}
		i++;
	}
}
int getLen(char guess[]){
	int i = 0;
	while(guess[i] != '\0'){
		i++;
	}
	
	return i;
}

bool invChar(char guess[]){
	int i = 0;
	while(guess[i] != '\0'){
		if(!(guess[i] > 96 && guess[i] < 123)){
			return 1;
		} 
		i++;
	}
	
	return 0;
}

bool correctGuess(char guess[], char word[]){
	int i = 0;
	bool same = 1;
	
	while(guess[i] != '\0'){
		if(guess[i] != word[i]){
			same = 0;
			break;
		}
		i++;
	}
	
	i = 0;
	if(same == 1){
		printf("                ");
		while(word[i] != '\0'){
			printf("%c", word[i] - 32);
			i++;
		}
		printf("\n");
	}
	
	return same;
}

void checkLetter(int row, int column, char guesses[][column], char guess[], char word[]){
	for(int x = 0; x < column - 1; x++){
		guesses[row + 1][x] = ' ';
		if(guess[x] == word[x]){
			guesses[row][x] = word[x] - 32;
		}
		else{
			guesses[row][x] = guess[x];
		}
	}
	
	guesses[row][column - 1] = '\0';
}

void checkPos(int row, int column, char guesses[][column], char word[]){
	int appEarly = 0;
	int inWord = 0;
	
	for(int i = 0; i < column - 1; i++){
		appEarly = 0;
		inWord = 0;
		for(int x = 0; x < column - 1; x++){
			if((guesses[row-1][i] == guesses[row-1][x]) && appEarly == 0 && x < i){
				guesses[row][i] = ' ';
				appEarly = 1;
			}
			if(guesses[row-1][i] == guesses[row-1][x] + 32){
				guesses[row][i] = ' ';
				inWord = 1;
			}
			if(appEarly == 0 && inWord == 0 && guesses[row-1][i] == word[x]){
				guesses[row][i] = '^';
			}
		}
	}
	
	guesses[row][column-1] = '\0';
}

void printGuesses(int row, int column, char guesses[][column]){
	int i = 0;
	
	while(i < row + 1){
		printf("%s\n", guesses[i]);
		i++;
	}
}


