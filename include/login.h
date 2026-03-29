#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>

/* Constants for string limits and database size */
#define STR_LEN 50
#define MAX_USER 10

/* Typedef for fixed-length strings used throughout the application */
typedef char String[STR_LEN] ;

/* Structure representing a user account and security credentials */
typedef struct {
    String user;           // Account username
    String password;       // Account password
    char admin;            // Privilege level: 't' for true (Admin), 'f' for false
    String securityAnswer; // Answer to security question (Favorite Color)
} User;

/* Function Prototypes for authentication and user administration */
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
