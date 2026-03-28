#ifndef PROGRAM_H
#define PROGRAM_H
#include "login.h"
#include "devices.h"

int getCurrentDeviceDatabase(UserDevice database[], int size, String user);
void admin(User userDatabase[], deviceInfo deviceDatabase[], int *userDatabaseSize, int *deviceDatabaseSize);
void pLoop(User currentUser, User userDatabase[], int *userDatabaseSize);

#endif
