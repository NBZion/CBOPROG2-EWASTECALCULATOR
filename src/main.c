#include "login.h"
#include "devices.c"
int main() {
    run();

    
    FILE *fDevices;
    FILE *fMinerals;
    fDevices = fopen("devices.txt", "r");
    fMinerals = fopen("minerals.txt", "r");

    deviceInfo devices[MAX_DEVICES];

    if (fDevices != NULL && fMinerals != NULL)
    {
        for (int i = 0; i < 100; i++)
        {
            initializeDevices(&devices[i], fDevices, fMinerals);   // Initializes the deviceName and mineralType for every element of devices[]
        }
    }
    
    

    return 0;
}
