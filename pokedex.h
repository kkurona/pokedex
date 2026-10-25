#ifndef POKEDEX_H
#define POKEDEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_POKEMON 151
#define FILE_NAME "pokedex_data.txt"

// ****************************************
//    Struct Definition for Pokemon Entry
// ****************************************
struct Pokemon {
    char name[20];
    char type[50];
    char description[50];
    int seen;
    int caught;
};
// ****************************************
//              Function Prototypes
// ****************************************

void clearScreen();
void clearInputBuffer();
void displayMenu();
void emptyEntries();
void selectPokemonType(char *typeOutput, size_t maxLen, int allowKeepCurrent);
void addEntry(struct Pokemon pokedex[], int *count);
void modifyEntry(struct Pokemon pokedex[], int count);
void deleteEntry(struct Pokemon pokedex[], int *count);
void displayEntries(struct Pokemon pokedex[], int count);
int stristr(const char *searchString, const char *substring);
int caseInsensitiveCompare(const char *str1, const char *str2);
void searchEntries(struct Pokemon pokedex[], int count);
void searchType(struct Pokemon pokedex[], int count);
void exportPokedex (struct Pokemon pokedex[], int count);
void importPokedex (struct Pokemon pokedex[], int *count);
void researchTaskMenu(struct Pokemon pokedex[], int count);
void reviewResearchPerPokemon(struct Pokemon pokedex[], int count);
void reviewResearchPerTaskType(struct Pokemon pokedex[], int count);
void updateResearchTask(struct Pokemon pokedex[], int count);

#endif