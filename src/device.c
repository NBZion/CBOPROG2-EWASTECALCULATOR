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

// Sort Devices using Selection Sort
void sortDevices(deviceInfo d[], int devCount) {
    int min;
    deviceInfo temp;

    for(int i=0; i<devCount;i++) {
        min=i;
        for(int j=i+1; j< devCount; j++) {
            if(strcmp(d[j].deviceName, d[min].deviceName) < 0) {
                min=j;
            }
        }

        temp = d[i];
        d[i] = d[min];
        d[min] =  temp;
    }
}
void addInfoDevice(deviceInfo d[], int *devCount) {
    FILE *fDevices = fopen("data/devices.txt", "a");
    FILE *fMinerals = fopen("data/minerals.txt", "a");
    if(*devCount <= MAX_DEVICES) {

        if (fDevices == NULL || fMinerals == NULL) {
            printf("Error: Could not open database files for updating.\n");
        }else {

            // Get Device Name
            printf("Enter Device Name: ");
            getchar(); // Clear newline buffer from previous inputs
            fgets(d[*devCount].deviceName, 51, stdin);
            d[*devCount].deviceName[strcspn(d[*devCount].deviceName, "\n")] = '\0';

            // Get Mineral Composition
            printf("Enter mineral content (in grams):\n");
            printf("Gold     : "); scanf("%f", &d[*devCount].minerals.gold);
            printf("Aluminum : "); scanf("%f", &d[*devCount].minerals.aluminum);
            printf("Silver   : "); scanf("%f", &d[*devCount].minerals.silver);
            printf("Platinum : "); scanf("%f", &d[*devCount].minerals.platinum);
            printf("Rhodium  : "); scanf("%f", &d[*devCount].minerals.rhodium);
            printf("Nickel   : "); scanf("%f", &d[*devCount].minerals.nickel);
            printf("Tin      : "); scanf("%f", &d[*devCount].minerals.tin);
            printf("Lithium  : "); scanf("%f", &d[*devCount].minerals.lithium);

            // Calculate total price based on market rates
            calculateMinerals(&d[*devCount]);

            // Append name to devices.txt
            fprintf(fDevices, "\n%s", d[*devCount].deviceName);

            // Append values to minerals.txt using the space-separated format
            fprintf(fMinerals, "\n%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f",
                    d[*devCount].minerals.gold, d[*devCount].minerals.aluminum,
                    d[*devCount].minerals.silver, d[*devCount].minerals.platinum,
                    d[*devCount].minerals.rhodium, d[*devCount].minerals.nickel,
                    d[*devCount].minerals.tin, d[*devCount].minerals.lithium);

            printf("\nSuccessfully added '%s' (Value: $%.2f) to the system.\n",
                    d[*devCount].deviceName, d[*devCount].price);

            // Increment the global device counter
            (*devCount)++;

        }

    }else {
        printf("Error: Maximum device capacity reached. Cannot add more technology.\n");
    }

    fclose(fDevices);
    fclose(fMinerals);
}

float calculateProfile(UserDevice *p, deviceInfo infoDatabase[], int deviceCount)
{
    float accountValue;
    for (int i = 0; i < 10; i++) // Loops through each of the user's devices
    {
        for (int j = 0; j < deviceCount; j++) // Loops through the entire database of devices
        {
            if (strcmp(p -> devices[i].deviceName, infoDatabase[j].deviceName) == 0)
            {
                accountValue += infoDatabase[j].price;
            }
        }
    }

    return accountValue;
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
    printf("\n");
    printf("Displaying information for: %s\n\n", device.deviceName);
    printf("Gold     : %.2f g\n", device.minerals.gold);
    printf("Aluminum : %.2f g\n", device.minerals.aluminum);
    printf("Silver   : %.2f g\n", device.minerals.silver);
    printf("Platinum : %.2f g\n",device.minerals.platinum);
    printf("Rhodium  : %.2f g\n",device.minerals.rhodium);
    printf("Nicket   : %.2f g\n",device.minerals.nickel);
    printf("Tin      : %.2f g\n",device.minerals.tin);
    printf("Lithium  : %.2f g\n", device.minerals.lithium);
    printf("\nPrice    : %.2f php\n", device.price);
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

    printf("\nEnter device number: ");
    scanf("%d", &deviceDecision);

    deviceDecision--;


    currentUser->devices[currentUser->deviceCount] = infoDatabase[deviceDecision];

    currentUser->deviceCount++;
}

void removeUserDevice(UserDevice *currentUser) {
    int deviceDecision;
    char deleteConfirmation;
    // List Current Devices in current User's device array
    printf("\n-------------------- Device Removal ---------------------\n\n");
    for(int i=0; i<currentUser->deviceCount; i++) {
        printf("%3d: %20.20s ", i+1, currentUser->devices[i].deviceName);
        if(((i+1)%2) == 0)  printf("\n");
        else printf("| ");
    }

    printf("\n");
    printf("\nEnter device number: ");
    scanf("%d", &deviceDecision);

    deviceDecision--;
    displayDevice(currentUser->devices[deviceDecision]);
    printf("\nAre you sure you want to remove %s?\n", currentUser->devices[deviceDecision].deviceName);
    printf("\n[y] Yes ");
    printf("\n[n] No ");
    printf("\n\nEnter letter (lowercase): ");
    scanf(" %c", &deleteConfirmation);

    if(deleteConfirmation == 'y') {
        // "Remove" Device
        for(int i=deviceDecision; i<currentUser->deviceCount; i++) {
            if(i+1 < currentUser->deviceCount) {
                currentUser->devices[i] = currentUser->devices[i+1];
            }
        }

        currentUser->deviceCount--;
    }


}
