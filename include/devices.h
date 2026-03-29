#ifndef DEVICES_H
#define DEVICES_H

#include <stdio.h>
#include <login.h>

/* Maximum capacity for the global device database */
#define MAX_DEVICES 200     // There are 100 devices in the dataset, which means that the admin can only add up to 100 more devices

/* Structure to store the weights (in grams) of precious and industrial minerals in a device */
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

/* Structure representing a specific electronic device and its calculated value */
typedef struct deviceInfo
{
    char deviceName[51];    // Name of the device
    mineralType minerals;   // Minerals contained within the device
    float price;            // Calculated price of minerals contained within the device
}deviceInfo;

/* Structure to associate a user with their collection of salvaged devices */
typedef struct {
    String name;            // The username of the owner
    deviceInfo devices[10]; // List of devices in user's inventory (Max 10)
    int deviceCount;        // Current number of devices owned
} UserDevice;

/* Function Prototypes for device management and calculations */
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
