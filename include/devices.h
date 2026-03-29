#ifndef DEVICES_H
#define DEVICES_H

#include <stdio.h>
#include <login.h>

#define MAX_DEVICES 200     // There are 100 devices in the dataset, which means that the admin can only add up to 100 more devices

typedef struct mineralType
{
    float gold;
    float aluminum;
    float silver;
    float platinum;
    float rhodium;
    float nickel;
    float tin;
    float lithium;
}mineralType;

typedef struct deviceInfo
{
    char deviceName[51];    // Name of the device
    mineralType minerals;   // Minerals contained within the device
    float price;            // Calculated price of minerals contained within the device
}deviceInfo;

typedef struct {
    String name;
    deviceInfo devices[10];
    int deviceCount;
} UserDevice;

void initializeDevices(deviceInfo d[],int *devCount, FILE *devices, FILE *minerals);
void sortDevices(deviceInfo d[], int devCount);
void addInfoDevice(deviceInfo d[], int *devCount);
void displayProfile(float inventoryValue, float toxicityScore);
float calculateToxicity(UserDevice *p, deviceInfo infoDatabase[], int deviceCount);
void calculateMinerals(deviceInfo *d);
float calculateProfile(UserDevice *p, deviceInfo infoDatabase[], int deviceCount);
void loadDeviceFile(UserDevice database[], deviceInfo infoDatabase[],int infoCount,int *size, FILE *f);
void saveDeviceFile(UserDevice database[], int size, FILE *f);
int findDeviceIndex(deviceInfo info[], int infoCount, char *devName);
void fillDevice(UserDevice *userData, deviceInfo info[],int infoCount,int deviceIndex , char *deviceName);
void displayDevice(deviceInfo device);
void addUserDevice(UserDevice *currentUser, deviceInfo infoDatabase[], int infoCount);
void removeUserDevice(UserDevice *currentUser);
#endif
