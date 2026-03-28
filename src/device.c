#include <stdio.h>
#include <string.h>
#include "devices.h"

void initializeDevices(deviceInfo *d, FILE *devices, FILE *minerals)
{
    fgets(d -> deviceName, 51, devices);                                    // Scans for device names
    d->deviceName[strcspn(d->deviceName, "\n")] = '\0';                     // Replaces newlines with nullbytes

    fscanf(minerals, "%f %f %f %f %f %f %f %f", &d -> minerals.gold,        // Scans for every mineralType
                                                &d -> minerals.aluminum,
                                                &d -> minerals.silver,
                                                &d -> minerals.platinum,
                                                &d -> minerals.rhodium,
                                                &d -> minerals.nickel,
                                                &d -> minerals.tin,
                                                &d -> minerals.lithium);
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

    while(fgets(buffer, sizeof(buffer),f) != NULL) {

        char *token = strtok(buffer,",");

        strcpy(database[*size].name, token);

        int dCount = 0;

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

            for(int j=0; j > database[i].deviceCount; j++) {
                fprintf(f, ",%s", database[i].devices[j].deviceName);
            }

            fprintf(f,"\n");
        }

        fclose(f);
    }
}
