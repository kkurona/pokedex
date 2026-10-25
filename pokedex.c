#include "pokedex.h"

// function to clear the console screen
void clearScreen() {
    // \e[1;1H moves the cursor to the top-left corner of the terminal
    // \e[2J clears the entire screen
    printf("\e[1;1H\e[2J"); 
}

// clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// function to display the main menu
void displayMenu() {
    printf("---------- Welcome to the Pokedex! ----------\n");
    printf("Please select an option:\n");
    printf("1. Add Entry\n");
    printf("2. Modify Entry\n");
    printf("3. Delete Entry\n");
    printf("4. Display all Entries\n");
    printf("5. Search Pokemon by Name\n");
    printf("6. Search Pokemon by Type\n");
    printf("7. Research Tasks\n");
    printf("8. Export\n");
    printf("9. Import\n");
    printf("10. Exit\n");
}

void emptyEntries() {
    printf("There are no entries.\n\n");
}

// select pokemon type function
void selectPokemonType(char *typeOutput, size_t maxLen, int allowKeepCurrent){
int choice = -1;

while (1) {
    printf("\n ----- Select Pokemon Type ----\n");
    printf("1: Grass\n");
    printf("2. Fire\n");
    printf("3. Water\n");
    printf("4. Electric\n");
    if (allowKeepCurrent) {
        printf ("0. Keep Current Type\n");
    }
    printf("Enter your choice: ");

    if (scanf("%d", &choice) == 1) {
        clearInputBuffer();

    if (choice == 1) {
        snprintf(typeOutput, maxLen, "Grass");
        break;
        } else if (choice == 2) {
            snprintf(typeOutput, maxLen, "Fire");
            break;
        } else if (choice == 3) {
            snprintf(typeOutput, maxLen, "Water");
            break;
        } else if (choice == 4) {
            snprintf(typeOutput, maxLen, "Electric");
            break;
        } else if (allowKeepCurrent && choice == 0) {
            break;
        }
        } else { 
            clearInputBuffer();
        }
        printf("Invalid choice! Select a valid option. \n");
    }
}

// function to add a new Pokemon entry
void addEntry(struct Pokemon pokedex[], int *count) {
    // check if the maximum number of entries has been reached
    if (*count >= MAX_POKEMON) {
        printf("Pokedex is full. Cannot add more entries.\n");
        return;
    }

    printf("---------- Add New Pokemon Entry (#%d) ----------\n", *count + 1);

    // get Pokemon Name
    printf("Enter Pokemon Name: ");
    if (fgets(pokedex[*count].name, sizeof(pokedex[*count].name), stdin) != NULL) {
        pokedex[*count].name[strcspn(pokedex[*count].name, "\n")] = '\0';
    }

    // get Pokemon Type
    selectPokemonType(pokedex[*count].type, sizeof(pokedex[*count].type), 0);

    // get Pokemon Description
    printf("Enter Pokemon Description: ");
    if (fgets(pokedex[*count].description, sizeof(pokedex[*count].description), stdin) != NULL) {
        pokedex[*count].description[strcspn(pokedex[*count].description, "\n")] = '\0';
    }

    (*count)++; // increment the count of entries

    printf("\n\nNew Pokemon entry added successfully!\n\n");
}

// function to modify an existing Pokemon entry
void modifyEntry(struct Pokemon pokedex[], int count) {
    if (count == 0) {
        emptyEntries();
        return;
    }

    displayEntries(pokedex, count);
    int index;

    // user input to modify entry
    printf("Enter the index of the Pokemon entry to modify (1 to %d): ", count);
    if (scanf("%d", &index) != 1) {
        clearInputBuffer();
        printf ("Invalid Input! Please enter a valid number.");
        return;
    }
    clearInputBuffer();

    char newName[20];
    char newDescription[50];

    // validate the index
    if (index < 1 || index > count) {
        printf("Invalid index. Please try again.\n");
        return;
    }

    // adjust for zero-based indexing
    index--;

    printf("Modifying Pokemon Entry #%d:\n", index + 1);
    printf("Current Name: %s\n", pokedex[index].name);
    printf("Current Type: %s\n", pokedex[index].type);
    printf("Current Description: %s\n", pokedex[index].description);

    // get new name from the user
    printf("Enter new Pokemon Name (or press Enter to keep current): ");
    if (fgets(newName, sizeof(newName), stdin) != NULL) {
        newName[strcspn(newName, "\n")] = '\0';
    }
    if (newName[0] != '\0') {
        snprintf(pokedex[index].name, sizeof(pokedex[index].name), "%s", newName);
    }

    //  get new type from the user
    selectPokemonType (pokedex[index].type, sizeof(pokedex[index].type), 1);

    // get new description from user
    printf("Enter new Pokemon Description (or press Enter to keep current): ");
    if (fgets(newDescription, sizeof(newDescription), stdin) != NULL) {
        newDescription[strcspn(newDescription, "\n")] = '\0';
    }
    if (newDescription[0] != '\0') {
        snprintf(pokedex[index].description, sizeof(pokedex[index].description), "%s", newDescription);
    }

    // notify it was a success
    printf("\nPokemon entry modified successfully!\n\n");
}

// delete entry
void deleteEntry(struct Pokemon pokedex[], int *count) {
    if (*count == 0) {
        emptyEntries();
        return;
    }

    displayEntries(pokedex, *count);

    int index;
    printf("Enter the index of the Pokemon entry to delete (1 to %d): ", *count);
    scanf("%d", &index);
    clearInputBuffer();

    // validate the index
    if (index < 1 || index > *count) {
        printf("Invalid index. Please try again.\n");
        return;
    }

    // adjust for zero-based indexing
    index--;

    // shift entries to remove the specified entry
    for (int i = index; i < *count - 1; i++) {
        pokedex[i] = pokedex[i + 1];
    }

    (*count)--; // decrement the count of entries

    printf("\nPokemon entry deleted successfully!\n\n");
}

// display Pokemon
void displayEntries(struct Pokemon pokedex[], int count) {
    if (count == 0) {
        emptyEntries();
        return;
    }

    printf("---------- Displaying All Pokemon Entries ----------\n");
    for (int i = 0; i < count; i++) {
        printf("Entry #%d:\n", i + 1);
        printf("Name: %s\n", pokedex[i].name);
        printf("Type: %s\n", pokedex[i].type);
        printf("Description: %s\n", pokedex[i].description);
        printf("----------------------------------------\n");
    }
}

// needle in a haystack comparison
int stristr(const char *searchString, const char *substring) {
    if (!*substring) return 1; // empty search string matches everything

    // string search system
    for (; *searchString != '\0'; searchString++) {
        if (tolower((unsigned char)*searchString) == tolower((unsigned char)*searchString)) {
            const char *h = searchString + 1;
            const char *n = substring + 1;

            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                h++;
                n++;
            }

            if (!*n) return 1; // reached end of needle: match found
        }
    }
    return 0; // substring not found
}

// case-insenstive string comparison
int caseInsensitiveCompare(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return 0; // Not equal
        }
        str1++;
        str2++;
    }
    return *str1 == *str2; // Equal if both ended
}

// search pokemon by name
void searchEntries(struct Pokemon pokedex[], int count) {
    char searchName[20];
    int foundCount = 0;

    if (count == 0) {
        emptyEntries();
        return;
    }

    // iterate through pokemon list to show user
    printf("\n----- Pokemon List -----\n");
    for (int i = 0; i < count; i++) {
        printf("%-15s %-20s\n", "Name:", pokedex[i].name);
    }
    printf("------------------------\n\n");

    while (1) {
        printf("Enter Pokemon name to search (or 'q' to exit): ");
        if (fgets(searchName, sizeof(searchName), stdin) == NULL) {
            break;
        }

        // strip trailing newline added by fgets
        searchName[strcspn(searchName, "\n")] = '\0';

        // check exit condition
        if (strcmp(searchName, "q") == 0 || strcmp(searchName, "exit") == 0) {
            printf("Exiting search...\n\n");
            break;
        }

        printf("\n================ Search Results ================\n");

        for (int i = 0; i < count; i++) {
            // check if searchName is a substring of pokedex[i].name
            if (stristr(pokedex[i].name, searchName)) {
                printf("Name:        %s\n", pokedex[i].name);
                printf("Type:        %s\n", pokedex[i].type);
                printf("Description: %s\n", pokedex[i].description);
                printf("-----------------------------------------------\n");
                foundCount++;
            }
        }

        if (foundCount == 0) {
            printf("No Pokemon found containing \"%s\".\n", searchName);
        } else {
            printf("Found %d matching Pokemon.\n", foundCount);
            foundCount = 0;
        }
        printf("===============================================\n\n");
    }
}

// search pokemon by type
void searchType(struct Pokemon pokedex[], int count) {
    int foundCount = 0;

    if (count == 0) {
        emptyEntries();
        return;
    }

    char targetType[20];
    printf("\n---------- Search Pokemon by Type ----------\n");
    selectPokemonType(targetType, sizeof(targetType), 1);

    // if user inputs 0; exit
    if (targetType[0] == '\0') {
        printf("Search canceled.\n\n");
        return;
    }
    
    printf("\n ----- Search Results for \"%s\" Type -----",targetType);

    for (int i = 0; i < count; i++) {
        if (strcmp(pokedex[i].type, targetType) == 0) {
            printf("\nEntry %d: \n", i + 1);
            printf("%-10s %-15s\n", "Name:", pokedex[i].name);
            printf("%-10s %-15s\n", "Type:", pokedex[i].type);
            printf("%-10s %-15s\n","Description:", pokedex[i].description);
            foundCount++;
        }
    }
    if (foundCount == 0) {
        printf("\nNo Pokemon found with type \"%s\". \n", targetType);
    } else {
        printf("\nTotal Pokemon found: %d\n",foundCount);
    }
    printf("\n---------------------------------------\n");
}

// export feature
void exportPokedex(struct Pokemon pokedex[], int count) {
    if (count == 0) {
        emptyEntries();
        return;
    }

    // open file name write only
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("\n Error! Could not open file \"%s\" for writing. \n\n", FILE_NAME);
        return;
    }
    
    //print into txt file
    if (count != 0){
        for (int i = 0; i < count; i++) {
            fprintf(file, "Name: %s\n", pokedex[i].name);
            fprintf(file, "Type: %s\n", pokedex[i].type);
            fprintf(file, "Description: %s\n", pokedex[i].description);
            fprintf(file, "Seen: %d\n", pokedex[i].seen);
            fprintf(file, "Caught: %d\n\n", pokedex[i].caught);
        }
    printf("\n Successfully exported %d entries to \"%s\"!\n\n", count, FILE_NAME);
    }
    fclose(file);
}

// import feature
void importPokedex (struct Pokemon pokedex[], int *count) {
    char fileName[100];
    char line[150];
    int importedCount = 0;

    // user input for file
    printf("\nEnter filename to import (Enter for default \"pokedex_data\"): ");
    if (fgets(fileName, sizeof(fileName), stdin) != NULL ) {
        fileName[strcspn(fileName, "\r\n")] = '\0';
    }

    // use default file if pressed enter
    if (fileName[0] == '\0') {
        snprintf(fileName, sizeof(fileName), "%s", FILE_NAME);
    }

    // open file name read only
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("\nError! Could not open file \"%s\". \n\n", fileName);
        return;
    }

    while (*count < MAX_POKEMON && fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';

        // read name 
        if (strncmp(line, "Name: ", 6) == 0) {
            snprintf(pokedex[*count].name, sizeof(pokedex[*count].name), "%s", line +6);

            //read type
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\r\n")] = '\0';
                if (strncmp(line, "Type: ", 6) == 0) {
                    snprintf(pokedex[*count].type, sizeof(pokedex[*count].type), "%s", line +6);
                }
            }
        
            // read description
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\r\n")] = '\0';
                if (strncmp(line, "Description: ", 13) == 0) {
                    snprintf(pokedex[*count].description, sizeof(pokedex[*count].description), "%s", line + 13);
                }
            }

            // read seen
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\r\n")] = '\0';
                if (strncmp(line, "Seen: ", 6) == 0) {
                    pokedex[*count].seen = atoi(line + 6);
                }
            }  

            // read caught
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\r\n")] = '\0';
                if (strncmp(line, "Caught: ", 8) == 0) {
                    pokedex[*count].caught = atoi(line + 8);
                }
            }

            (*count)++;
            importedCount++;
        }
    }

    fclose(file);
    printf("\nSuccesfully imported %d entries from \"%s\"!\n\n", importedCount, fileName);
}

// task menu for research
void researchTaskMenu(struct Pokemon pokedex[], int count) {
    if (count == 0) {
        emptyEntries();
        return;
    }

    // show menu and user choices
    int choice;
    while(1) {
        printf("\n---------- Research Task Menu ----------\n");
        printf("1. Review Research Task by Pokemon\n");
        printf("2. Review Research Task by Type\n");
        printf("3. Update Research Task\n");
        printf("4. Exit\n");
        printf("Enter Your Choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            clearScreen();
            printf("Invalid Input! Please Try Again.\n\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                clearScreen();
                reviewResearchPerPokemon(pokedex, count);
                break;
            case 2:
                clearScreen();
                reviewResearchPerTaskType(pokedex, count);
                break;
            case 3:
                clearScreen();
                updateResearchTask(pokedex,count);
                break;
            case 4:
                clearScreen();
                return;
            default:
            clearScreen();
            printf("Invalid Choice! Please Try Again. \n\n");
            break;
        }
    }
}

// review research by pokemon
void reviewResearchPerPokemon(struct Pokemon pokedex[], int count) {
    displayEntries(pokedex, count);
    
    // enter pokemon entry from 1 - 151
    int index;
    printf("Enter the Entry Number to View Research Tasks (1 to %d): ", count);
    if (scanf("%d", &index) != 1) {
        clearInputBuffer();
        printf("Invalid Input!\n\n");
        return;
    }
    clearInputBuffer();

    if (index  < 1 || index > count) {
        printf("Invalid Index.\n\n");
        return;
    }

    // decrement for struct 
    index--;

    // output
    printf("\n---------- Research Task Progress for %s ----------\n", pokedex[index].name);
    printf("%-10s %-15d\n", "Number Seen:", pokedex[index].seen);
    printf("%-10s %-15d\n", "Number Caught:", pokedex[index].caught);
    printf("---------------------------------------------------\n\n");
}

// review per task type
void reviewResearchPerTaskType(struct Pokemon pokedex[], int count) {
    // user enter choice
    int taskType;
    printf("Select Research Task Type: \n");
    printf("1. Seen\n");
    printf("2. Caught\n");
    printf("Enter Your Choice: ");

    // input validation
    if (scanf("%d", &taskType) != 1 || (taskType != 1 && taskType != 2) ) {
        clearInputBuffer();
        printf("Invalid Choice. Try Again. \n\n");
        return;
    }
    clearInputBuffer();

    // research task progress using unary operator
    printf("\n---------- Research Task Progress (%s) ----------\n", (taskType == 1) ? "Seen" : "Caught");
    int foundCount = 0;

    // for loop to iterate through the respective choice
    for (int i = 0; i < count; i++) {
        int val = (taskType == 1) ? pokedex[i].seen : pokedex[i].caught;
        if (val > 0) {
            printf("Entry #%d - %s: %d\n", i + 1, pokedex[i].name, val);
            foundCount++;
        }
    }

    // error if no match
    if (foundCount == 0) {
        printf("No match found.\n");
    } else {
        printf("\n---------- End of List ----------");
    }
}

// update research
void updateResearchTask(struct Pokemon pokedex[], int count) {
    // user inputs choice
    int taskType;
    printf("Select Research Task Type: \n");
    printf("1. Seen\n");
    printf("2. Caught\n");
    printf("Enter Your Choice: ");

    // input validation
    if (scanf("%d", &taskType) != 1 || (taskType != 1 && taskType != 2) ) {
        clearInputBuffer();
        printf("Invalid Choice. Try Again. \n\n");
        return;
    }
    clearInputBuffer();

    displayEntries(pokedex, count);

    // user inputs how much count to add to respective task type with input validation
    int index;
    printf("Enter Pokemon Entry Number (1 to %d): ", count);
    if (scanf("%d", &index) != 1 || index < 1 || index > count) {
        clearInputBuffer();
        printf("Invalid Entry Number Given. \n\n");
        return;
    }
    clearInputBuffer();

    // decrement for struct
    index--;

    // user inputs how much to add for respective task type
    int amount;
    printf("Enter Count to add for %s (%s): ", pokedex[index].name, (taskType == 1) ? "Seen" : "Caught");
    if (scanf("%d", &amount) != 1 || amount < 0) {
        clearInputBuffer();
        printf("Invalid Number. Must be Greater than 0.\n\n");
        return;
    }
    clearInputBuffer();

    // logic to add
    if (taskType == 1) {
        pokedex[index].seen += amount;
    } else { 
        if (pokedex[index].caught + amount > pokedex[index].seen) {
            printf("Caught Count Can Not be Greater than Seen Count!");
            return;
        }
        pokedex[index].caught += amount;
    }

    printf("\nResearch Task Updated!\n\n");
}