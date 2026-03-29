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

    // UI 
    printf("\n-------------------- User Login --------------------");
    printf("\n\nUsername: ");
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
            printf("\nNOTICE: Incorrect password.\n");
        }
    }else {
        printf("\nNOTICE: Username not found.\n");
    }

    if(correctPassword) {
        return userIndex;
    }else {
        return -1;
    }
}

void removeUser(User database[], int *size) {
    int removeDecision;
    char removeConfirmation;
    // List Users
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

void editUser(User database[], int size) {
    int userDecision;
    int editDecision;
    String tempInput;
    char tempCInput;
    // List Users
    printf("\n-------------------- User Database ---------------------\n");
    for(int i=0;i<size;i++) {
        printf("\n[%d] %s", i+1, database[i].user);
    }

    printf("\n\nEnter user number: ");
    scanf("%d", &userDecision);

    userDecision--;

    printf("\nWhat do you wanna edit?\n\n[1] Username\n[2] Password\n[3] Admin\n[4] Security Answer\n\nEnter number: ");
    scanf("%d", &editDecision);

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

    saveFile(database, size, fopen("userdatabase.txt", "w"));
}

void displayUser(User user) {
    printf("User: %s\nPassword: %s\nAdmin: %c\nSecurity answer: %s\n", user.user, user.password, user.admin, user.securityAnswer);
}

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

void registerUser(User database[], int *size) {
    String userInput, passwordInput, securityInput;
    char foundUser = 'f';

    printf("\n------------------ User Register -------------------");
    printf("\n\nRegister username: ");
    scanf("%s", userInput);
    // Check if user already Exists
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
            strcpy(database[0].user, userInput);
            strcpy(database[0].password, passwordInput);
            database[0].admin = 't';
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
        printf("\nNOTICE: User already Exists in Database!");
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

        //UI
        printf("\n------- E-Waste Salvage & Toxicity Predictor -------\n\n");
        printf("[1] Login\n[2] Register\n[3] Reset password\n[4] Exit\n\nEnter number: ");
        scanf("%d", &loginInput);

        switch(loginInput) {
            case 1: //Login
                currentUser = loginUser(userDatabase, currentUserCount);
                if(currentUser != -1) {
                    // Transition to main program loop if user is logged in
                    pLoop(userDatabase[currentUser],userDatabase, &currentUserCount);
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
