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

void saveDeviceFile(UserDevice database[], int *size, FILE *f) {
    if(f != NULL) {
        for(int i=0;i<*size;i++) {
            fprintf(f, "%s", database[i].name);

            for(int j=0; j < database[i].deviceCount; j++) {
                fprintf(f, ",%s", database[i].devices[j].deviceName);
            }

            fprintf(f,"\n");
        }

        fclose(f);
    }
}

void addUserDevice(UserDevice currentUser, deviceInfo infoDatabase[], int infoCount) {
    // List Current Devices to Pick
    for(int i=0; i<infoCount; i++) {
        printf("%d - %s | ", i, infoDatabase[i].deviceName);
        if((i%2) == 0 && i != 0)  printf("\n");
    }
}
