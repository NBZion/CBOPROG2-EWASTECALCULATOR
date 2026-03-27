#include <stdio.h>
#include <string.h>
#include "program.h"
#include "login.h"
#include "devices.h"

void pLoop(User currentUser)
{
    printf("Welcome %s!\n", currentUser.user);

    UserDevice deviceDatabase[10];
    int deviceDatabaseCount;

    // Create devicedatabase.txt if doesn't exist
    if(fopen("devicedatabase.txt","r") == NULL) {
        fopen("devicedatabase.txt","w");
    }

    // Device initialization
    FILE *fDevices;
    FILE *fMinerals;
    fDevices = fopen("data/devices.txt", "r");
    fMinerals = fopen("data/minerals.txt", "r");

    deviceInfo devices[MAX_DEVICES];
    int deviceCount = 0;

    if(fDevices != NULL && fMinerals != NULL) {
        deviceCount=0;
        for(int i=0; i< 100; i++) {
            initializeDevices(&devices[i], fDevices, fMinerals);
            deviceCount++;
        }
    }
    // Put price for metal calculation here or on initializedevice

    loadDevice(deviceDatabase, devices, deviceCount, &deviceDatabaseCount, fopen("devicedatabase.txt","r"));


    return;
}
