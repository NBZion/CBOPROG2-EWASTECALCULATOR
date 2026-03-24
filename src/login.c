#include <stdio.h>
#include <string.h>
#include "login.h"

#define STR_LEN 50
#define MAX_USER 10

typedef char String[STR_LEN] ;

typedef struct {
    String user;
    String password;
    char admin; // t if true f if false
} User;

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

void loadFile(User database[], int size, FILE *f) {

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
