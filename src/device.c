#include <stdio.h>
#include <string.h>
#include "devices.h"

void initializeDevices(deviceInfo d[],int *deviceCount, FILE *devices, FILE *minerals)
{
    *deviceCount = 0;

    while(fscanf(minerals, "%f %f %f %f %f %f %f %f", &d[*deviceCount].minerals.gold, &d[*deviceCount].minerals.aluminum, &d[*deviceCount].minerals.silver,&d[*deviceCount].minerals.platinum, &d[*deviceCount].minerals.rhodium, &d[*deviceCount].minerals.nickel, &d[*deviceCount].minerals.tin, &d[*deviceCount].minerals.lithium) != EOF) {
        fgets(d[*deviceCount].deviceName, 51, devices);                                    // Scans for device names
        d[*deviceCount].deviceName[strcspn(d[*deviceCount].deviceName, "\n")] = '\0';                     // Replaces newlines with nullbytes
        (*deviceCount)++;
    }

}

void calculateMinerals(deviceInfo *d)
{
    float goldPrice, aluPrice, silPrice, platPrice, rhoPrice, nickPrice, tinPrice, lithPrice;
    float priceSum;

    goldPrice = d -> minerals.gold * 9753.76;
    aluPrice = d -> minerals.aluminum * 0.2;
    silPrice = d -> minerals.silver * 161.45;
    platPrice = d -> minerals.platinum * 4142.62;
    rhoPrice = d -> minerals.rhodium * 22294.77;
    nickPrice = d -> minerals.nickel * 1.04;
    tinPrice = d -> minerals.tin * 2.98;
    lithPrice = d -> minerals.lithium * 1.33;

    priceSum = goldPrice + aluPrice + silPrice + platPrice + rhoPrice + nickPrice + tinPrice + lithPrice;
    d -> price = priceSum;
}

int findDeviceIndex(deviceInfo info[], int infoCount, char *devName) {
    int found = -1;

    for(int i=0; i<infoCount; i++) {
        if(strcmp(info[i].deviceName, devName) == 0) {
            found=i;
        }
    }


    return found;
}

void fillDevice(UserDevice *userData, deviceInfo info[], int infoCount, int deviceIndex,char *deviceName) {
    // Find for Listed Device
    int infoDeviceIndex = findDeviceIndex(info, infoCount, deviceName);

    // Set Device Name
    strcpy(userData->devices[deviceIndex].deviceName, deviceName);
    // Set Minerals
    userData->devices[deviceIndex].minerals = info[infoDeviceIndex].minerals;

    // Set Price
    userData->devices[deviceIndex].price =  info[infoDeviceIndex].price;

}

void loadDeviceFile(UserDevice database[], deviceInfo infoDatabase[], int infoCount,int *size, FILE *f) {
    char buffer[512];
    int dCount;

    *size = 0;

    while(fgets(buffer, sizeof(buffer),f) != NULL) {

        char *token = strtok(buffer,",");

        strcpy(database[*size].name, token);

        dCount=0;

        while((token = strtok(NULL, ",\n")) != NULL) {
            fillDevice(&database[*size], infoDatabase, infoCount, dCount, token);
            dCount++;
        }

        database[*size].deviceCount = dCount;
        (*size)++;
    }

    fclose(f);
}

void saveDeviceFile(UserDevice database[], int size, FILE *f) {
    if(f != NULL) {
        for(int i=0;i<size;i++) {
            fprintf(f, "%s", database[i].name);

            for(int j=0; j < database[i].deviceCount; j++) {
                fprintf(f, ",%s", database[i].devices[j].deviceName);
            }

            fprintf(f,"\n");
        }

        fclose(f);
    }
}

void displayDevice(deviceInfo device)  {
    printf("INFORMATION\n");
    printf("Name: %s\n", device.deviceName);
    printf("Contained Minerals: \n");
    printf("Gold: %f \n", device.minerals.gold);
    printf("Aluminum: %f\n", device.minerals.aluminum);
    printf("Silver: %f\n", device.minerals.silver);
    printf("Platinum: %f\n",device.minerals.platinum);
    printf("Rhodium: %f\n",device.minerals.rhodium);
    printf("Nicket: %f\n",device.minerals.nickel);
    printf("Tin: %f\n",device.minerals.tin);
    printf("Lithium: %f\n", device.minerals.lithium);

    printf("\nPrice: %.2f\n", device.price);
}

void addUserDevice(UserDevice *currentUser, deviceInfo infoDatabase[], int infoCount) {
    int deviceDecision;
    // List Current Devices to Pick
    for(int i=0; i<infoCount; i++) {
        printf("%3d: %20.20s ", i+1, infoDatabase[i].deviceName);
        if(((i+1)%3) == 0)  printf("\n");
        else printf("| ");
    }
    printf("\n");

    printf("Pick a number(1-100) to pick a device to add to inventory...\n@add - ");
    scanf("%d", &deviceDecision);

    deviceDecision--;


    currentUser->devices[currentUser->deviceCount] = infoDatabase[deviceDecision];

    currentUser->deviceCount++;
}

void removeUserDevice(UserDevice *currentUser) {
    int deviceDecision;
    int deleteConfirmation;
    // List Current Devices in current User's device array
    for(int i=0; i<currentUser->deviceCount; i++) {
        printf("%3d: %20.20s ", i+1, currentUser->devices[i].deviceName);
        if(((i+1)%2) == 0)  printf("\n");
        else printf("| ");
    }

    printf("\n");
    scanf("%d", &deviceDecision);

    deviceDecision--;
    printf("Are you sure you want to remove %s?\n", currentUser->devices[deviceDecision].deviceName);
    displayDevice(currentUser->devices[deviceDecision]);
    scanf("%d", &deleteConfirmation);

    // "Remove" Device
    for(int i=deviceDecision; i<currentUser->deviceCount; i++) {
        if(i+1 < currentUser->deviceCount) {
            currentUser->devices[i] = currentUser->devices[i+1];
        }
    }

    currentUser->deviceCount--;

}
