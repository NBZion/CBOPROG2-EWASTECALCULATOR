#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>

#define STR_LEN 50
#define MAX_USER 10

typedef char String[STR_LEN] ;

typedef struct {
    String user;
    String password;
    char admin; // t if true f if false
    String securityAnswer;
} User;

int loginUser(User database[], int size);
void registerUser(User database[], int *size);
void resetUser(User database[], int size);
void removeUser(User database[], int *size);
void editUser(User database[], int size);
void displayUser(User user);
void saveFile(User database[], int size, FILE *f);
void loadFile(User database[], int *size, FILE *f);
void run();
#endif
