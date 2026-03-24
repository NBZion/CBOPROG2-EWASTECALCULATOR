#include <stdio.h>
#include <string.h>
#include "login.h"


// Returns 1 if Succesful, Returns 0 If Not
int loginUser() {

}

void registerUser() {

}

void saveFile(User database[], int size, FILE *f) {
    if(f != NULL) {
        for(int i=0; i<size; i++) {
            fprintf(f, "%s %s %c\n", database[i].user,database[i].password,database[i].admin);
        }

        fclose(f);
    }
}

void loadFile(User database[], int *size, FILE *f) {
    if(f != NULL) {
       while(fscanf(f, "%s %s %c", database[*size].user, database[*size].password, database[*size].admin) != EOF){
          (*size)++;
       }
    }
}

void run() {
    // Initialization
    User userDatabase[MAX_USER];
    int currentUserCount = 0;
    int loginInput;
    char running = 't';

    // Create File if doesn't exist
    FILE *fp = fopen("userdatabase.txt", "w");
    fclose(fp);

    // Load Database
    loadFile(userDatabase, &currentUserCount, fopen("userdatabase.txt", "r"));

    // While Loop
    while(running == 't') {

        scanf("%d", &loginInput);

        switch(loginInput) {
            case 1: //Login
                break;
            case 2: // Register
                break;
            case 3: // Reset Password
                break;
            case 4: // Exit
                break;
        }
    }
}
