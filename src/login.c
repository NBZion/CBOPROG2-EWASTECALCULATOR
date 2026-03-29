#include <stdio.h>
#include <string.h>
#include "login.h"
#include "encrypt.h"
#include "program.h"

/* Authenticates a user by checking credentials against the provided database */
int loginUser(User database[], int size) {
    String userInput, passwordInput;
    int userIndex = -1;
    int correctPassword = 0;

    // UI for login prompt
    printf("\n-------------------- User Login --------------------");
    printf("\n\nUsername: ");
    scanf("%s", userInput);
    // Search for Username in the array
    for(int i=0; i<size; i++) {
        if(strcmp(database[i].user, userInput) == 0) {
            userIndex=i;
        }
    }

    /* If user exists, prompt for password and verify */
    if(userIndex != -1) {
        printf("Password: ");
        scanf("%s", passwordInput);

        if(strcmp(database[userIndex].password, passwordInput) == 0) {
            correctPassword=1;
        }else {
            printf("\nNOTICE: Incorrect password.\n");
        }
    }else {
        printf("\nNOTICE: Username not found.\n");
    }

    /* Return index if successful, otherwise -1 */
    if(correctPassword) {
        return userIndex;
    }else {
        return -1;
    }
}

/* Administrative function to delete a user account and update the file */
void removeUser(User database[], int *size) {
    int removeDecision;
    char removeConfirmation;
    // List existing Users
    for(int i=0; i<*size;i++) {
        printf("\n[%d] %s", i+1, database[i].user);
    }

    printf("\n\nWho would you like to remove?\n\nEnter user number: ");
    scanf("%d", &removeDecision);

    removeDecision--;
    printf("\nAre you sure you want to remove %s?\n", database[removeDecision].user);
    printf("\n[y] Yes");
    printf("\n[n] No\n");
    printf("\nEnter letter (lowercase): ");
    scanf(" %c", &removeConfirmation);

    /* Delete by shifting elements and decrementing the size counter */
    if(removeConfirmation == 'y') {
        for(int i=removeDecision; i<*size; i++) {
            if(i+1<*size) {
                database[i] = database[i+1];
            }
        }

        (*size)--;
    }

    saveFile(database, *size, fopen("userdatabase.txt", "w"));
}

/* Administrative function to modify existing user details (Admin status, passwords, etc) */
void editUser(User database[], int size) {
    int userDecision;
    int editDecision;
    String tempInput;
    char tempCInput;
    // List Users for selection
    printf("\n-------------------- User Database ---------------------\n");
    for(int i=0;i<size;i++) {
        printf("\n[%d] %s", i+1, database[i].user);
    }

    printf("\n\nEnter user number: ");
    scanf("%d", &userDecision);

    userDecision--;

    printf("\nWhat do you wanna edit?\n\n[1] Username\n[2] Password\n[3] Admin\n[4] Security Answer\n\nEnter number: ");
    scanf("%d", &editDecision);

    /* Switch based on which field needs to be updated */
    switch(editDecision) {
        case 1:
            printf("Input New Username: ");
            scanf("%s",tempInput);
            strcpy(database[userDecision].user, tempInput);
            break;
        case 2:
            printf("Input New Password: ");
            scanf("%s", tempInput);
            strcpy(database[userDecision].password, tempInput);
            break;
        case 3:
            printf("Input New Admin Status(t/f): ");
            scanf(" %c", &tempCInput);
            database[userDecision].admin = tempCInput;
            break;
        case 4:
            printf("Input New Security Answer(Color): ");
            scanf("%s", tempInput);
            strcpy(database[userDecision].securityAnswer, tempInput);
            break;
    }

    /* Commit changes to disk */
    saveFile(database, size, fopen("userdatabase.txt", "w"));
}

/* Debug/Admin helper to print raw user object data */
void displayUser(User user) {
    printf("User: %s\nPassword: %s\nAdmin: %c\nSecurity answer: %s\n", user.user, user.password, user.admin, user.securityAnswer);
}

/* Implements password recovery using the stored security answer */
void resetUser(User database[], int size) {
    String userInput, securityInput;
    int userIndex = -1;

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

        /* If security answer matches, allow password change */
        if(strcmp(database[userIndex].securityAnswer, securityInput) == 0) {
            printf("Input New Password: ");
            scanf("%s", securityInput);
            strcpy(database[userIndex].password, securityInput);
            printf("Password changed succesfully!\n");
            saveFile(database, size, fopen("userdatabase.txt", "w"));
        }else {
            printf("\nNOTICE: Incorrect Security\n");
        }
    }else {
        printf("\nNOTICE: Username Not Found\n");
    }
}

/* Creates a new user account and handles initial admin assignment */
void registerUser(User database[], int *size) {
    String userInput, passwordInput, securityInput;
    char foundUser = 'f';

    printf("\n------------------ User Register -------------------");
    printf("\n\nRegister username: ");
    scanf("%s", userInput);
    // Check if user already exists to prevent duplicates
    for(int i=0; i<*size; i++) {
        if(strcmp(userInput, database[i].user) == 0) {
            foundUser = 't';
        }
    }

    if(foundUser == 'f') {
        printf("Register password: ");
        scanf("%s", passwordInput);

        printf("\n(SECURITY) Enter your favorite color: ");
        scanf("%s", securityInput);

        // Update Database
        if(*size < 1) {
            /* The first user registered in the system is automatically an Admin */
            strcpy(database[0].user, userInput);
            strcpy(database[0].password, passwordInput);
            database[0].admin = 't';
            strcpy(database[0].securityAnswer, securityInput);
        }else {
            /* Subsequent users are standard users by default */
            strcpy(database[*size].user, userInput);
            strcpy(database[*size].password, passwordInput);
            database[*size].admin = 'f';
            strcpy(database[*size].securityAnswer, securityInput);
        }
        (*size)++;
        saveFile(database, *size, fopen("userdatabase.txt", "w"));
    }else {
        printf("\nNOTICE: User already Exists in Database!");
    }
}

/* Encrypts sensitive user data and writes it to the userdatabase.txt file */
void saveFile(User database[], int size, FILE *f) {
    String encryptedUser, encryptedPassword, encryptedSecurity;
    char encryptedAdmin;
    if(f != NULL) {
        for(int i=0; i<size; i++) {
            /* Encrypt strings using Vigenere Cipher */
            encrypt(encryptedUser, database[i].user);
            encrypt(encryptedPassword, database[i].password);
            /* Simple encryption for the single admin character */
            encryptedAdmin = (database[i].admin - 33 + KEY[0]) % 94 + 33;
            encrypt(encryptedSecurity, database[i].securityAnswer);
            fprintf(f, "%s %s %c %s\n", encryptedUser, encryptedPassword, encryptedAdmin, encryptedSecurity);
        }
        fclose(f);
    }
}

/* Reads encrypted data from the file and populates the runtime user database */
void loadFile(User database[], int *size, FILE *f) {
    *size=0;
    if(f != NULL) {
        String encryptedUser, encryptedPassword, encryptedSecurity;
        char encryptedAdmin;
        while(fscanf(f, "%s %s %c %s", encryptedUser, encryptedPassword, &encryptedAdmin, encryptedSecurity) != EOF){
            /* Decrypt data back to plaintext for runtime use */
            decrypt(database[*size].user, encryptedUser);
            decrypt(database[*size].password, encryptedPassword);
            database[*size].admin = (encryptedAdmin - 33 - KEY[0] + 94) % 94 + 33;
            decrypt(database[*size].securityAnswer, encryptedSecurity);
            (*size)++;
        }
        fclose(f);
    }
}

/* Main menu loop that manages initial program state (Login/Register/Reset) */
void run() {
    // Initialization of user data
    User userDatabase[MAX_USER];
    int currentUserCount = 0;
    int loginInput;
    int currentUser;
    char running = 't';

    // Create database file if it doesn't exist to prevent file pointer errors
    if(fopen("userdatabase.txt", "r") == NULL) {
        fopen("userdatabase.txt","w");
    }


    // While Loop for main entry screen
    while(running == 't') {
        // Refresh Database from file
        loadFile(userDatabase, &currentUserCount, fopen("userdatabase.txt", "r"));

        //UI for initial entry
        printf("\n------- E-Waste Salvage & Toxicity Predictor -------\n\n");
        printf("[1] Login\n[2] Register\n[3] Reset password\n[4] Exit\n\nEnter number: ");
        scanf("%d", &loginInput);

        switch(loginInput) {
            case 1: //Login
                currentUser = loginUser(userDatabase, currentUserCount);
                if(currentUser != -1) {
                    // Transition to main dashboard loop if login is successful
                    pLoop(userDatabase[currentUser],userDatabase, &currentUserCount);
                }
                break;
            case 2: // Register
                registerUser(userDatabase, &currentUserCount);
                break;
            case 3: // Reset Password
                resetUser(userDatabase, currentUserCount);
                break;
            case 4: // Exit the entire program
                running = 'f';
                break;
        }
    }
}
