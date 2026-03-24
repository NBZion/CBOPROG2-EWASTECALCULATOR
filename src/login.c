#include <stdio.h>
#include <string.h>
#include <type_traits>
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

}

void loadFile(User database[], int size, FILE *f) {

}

void run() {
    // Initialization
    User userDatabase[MAX_USER];
    int currentUserSize = 0;
    int loginInput;

    // Create File if doesn't exist
    FILE *fp = fopen("userdatabase.txt", "w");
    fclose(fp);

    // While Loop
    while(1) {

        scanf("%d", &loginInput);

        switch(loginInput) {
            case 1: //Login
                break;
            case 2: // Register
                break;
            case 3: // Reset Password
                break;
        }
    }
}
