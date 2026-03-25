#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "login.h"

#define KEY "SEGFAULT"

int encrypt(String destination, const String source);
int decrypt(String destination, const String source);

#endif
