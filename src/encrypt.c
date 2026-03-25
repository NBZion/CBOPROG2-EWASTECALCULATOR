#include <string.h>
#include "encrypt.h"


// Vigenere Cipher
void encrypt(String destination, const String source) {
    int keyLen = (int)strlen(KEY);
    int i;

    for(i=0; source[i] != '\0'; i++) {
        destination[i] = (source[i] -33 + KEY[i % keyLen]) % 94 + 33;
    }

    destination[i] = '\0';
}

void decrypt(String destination, const String source) {
    int keyLen = (int)strlen(KEY);
    int i;

    for(i=0; source[i] != '\0'; i++) {
        destination[i] = (source[i] - 33 - KEY[i % keyLen] + 94) % 94 + 33;
    }

    destination[i] = '\0';
}
