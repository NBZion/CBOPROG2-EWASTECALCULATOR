#include <stdio.h>
#include <string.h>
#include "program.h"
#include "login.h"

void pLoop(User currentUser)
{
    printf("Welcome %s!\n", currentUser.user);
    return;
}
