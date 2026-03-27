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

    if (fDevices != NULL && fMinerals != NULL)
    {
        for (int i = 0; i < 100; i++)
        {
            initializeDevices(&devices[i], fDevices, fMinerals);
        }
    }
    
    return;
}
