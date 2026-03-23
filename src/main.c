#include <stdio.h>
#include <string.h>

/*
    Member 1 : Alphonso Cura
    Member 2 : Zion Tagle
    Section  : XC23
    Course   : CBPROG2
*/

#define MAX_DEVICES 200     // There are 100 devices in the dataset, which means that the admin can only add up to 100 more devices.

// --- Structure Declarations ---
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


// --- Function Prototypes ---
void initializeDevices(deviceInfo *d, FILE *devices, FILE *minerals);
void debug(deviceInfo *d);

// --- Functions ---
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

void debug(deviceInfo *d)   // Debug function, REMOVE THIS AFTER
{
    printf("%s %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f", d -> deviceName, 
                                                         d -> minerals.gold, 
                                                         d -> minerals.aluminum, 
                                                         d -> minerals.silver, 
                                                         d -> minerals.platinum, 
                                                         d -> minerals.rhodium, 
                                                         d -> minerals.nickel, 
                                                         d -> minerals.tin, 
                                                         d -> minerals.lithium);
}

int main()
{
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

    debug(&devices[20]);    // Helper function only for debugging, REMOVE AFTER
                            // Change index or whatever
}





