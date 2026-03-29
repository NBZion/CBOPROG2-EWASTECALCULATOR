#ifndef PROGRAM_H
#define PROGRAM_H
#include "login.h"
#include "devices.h"

/* Returns the index of a user's device data within the UserDevice database array */
int getCurrentDeviceDatabase(UserDevice database[], int size, String user);

/* Entry point for administrative tools (User/Device database management) */
void admin(User userDatabase[], deviceInfo deviceDatabase[], int *userDatabaseSize, int *deviceDatabaseSize);

/* Main logic loop for logged-in users to manage their e-waste inventory */
void pLoop(User currentUser, User userDatabase[], int *userDatabaseSize);

#endif
