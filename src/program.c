#include <stdio.h>
#include <string.h>
#include "program.h"
#include "login.h"
#include "devices.h"

/* Finds the location of a specific user's inventory record in the global user-device database */
int getCurrentDeviceDatabase(UserDevice database[], int size, String user) {
    int found = -1;

    for(int i=0; i<size;i++) {
        if(strcmp(database[i].name, user) == 0) {
            found=i;
        }
    }
    return found;
}

/* Administrative interface for managing the system's users and the global device definitions */
void admin(User userDatabase[], deviceInfo deviceDatabase[], int *userDatabaseSize, int *deviceDatabaseSize) {
    int adminDecision;
    char running = 't';

    while(running == 't') {

        // UI header
        printf("\n---------------- Admin Control -----------------");
        printf("\n\nWelcome Admin! What would you like to do?\n");
        printf("\n[1] Add User\n[2] Remove user\n[3] Edit User\n[4] Add Device to Info Database\n[5] Display User Database\n[6] Exit\n\nEnter number: ");

        scanf("%d", &adminDecision);

        /* Refresh user data before performing operations */
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
                /* Print details for every registered user */
                for(int i=0; i<*userDatabaseSize;i++)
                    displayUser(userDatabase[i]);
                break;
            case 6:
                running='f'; // Return to user dashboard
                break;
        }
    }
}

/* Primary loop for logged-in users to interact with their salvaged e-waste inventory */
void pLoop(User currentUser, User userDatabase[], int *userDatabaseSize)
{
    // Dashboard greeting
    printf("\n-------------------- Dashboard ---------------------");
    printf("\n\nWelcome %s!\n\n", currentUser.user);
    float accountValue, lithiumAverage;
    UserDevice deviceDatabase[10];
    int deviceDatabaseCount;

    // Ensure persistence file exists
    if(fopen("devicedatabase.txt","r") == NULL) {
        fopen("devicedatabase.txt","w");
    }

    // Load global device definitions and mineral data
    FILE *fDevices;
    FILE *fMinerals;
    fDevices = fopen("data/devices.txt", "r");
    fMinerals = fopen("data/minerals.txt", "r");

    deviceInfo devices[MAX_DEVICES];
    int deviceCount = 0;

    // Populate global device array and sort alphabetically
    initializeDevices(devices, &deviceCount, fDevices, fMinerals);
    sortDevices(devices, deviceCount);

    // Calculate the value of all devices in the global database
    for (int j = 0; j < deviceCount; j++)
    {
        calculateMinerals(&devices[j]);
    }

    // Load user inventories from file
    loadDeviceFile(deviceDatabase, devices, deviceCount, &deviceDatabaseCount, fopen("devicedatabase.txt","r"));

    // User Program Loop
    int deviceDecision;
    int currentUserIndex = getCurrentDeviceDatabase(deviceDatabase, deviceDatabaseCount, currentUser.user);
    UserDevice currentUserDevice = deviceDatabase[currentUserIndex];
    char running = 't';
    while(running == 't') {
        /* Reload files to ensure current state is displayed */
        loadDeviceFile(deviceDatabase, devices, deviceCount, &deviceDatabaseCount, fopen("devicedatabase.txt","r"));

        // Print Personal Inventory Summary
        printf("----------------------------------------------------\n");
        printf("\nYou have %d devices in your inventory!\n",currentUserDevice.deviceCount);
        printf("----------------- Current Devices -----------------\n");
        for(int i=0;i<currentUserDevice.deviceCount;i++) {
            printf("%s - %.2f php\n", currentUserDevice.devices[i].deviceName, currentUserDevice.devices[i].price);
        }
        printf("---------------------------------------------------\n");
        printf("Select one of the Following...\n\n[1] Add Device\n[2] Remove Device\n[3] View Inventory \n[4] Log Out\n");

        /* Restricted menu option for Admin accounts */
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
                /* Profile view: shows total value and toxicity analysis */
                accountValue = calculateProfile(&currentUserDevice, devices, deviceCount);
                lithiumAverage = calculateToxicity(&currentUserDevice, devices, deviceCount);
                displayProfile(accountValue, lithiumAverage);
                break;
            case 4:
                running = 'f'; // Logout and return to run() menu
                break;
            case 5:
                if(currentUser.admin == 't') {
                    admin(userDatabase,devices, userDatabaseSize, &deviceCount);
                }
                break;
        }
    }


}
