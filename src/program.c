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

        // UI
        printf("\n---------------- Admin Control -----------------");
        printf("\n\nWelcome Admin! What would you like to do?\n");
        printf("\n[1] Add User\n[2] Remove user\n[3] Edit User\n[4] Add Device to Info Database\n[5] Display User Database\n[6] Exit\n\nEnter number: ");

        scanf("%d", &adminDecision);

        loadFile(userDatabase, userDatabaseSize, fopen("userdatabase.txt", "r"));
        switch(adminDecision) {
            case 1:
                registerUser(userDatabase, userDatabaseSize);
                break;
            case 2:
                removeUser(userDatabase, userDatabaseSize);
                break;
            case 3:
                editUser(userDatabase, *userDatabaseSize);
                break;
            case 4:
                addInfoDevice(deviceDatabase, deviceDatabaseSize);
                break;
            case 5:
                for(int i=0; i<*userDatabaseSize;i++)
                    displayUser(userDatabase[i]);
                break;
            case 6:
                running='f';
                break;
        }
    }
}

void pLoop(User currentUser, User userDatabase[], int *userDatabaseSize)
{
    // UI
    printf("\n-------------------- Dashboard ---------------------");
    printf("\n\nWelcome %s!\n\n", currentUser.user);
    float accountValue, lithiumAverage;
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

    // Put contents of devices.txt and minerals.txt into struct
    initializeDevices(devices, &deviceCount, fDevices, fMinerals);
    // Sort Devices to make Selections in add, remove devices easier
    sortDevices(devices, deviceCount);

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
        printf("----------------------------------------------------\n");
        printf("\nYou have %d devices in your inventory!\n",currentUserDevice.deviceCount);
        printf("----------------- Current Devices -----------------\n");
        for(int i=0;i<currentUserDevice.deviceCount;i++) {
            printf("%s - %.2f php\n", currentUserDevice.devices[i].deviceName, currentUserDevice.devices[i].price);
        }
        printf("---------------------------------------------------\n");
        printf("Select one of the Following...\n\n[1] Add Device\n[2] Remove Device\n[3] View Inventory \n[4] Log Out\n");
        if(currentUser.admin == 't') {
            printf("[5] Admin\n");
        }
        printf("\nEnter number: ");
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
                accountValue = calculateProfile(&currentUserDevice, devices, deviceCount);
                lithiumAverage = calculateToxicity(&currentUserDevice, devices, deviceCount);
                displayProfile(accountValue, lithiumAverage);
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
