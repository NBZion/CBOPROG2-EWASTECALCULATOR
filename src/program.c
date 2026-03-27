#include <stdio.h>
#include <string.h>
#include "program.h"
#include "login.h"
#include "devices.h"

void pLoop(User currentUser)
{
    printf("Welcome %s!\n", currentUser.user);

    // Device initialization
    FILE *fDevices;
    FILE *fMinerals;
    fDevices = fopen("data/devices.txt", "r");
    fMinerals = fopen("data/minerals.txt", "r");

    deviceInfo devices[MAX_DEVICES];
    int deviceCount = 0;
    initializeDevices(devices, fDevices, fMinerals, &deviceCount);

    return;
}
