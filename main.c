/*
 * main.c
 *
 *  Created on: Jun 15, 2015
 *      Author: dchiu
 */
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "stats.h"
#include "menu.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief Main function
 *
 * @param argc Ignore
 * @param argv Ignore
 * @return int
 */



int main(int argc, char *argv[]) {
	
	//Stores values of letter amounts
	int histogram[ALPHABET_SIZE];

	//Max number of letter present
	int maxNum = 0;

	//Makes sure the histogram values are empty
	for(int i = 0; i < ALPHABET_SIZE; i++){
		histogram[i] = 0;
	}

	//Stores input from user
	char userInput[MAX_INPUT_LEN];

	//Runs main loop
	bool done = false;

	//For knowing when strings can be expected
	bool inputtingStrings = true;

	//Values to store the total vowels and consinants
	double totalVowels = 0;
	double totalCons = 0; 

	//Prints the histogram
	void printHisto(int letters[ALPHABET_SIZE]){

		//Max represents the highest amount of letter
		for(int max = maxNum; max >= -1; max--){

			//Iterates through the whole alphabet
			for(int letter = 0; letter < ALPHABET_SIZE; letter++){
				if(max > 0){
					if(letters[letter] >= max){
						printf("* ");
					} else {
						printf("  ");
					}
					if(letter == ALPHABET_SIZE - 1){
						printf("\n");
					}
				} else if(max == 0) {
					printf("%c ", (letter + 97));
					if(letter == ALPHABET_SIZE - 1){
						printf("\n");
					}
				} else {
					printf("%d ", (letters[letter]));
				}
			}
		}
		printf("\n");
	}

	//Updates the letter amounts in histogram and total consinant and vowel values
	void updateFreq(char str[]){
		for(int i = 0; i < strlen(str); i++){
			
			//Ensures only lowercase values are looked at
			if(isalpha(tolower(str[i]))){
				if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'){
					totalVowels += 1;
				} else {
					totalCons += 1;
				}

				//Uses ascii values to add to the corresponding location in histogram
				int asciiVal = tolower(str[i]);				
				int pos = asciiVal - 97;
				histogram[pos]++;
				if(histogram[pos] > maxNum){
					maxNum = histogram[pos];
				}
			}
		}
	}

	printf("Enter Strings, # to stop");

	//Main loop
	while(!done){
		
		//Collects user input
		scanf("%s", userInput);

		//Updates the histogram and vowel/consinant values whenever a string is input if allowed
		if(inputtingStrings){
			updateFreq(userInput);
		}

		//Checks if the user has input a digit then responds accordingly
		if(isdigit(userInput[0])){

			//Displays percentages of vowels and consinants
			if(userInput[0] == '1'){
				int totalLetters = totalVowels + totalCons;
				double percentV = (totalVowels / totalLetters) * 100;
				double percentC = (totalCons / totalLetters) * 100;
				printf("Vowel-Consinant frequency: Vowel: %0.02f, Consinant: %0.02f\n", percentV, percentC);
				inputtingStrings = false;
			}
			
			//Displays the histogram of letter amounts
			else if(userInput[0] == '2'){
				printHisto(histogram);
				inputtingStrings = false;
			}

			//Allows strings to be input again
			else if(userInput[0] == '3'){
				inputtingStrings = true;
			}

			//Exits the program
			else if(userInput[0] == '4'){
				inputtingStrings = false;
				done = true;
			}

			//Displays menu options if strings are not being input
			getMenuOption();
		}
	}

	printf("Exiting...\n");
	return 0;
};


