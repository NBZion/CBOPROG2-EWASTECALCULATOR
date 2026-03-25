#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "login.h"

#define KEY "SEGFAULT"

void encrypt(String destination, const String source);
void decrypt(String destination, const String source);

#endif
