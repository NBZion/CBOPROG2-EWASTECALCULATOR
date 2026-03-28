#include <stdio.h>
#include <string.h>
#include "program.h"
#include "login.h"
#include "devices.h"

int getCurrentDeviceDatabase(UserDevice database[], int size, String user) {
    int found = -1;

    for(int i=0; i<size;i++) {
        if(strcmp(database[i].name, user) == 0) {
            found=i;
        }
    }
    return found;
}

void admin(User userDatabase[], deviceInfo deviceDatabase[], int *userDatabaseSize, int *deviceDatabaseSize) {
    int adminDecision;
    char running = 't';

    while(running == 't') {
        printf("Welcome Admin! What would you like to do?\n");
        printf("1 - Add User\n2 - Remove user\n3 - Edit User\n4 - Add Device to Info Database\n5 - Exit\n@admin - ");
        scanf("%d", &adminDecision);

        switch(adminDecision) {
            case 1:

            case 2:

            case 3:

            case 4:

            case 5:
        }
    }
}

void pLoop(User currentUser, User userDatabase[], int *userDatabaseSize)
{
    printf("Welcome %s!\n", currentUser.user);
    float accountValue;
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

    initializeDevices(devices, &deviceCount, fDevices, fMinerals);

    // Metal calculations
    for (int j = 0; j < deviceCount; j++)
    {
        calculateMinerals(&devices[j]);
    }

    // Load Device File to get current user

    loadDeviceFile(deviceDatabase, devices, deviceCount, &deviceDatabaseCount, fopen("devicedatabase.txt","r"));

    // Program Loop
    int deviceDecision;
    int currentUserIndex = getCurrentDeviceDatabase(deviceDatabase, deviceDatabaseCount, currentUser.user);
    UserDevice currentUserDevice = deviceDatabase[currentUserIndex];
    char running = 't';
    while(running == 't') {
        loadDeviceFile(deviceDatabase, devices, deviceCount, &deviceDatabaseCount, fopen("devicedatabase.txt","r"));
        // Maybe also add Device Dashboard here as print
        printf("You have %d Devices\nSelect one of the Following...\n1 - Add Device\n2 - Remove Device\n3 - View Inventory \n4 - Log Out\n", currentUserDevice.deviceCount);
        if(currentUser.admin == 't') {
            printf("5 - Admin\n");
        }
        printf("@ - ");
        scanf("%d", &deviceDecision);

        switch(deviceDecision) {
            case 1:
                addUserDevice(&currentUserDevice, devices, deviceCount);
                deviceDatabase[currentUserIndex] = currentUserDevice;
                saveDeviceFile(deviceDatabase, deviceDatabaseCount, fopen("devicedatabase.txt","w"));
                break;
            case 2:
                removeUserDevice(&currentUserDevice);
                deviceDatabase[currentUserIndex] = currentUserDevice;
                saveDeviceFile(deviceDatabase, deviceDatabaseCount, fopen("devicedatabase.txt","w"));
                break;
            case 3:
                // Actually show inventory using displayDevice
                accountValue = calculateProfile(&currentUserDevice, devices, deviceCount);
                printf("\n%.2f php inventory value.\n", accountValue); // Only for debugging, to be removed later when UI is implemented
                break;
            case 4:
                running = 'f';
                break;
            case 5:
                if(currentUser.admin == 't') {
                    admin(userDatabase,devices, userDatabaseSize, &deviceCount);
                }
                break;
        }
    }


}
