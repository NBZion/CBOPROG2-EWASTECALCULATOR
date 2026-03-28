#include <stdio.h>
#include <string.h>
#include "program.h"
#include "login.h"
#include "devices.h"

int getCurrentDeviceDatabase(UserDevice database[], int size, String user) {
    int found = -1;

    for(int i=0; i<size;i++) {
        if(strcmp(database[i].name, user) != 0) {
            found=i;
        }
    }

    return found;
}

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


    // Program Loop
    int deviceDecision;
    UserDevice currentUserDevice = deviceDatabase[getCurrentDeviceDatabase(deviceDatabase, deviceDatabaseCount, currentUser.user)];
    char running = 't';
    while(running == 't') {
        loadDeviceFile(deviceDatabase, devices, deviceCount, &deviceDatabaseCount, fopen("devicedatabase.txt","r"));
        // Maybe also add Device Dashboard here as print
        printf("You have %d Devices\nSelect one of the Following...\n1 - Add Device\n2 - Remove Device\n4 - Log Out\n", currentUserDevice.deviceCount);
        if(currentUser.admin == 't') {
            printf("5 - Admin\n");
        }
        printf("@ - ");
        scanf("%d", &deviceDecision);

        switch(deviceDecision) {
            case 1:

            case 2:

            case 3:

            case 4:
                running = 'f';
                break;
            case 5:
                if(currentUser.admin == 't') {

                }
                break;
        }
    }


}
