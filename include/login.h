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
} User;

void saveFile(User database[], int size, FILE *f);
void loadFile(User database[], int *size, FILE *f);
void run();
#endif
