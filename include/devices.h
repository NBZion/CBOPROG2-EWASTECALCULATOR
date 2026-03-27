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
    String deviceName;    // Name of the device
    mineralType minerals;   // Minerals contained within the device
    float price;            // Calculated price of minerals contained within the device
}deviceInfo;

typedef struct {
    String name;
    deviceInfo devices[10];
    int deviceCount;
} UserDevice;

void initializeDevices(deviceInfo *d, FILE *devices, FILE *minerals, int *deviceCount);
void loadDevice(UserDevice database[], int *size, FILE *f);
void saveDevice(UserDevice database[], int *size, FILE *f);

#endif
