#include <stdio.h>
#include <string.h>
#include "login.h"
#include "encrypt.h"
#include "program.h"

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

void resetUser(User database[], int size) {
    String userInput, securityInput;
    int userIndex = -1;
    int correctSecurity = 0;

    printf("What is your Username?\n");
    scanf("%s", userInput);
    // Search for Username
    for(int i=0; i<size; i++) {
        if(strcmp(database[i].user, userInput) == 0) {
            userIndex=i;
        }
    }

    if(userIndex != -1) {
        printf("What is your Favorite Color?: ");
        scanf("%s", securityInput);

        if(strcmp(database[userIndex].securityAnswer, securityInput) == 0) {
            printf("Input New Password: ");
            scanf("%s", securityInput);
            strcpy(database[userIndex].password, securityInput);
            printf("Password changed succesfully!\n");
            saveFile(database, size, fopen("userdatabase.txt", "w"));
        }else {
            printf("Incorrect Security\n");
        }
    }else {
        printf("Username Not Found\n");
    }
}

void registerUser(User database[], int *size) {
    String userInput, passwordInput, securityInput;
    char foundUser = 'f';

    printf("Input New User: ");
    scanf("%s", userInput);
    // Check if user already Exists
    for(int i=0; i<*size; i++) {
        if(strcmp(userInput, database[i].user) == 0) {
            foundUser = 't';
        }
    }

    if(foundUser == 'f') {
        printf("Input New Password: ");
        scanf("%s", passwordInput);

        printf("What is your favorite color?(this will be used for the answer of the security question): ");
        scanf("%s", securityInput);

        // Update Database
        if(*size < 1) {
            strcpy(database[0].user, userInput);
            strcpy(database[0].password, passwordInput);
            database[0].admin = 'f';
            strcpy(database[0].securityAnswer, securityInput);
        }else {
            strcpy(database[*size].user, userInput);
            strcpy(database[*size].password, passwordInput);
            database[*size].admin = 'f';
            strcpy(database[*size].securityAnswer, securityInput);
        }
        (*size)++;
        saveFile(database, *size, fopen("userdatabase.txt", "w"));
    }else {
        printf("User already Exists in Database");
    }
}

void saveFile(User database[], int size, FILE *f) {
    String encryptedUser, encryptedPassword, encryptedSecurity;
    char encryptedAdmin;
    if(f != NULL) {
        for(int i=0; i<size; i++) {
            encrypt(encryptedUser, database[i].user);
            encrypt(encryptedPassword, database[i].password);
            encryptedAdmin = (database[i].admin - 33 + KEY[0]) % 94 + 33;
            encrypt(encryptedSecurity, database[i].securityAnswer);
            fprintf(f, "%s %s %c %s\n", encryptedUser, encryptedPassword, encryptedAdmin, encryptedSecurity);
        }
        fclose(f);
    }
}

void loadFile(User database[], int *size, FILE *f) {
    *size=0;
    if(f != NULL) {
        String encryptedUser, encryptedPassword, encryptedSecurity;
        char encryptedAdmin;
        while(fscanf(f, "%s %s %c %s", encryptedUser, encryptedPassword, &encryptedAdmin, encryptedSecurity) != EOF){
            decrypt(database[*size].user, encryptedUser);
            decrypt(database[*size].password, encryptedPassword);
            database[*size].admin = (encryptedAdmin - 33 - KEY[0] + 94) % 94 + 33;
            decrypt(database[*size].securityAnswer, encryptedSecurity);
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
    int currentUser;
    char running = 't';

    // Create File if doesn't exist
    if(fopen("userdatabase.txt", "r") == NULL) {
        fopen("userdatabase.txt","w");
    }


    // While Loop
    while(running == 't') {
        // Load Database
        loadFile(userDatabase, &currentUserCount, fopen("userdatabase.txt", "r"));

        scanf("%d", &loginInput);

        switch(loginInput) {
            case 1: //Login
                currentUser = loginUser(userDatabase, currentUserCount);
                if(currentUser != -1) {
                    // Transition to main program loop if user is logged in
                    pLoop(userDatabase[currentUser]);
                }
                break;
            case 2: // Register
                registerUser(userDatabase, &currentUserCount);
                break;
            case 3: // Reset Password
                resetUser(userDatabase, currentUserCount);
                break;
            case 4: // Exit
                running = 'f';
                break;
        }
    }
}
