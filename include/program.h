#ifndef PROGRAM_H
#define PROGRAM_H
#include "login.h"
#include "devices.h"

int getCurrentDeviceDatabase(UserDevice database[], int size, String user);
void pLoop(User currentUser);

#endif
