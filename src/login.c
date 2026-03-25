#include <stdio.h>
#include <string.h>
#include "login.h"


// Returns 1 if Succesful, Returns 0 If Not
int loginUser(User database[], int size) {
    String userInput, passwordInput;
    int userIndex = -1;
    int correctPassword = 0;

    printf("What is your Username?\n");
    scanf("%s", userInput);
    // Search for Username
    for(int i=0; i<size; i++) {
        if(strcmp(database[i].user, userInput) == 0) {
            userIndex=i;
        }
    }

    if(userIndex != -1) {
        printf("Password: ");
        scanf("%s", passwordInput);

        if(strcmp(database[userIndex].password, passwordInput) == 0) {
            correctPassword=1;
        }else {
            printf("Incorrect Password\n");
        }
    }else {
        printf("Username Not Found\n");
    }

    if(correctPassword) {
        return userIndex;
    }else {
        return -1;
    }
}

void registerUser(User database[], int *size) {
    String userInput, passwordInput;

    printf("Input New User: ");
    scanf("%s", userInput);
    printf("Input New Password: ");
    scanf("%s", passwordInput);

    // Update Database
    if(*size < 1) {
        strcpy(database[0].user, userInput);
        strcpy(database[0].password, passwordInput);
        database[0].admin = 'f';
    }else {
        strcpy(database[*size].user, userInput);
        strcpy(database[*size].password, passwordInput);
        database[*size].admin = 'f';
    }
    (*size)++;
    saveFile(database, *size, fopen("userdatabase.txt", "w"));
}

void saveFile(User database[], int size, FILE *f) {
    if(f != NULL) {
        for(int i=0; i<size; i++) {
            fprintf(f, "%s %s %c\n", database[i].user,database[i].password,database[i].admin); // Change Later to Encrypt
        }

        fclose(f);
    }
}

void loadFile(User database[], int *size, FILE *f) {
    if(f != NULL) {
       while(fscanf(f, "%s %s %c", database[*size].user, database[*size].password, &(database[*size].admin)) != EOF){ // Change Later to Decrypt
           (*size)++;
       }
       fclose(f);
    }
}

void run() {
    // Initialization
    User userDatabase[MAX_USER];
    int currentUserCount = 0;
    int loginInput;
    char running = 't';

    // Create File if doesn't exist
    if(fopen("userdatabase.txt", "r") == NULL) {
        fopen("userdatabase.txt","w");
    }

    // Load Database
    loadFile(userDatabase, &currentUserCount, fopen("userdatabase.txt", "r"));

    // While Loop
    while(running == 't') {

        scanf("%d", &loginInput);

        switch(loginInput) {
            case 1: //Login
                int currentUser = loginUser(userDatabase, currentUserCount);
                if(currentUser != -1) {
                    // Do Login Logic..
                }
                break;
            case 2: // Register
                registerUser(userDatabase, &currentUserCount);
                break;
            case 3: // Reset Password
                break;
            case 4: // Exit
                running = 'f';
                break;
        }
    }
}
