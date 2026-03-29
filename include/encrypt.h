#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "login.h"

/* Secret key used for the Vigenere Cipher encryption/decryption */
#define KEY "SEGFAULT"

/* Encrypts the source string into the destination buffer using the KEY */
void encrypt(String destination, const String source);

/* Decrypts the source string into the destination buffer using the KEY */
void decrypt(String destination, const String source);

#endif
