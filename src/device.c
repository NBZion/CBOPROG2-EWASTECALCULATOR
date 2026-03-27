#include <stdio.h>
#include <string.h>
#include "devices.h"

void initializeDevices(deviceInfo *d, FILE *devices, FILE *minerals,int *deviceCount)
{
    if (devices != NULL && minerals != NULL)
    {
        *deviceCount = 0;
        for (int i = 0; i < 100; i++)
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
            (*deviceCount)++;
        }
    }

}
