#ifndef DEVICES_H
#define DEVICES_H

#define MAX_DEVICES 200     // There are 100 devices in the dataset, which means that the admin can only add up to 100 more devices


void initializeDevices(deviceInfo *d, FILE *devices, FILE *minerals);

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

#endif