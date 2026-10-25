#include "pokedex.h"

int main(void) {
    // variable declarations
    int choice;
    int count = 0;
    struct Pokemon pokedex[MAX_POKEMON];

    // clear the console screen
    clearScreen();

    // main loop to display menu and handle user input
    while (1) {
        // display the main menu
        displayMenu();
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        // switch statement to handle user choice
        switch (choice) {
        case 1:
            clearScreen();
            addEntry(pokedex, &count);
            break;
        case 2:
            clearScreen();
            modifyEntry(pokedex, count);
            break;
        case 3:
            clearScreen();
            deleteEntry(pokedex, &count);
            break;
        case 4: 
            clearScreen();
            displayEntries(pokedex, count);
            break;
        case 5:
            clearScreen();
            searchEntries(pokedex, count);
            break;
        case 6:
            clearScreen();
            searchType(pokedex, count);
            break;
        case 7:
            clearScreen();
            researchTaskMenu(pokedex, count);
            break;
        case 8:
            clearScreen();
            exportPokedex(pokedex, count);
            break;
        case 9:
            clearScreen();
            importPokedex(pokedex, &count);
            break;
        case 10:
            clearScreen();
            printf("Exiting the Pokedex. Goodbye!\n");
            return 0;
        default:
            clearScreen();
            printf("Invalid choice. Please try again.\n\n");
            break;
        }
    }
}