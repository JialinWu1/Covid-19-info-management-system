/*
 * This file gives full implementation of a few functions and gives headers for the rest of the functions that you
 * are required to implement.
 * You may also find all of these functions as part of the TODO list
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "household.h"

// sorting function required for ranking of data
void sortSelection(LocationCountPair arr[], int arrSize){
    int min = 0, temp = 0;
    char tempStr[20];

    for (int i = 0; i < arrSize ; i++)
    {
        min = i;  // record the position of the smallest
        for (int j = i + 1; j < arrSize; j++)
        {
            // update min when finding a smaller element
            if (arr[j].count > arr[min].count)
                min = j;
        }
        // put the smallest element at position i
        temp = arr[i].count;
        arr[i].count = arr[min].count;
        arr[min].count = temp;
        strcpy(tempStr, arr[i].town);
        strcpy(arr[i].town, arr[min].town);
        strcpy(arr[min].town, tempStr);
    }
}
/**
 * This is a generic validation function that takes the upper bound of valid options up to 8 and returns 9 if the user
 * opts to go back to the previous menu instead of providing valid data. Therefore 9 should not be a valid choice!!
 * @param upperbound
 * @return
 */
int dataValidation(int upperbound){
    int n = 0, num;
    char temp[40];
    while (1)
    {
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%d", &num);
        if (num == 9) return num;
        else if(num >= 0 && num <= upperbound && n == 1) return num;
        else
        {
            printf("Invalid data, Enter an integer 0 through %d or enter 9 to go back to the main menu. Try again \n",upperbound );
            continue;
        }

    } //while loop ends
}// dataValidation function ends

// full implementation of regionMapping function is given as a sample to help write other matching functions, if required.
/**
 *
 * @param x Takes an integer representing a region
 * @return and returns the corresponding region's name
 */
char* regionMapping(int x)
{
    // Validate x to avoid out-of-bounds access
    if (x < 0 || x >= ARR_REGION_LEN)
    {
        return NULL;
    }
    // Return the town name based on the specified index
    return regionsArr[x];
}// ends regionMapping function
/**
 * Full implementation of the menu function is provided that implements entire main user interface of the application.
 * Students are required to implement various functions called in this menu.
 * A list of ToDos is also given for easier development
 * @param top of the list to be provided by reference.
 */
void menu(NodePtr* top)
{
    int optionTopLevel = 0;
    while (1)
    {
        // Display a menu to the user
        char temp[120];
        char option[120];
        int valid = 0;
        puts("Menu:");
        printf("Enter your choice to\n");
        printf("1. display households of a race\n");
        printf("2. display households of a region\n");
        printf("3. display households of a town\n");
        printf("4. display households of a region with a given minimum number of people tested positive for Covid-19\n");
        printf("5. display the regions town-wise ranking of number of people fully vaccinated positive for Covid-19\n");
        printf("6. add a record\n");
        puts("7. delete all records of a region, town and race triplet");
        puts("8. display updated data");
        puts("9. store data to a file");
        puts("10. display data from file");
        puts("0. to exit the program");
        scanf("%d", &optionTopLevel);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { } // input stream flushing

        if (optionTopLevel == 0)
        {
            printf("\nThank you");
            return;
        }
        else if (optionTopLevel > 10)
        {
            printf("Invalid selection, enter an integer 0 through 10, try again\n");
            continue;
        }
        int regionOption = 0, townOption = 0, raceOption = 0, numberTested, numberTestedPos;
        char filename[120] = "..//data//";
        char strTemp[120];
        switch( optionTopLevel) {
            case 1:
                puts("Enter an integer for race: CAUCASIAN (0), INDIGENOUS(1), AFRO AMERICAN(2), ASIAN(3), and OTHER(4)");
                if((raceOption=dataValidation(4)) == 9 ) break;
                displayRecordsOfOneRace(*top, raceMapping(raceOption));
                break;
            case 2:
                puts("Enter an integer for region: Durham (0), Peel(1), and York(2):");
                if((regionOption=dataValidation(2)) == 9 ) break;
                displayRecordsOfOneRegion(*top, regionMapping(regionOption));
                break;
            case 3:
                puts("Enter an integer for town: OSHAWA(0), WHITBY(1), BRAMPTON(2), MISSISSAUGA(3), MAPLE(4) and VAUGHAN(5)");
                if((townOption=dataValidation(5)) == 9 ) break;
                displayRecordsOfOneTown(*top, townMapping(townOption));
                break;
            case 4:
                puts("Enter an integer for region: Durham (0), Peel(1), and York(2):");
                if((regionOption=dataValidation(2)) == 9 ) break;
                while(valid != 1) {
                    puts("Enter lowerbound of number of Covid-19 positive cases per household in the region\n");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &numberTestedPos);
                    if (numberTestedPos <= 0) {
                        puts("Invalid data, enter a positive integer, try again");
                        continue;
                    }
                    else valid = 1; // setting valid flag
                }
                valid = 0; // resetting valid flag for next iteration
                displayRecordsOfRegionWithPositiveCases(*top, regionMapping(regionOption), numberTestedPos);
                break;
            case 5:
                regionsTownWiseRankingVaccinated(*top);
                break;
            case 6:
                addNode(top, userInteractionForRecordAddition());
                printf("\nUpdated list after adding the new record:\n");
                printList(*top);
                break;
            case 7:
                puts("Enter region: 0 for Durham, 1 for Peel, 2 for York");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &regionOption);
                if(regionOption == 0){
                    puts("Enter town: 0 for Oshawa, 1 for Whitby");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                }
                else if(regionOption == 1){
                    puts("Enter town: 0 for Brampton, 1 for Mississauga");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                }
                else {
                    puts("Enter town: 0 for Maple, 1 for Vaughan");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                }
                puts("Enter race");
                puts("Enter 0 for Caucasian, 1 for indigenous, 2 for African_American, 3 for Asian, 4 for Other");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &raceOption);
                deleteNodesGivenCriteria(top, regionMapping(regionOption), townMappingRegionBased(regionOption, townOption),
                                         raceMapping(raceOption));
                printf("\nUpdated list after delete all records of a region, town and race triplet:\n");
                printList(*top);
                break;
            case 8:
                printList(*top);
                break;
            case 9:
                puts("Enter file name with extension, for example clients.txt");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%s", strTemp);
                writeListToFile(*top, strcat(filename, strTemp));
                break;
            case 10:
                puts("Enter file name with extension, for example clients.txt");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%s", strTemp);
                displayRecordsFromFile(strcat(filename, strTemp));
                break;
            default:
                puts("Invalid option");
        } // switch block ends here

    } // while loop ends

}// menus function ends
/**
 * This function takes region integer and town integer, town integer actually represents its town number within that region
 * So if there are three towns in a region, town number 0 corresponds to the first town in that region.
 * Read the header file and carefully go through the ordering of elements of regionArr and townArr. regionArr's elements
 * are in alphabetical order, but try to figure out what is the order of townArr elements?
 * @param region an integer value representing a region
 * @param x representing index value from townsArr array (refer to the header file)
 * @return
 */
char* townMappingRegionBased(int region, int x)
{
    //TODO 10 implement townMappingRegionBased function

    // Validate region and x to avoid out-of-bounds access
    if (region < 0 || region >= ARR_REGION_LEN ||
             x < 0 || x >= (ARR_TOWN_LEN / ARR_REGION_LEN))
    {
        return NULL;
    }
    // Determine the actual town number within the specified region
    int townNumber = region * (ARR_TOWN_LEN / ARR_REGION_LEN) + x;
    // Return the town name based on the determined town number
    return townsArr[townNumber];
}// ends townMappingRegionBased function
/**
 * This is a simple mapping function, just like regionMapping function
 * @param x is an integer corresponding to the townArr index
 * @return char array representing name of the town
 */
char* townMapping(int x)
{
    //TODO 11 implement townMapping function

    // Validate x to avoid out-of-bounds access
    if (x < 0 || x >= ARR_TOWN_LEN)
    {
        return NULL;
    }
    // Return the town name based on the specified index
    return townsArr[x];
}// ends townMapping function
/**
 *
 * @param x
 * @return
 */
char* raceMapping(int x)
{
    //TODO 12 implement raceMapping function

    // Validate x to avoid out-of-bounds access
    if (x < 0 || x >= ARR_RACE_LEN)
    {
        return NULL;
    }
    // Return the town name based on the specified index
    return racesArr[x];
}// ends raceMapping function
/**
 * It populates the linked list with valid random data. The top of the list is passed as a reference i.e. address of the pointer!
 * @param top top is passed by reference i.e. address of the pointer top is passed in the call!
 */
void initializeData(NodePtr* top) {
    // This function populates the linked list with random data.
    // TODO 01: Implement initializeData function.
    for(int i = 0; i < SIZE; i++)
    {
        //Allocate Memory for a New Node:
        NodePtr householdPtr = malloc(sizeof(*householdPtr));

        // Check if memory allocation is successful
        if (householdPtr == NULL)
        {
            puts("Memory allocation failure");
        }

        //generate random race, region and town index for the new node
        int raceIndex = rand() % ARR_RACE_LEN;
        int regionIndex = rand() % ARR_REGION_LEN;
        int townIndex = rand() % (ARR_TOWN_LEN / ARR_REGION_LEN); //the first town in a region is index 0

        //populate the household data
        strcpy(householdPtr->data.race, racesArr[raceIndex]);
        strcpy(householdPtr->data.region, regionsArr[regionIndex]);
        strcpy(householdPtr->data.town,townMappingRegionBased(regionIndex, townIndex));

        //generate random family size between 1 and 11
        householdPtr->data.familySize = rand() % 10 + 2;
        //generate random fully vaccinated number of people, not more than familySize
        householdPtr->data.fullyVaccinated = rand() % (householdPtr->data.familySize + 1);
        //generate random tested positive number of people, not more than familySize
        householdPtr->data.testedPositive = rand() % (householdPtr->data.familySize + 1);

        // Set the next pointer of the new node to the current top
        householdPtr->next = *top;

        // Update the top to point to the new node
        *top = householdPtr;
    }
} //initializeData ends
/**
 *
 * @param top is the top of the list
 * @param region is the region that all the displayed records should belong to
 */
void displayRecordsOfOneRegion(NodePtr top, char region[])
{
    // TODO 02: implement displayRecordsOfOneRegion function
    printf("%4s%5s%17s%22s%14s%7s%12s\n", "S.No", "Size", "Total Vaccinated","Total tested positive", "Race", "Region", "Town");;
    int ctr = 0;

    // Traverse the linked list
    NodePtr current = top;
    while (current != NULL)
    {
        // Check if the record belongs to the specified region
        if (strcmp(current->data.region, region) == 0)
        {
            printf("%4d%5d%17d%22d%14s%7s%12s\n",
                   (ctr)++,                         //S.no
                   current->data.familySize,        //"Size"
                   current->data.fullyVaccinated,   //"Total Vaccinated"
                   current->data.fullyVaccinated,   // "Total tested positive",
                   current->data.race,              // "Race",
                   current->data.region,            // "Region",
                   current->data.town);             // "Town");
        }
        // Move to the next node
        current = current->next;
    }
} //ends displayRecordsOfOneRegion
/**
 *
 * @param top
 * @param town
 */
void displayRecordsOfOneTown(NodePtr top, char town[])
{
    // TODO 03: implement displayRecordsOfOneTown function
    int ctr = 1;
    printf("%4s%5s%17s%22s%14s%7s%12s\n",
           "S.No", "Size", "Total Vaccinated","Total tested positive", "Race", "Region", "Town");
    // Traverse the linked list
    NodePtr current = top;
    while (current != NULL)
    {
        // Check if the record belongs to the specified town
        if (strcmp(current->data.town, town) == 0)
        {
            // Display the record
            printf("%4d%5d%17d%22d%14s%7s%12s\n",
                   (ctr)++,                       //S.no
                   current->data.familySize,      //"Size"
                   current->data.fullyVaccinated, //"Total Vaccinated"
                   current->data.fullyVaccinated, // "Total tested positive",
                   current->data.race,            // "Race",
                   current->data.region,          // "Region",
                   current->data.town);           // "Town");
        }
        // Move to the next node
        current = current->next;
    }
} //ends displayRecordsOfOneTown
/**
 *
 * @param top
 * @param race
 */
void displayRecordsOfOneRace(NodePtr top, char race[])
{
    // TODO 04: implement displayRecordsOfOneRace function
    int ctr = 1;
    printf("%4s%5s%17s%22s%14s%7s%12s\n",
           "S.No", "Size", "Total Vaccinated","Total tested positive", "Race", "Region", "Town");
    // Traverse the linked list
    NodePtr current = top;
    while (current != NULL)
    {
        // Check if the record belongs to the specified race
        if (strcmp(current->data.race, race) == 0)
        {
            // Display the record
            printf("%4d%5d%17d%22d%14s%7s%12s\n",
                   (ctr)++,                       //S.no
                   current->data.familySize,      //"Size"
                   current->data.fullyVaccinated, //"Total Vaccinated"
                   current->data.fullyVaccinated, // "Total tested positive",
                   current->data.race,            // "Race",
                   current->data.region,          // "Region",
                   current->data.town);           // "Town");
        }
        // Move to the next node
        current = current->next;
    }
} //ends displayRecordsOfOneTown
/**
 *
 * @param top
 * @param region
 * @param numOfPositiveCases
 */
void displayRecordsOfRegionWithPositiveCases(NodePtr top, char region[], int numOfPositiveCases)
{
    // TODO 05: implement displayRecordsOfRegionWithPositiveCases function
    int ctr = 1;  // Serial number counter
    NodePtr current = top;
    printf("%4s%5s%17s%22s%14s%7s%12s\n",
           "S.No", "Size", "Total Vaccinated","Total tested positive", "Race", "Region", "Town");
    // Traverse the linked list
    while (current != NULL) {
        // Check if the record belongs to the specified region and has lower bound of positive cases
        if (strcmp(current->data.region, region) == 0 &&
            (current->data.testedPositive) > numOfPositiveCases )
        {
            // Display the record
            printf("%4d%5d%17d%22d%14s%7s%12s\n",
                   ctr++,                          // Serial number
                   current->data.familySize,       //"Size"
                   current->data.fullyVaccinated, //"Total Vaccinated"
                   current->data.testedPositive,   // "Total tested positive",
                   current->data.race,             // "Race",
                   current->data.region,           // "Region",
                   current->data.town);            // "Town");
        }
        // Move to the next node
        current = current->next;
    }
}
/**
 * This function ranks all the towns in descending order of total number of people vaccinated
 * @param top
 */
void regionsTownWiseRankingVaccinated(NodePtr top)
{
    // TODO 06: implement regionsTownWiseRankingVaccinated function
    // Initialize arrays to store counts for each region and town
    int regionCounts[ARR_REGION_LEN] = {0};
    int townCounts[ARR_TOWN_LEN] = {0};
    // Traverse the linked list to count vaccinated people in each region and town
    NodePtr current = top;
    while (current != NULL)
    {
        // Find the index of the region in regionsArr
        int regionIndex = -1;
        for (int i = 0; i < ARR_REGION_LEN; ++i)
        {
            if (strcmp(current->data.region, regionsArr[i]) == 0)
            {
                regionIndex = i;
                break;
            }
        }
        // Update the count for the corresponding region
        if (regionIndex != -1)
        {
            regionCounts[regionIndex] += current->data.fullyVaccinated;
        }
        // Find the index of the town in townsArr
        int townIndex = -1;
        for (int i = 0; i < ARR_TOWN_LEN; ++i)
        {
            if (strcmp(current->data.town, townsArr[i]) == 0)
            {
                townIndex = i;
                break;
            }
        }
        // Update the count for the corresponding town
        if (townIndex != -1)
        {
            townCounts[townIndex] += current->data.fullyVaccinated;
        }
        // Move to the next node
        current = current->next;
    }//end of while loop

    // Create an array of LocationCountPair to hold counts and towns
    LocationCountPair townCountsArray[ARR_TOWN_LEN];
    for (int i = 0; i < ARR_TOWN_LEN; ++i)
    {
        strcpy(townCountsArray[i].town, townsArr[i]);
        townCountsArray[i].count = townCounts[i];
    }

    // Sort the array in descending order using the sortSelection method
    sortSelection(townCountsArray, ARR_TOWN_LEN);

    // Create an array of LocationCountPair to hold counts and regions
    LocationCountPair regionCountsArray[ARR_REGION_LEN];
    for (int i = 0; i < ARR_REGION_LEN; ++i)
    {
        strcpy(regionCountsArray[i].town, regionsArr[i]);
        regionCountsArray[i].count = regionCounts[i];
    }

    // Sort the array in descending order using the  sortSelection method
    sortSelection(regionCountsArray, ARR_REGION_LEN);

    // Print the header
    printf("Total vaccinated:\n");
    printf("Region-wise ranking:\n");

    // Print region-wise ranking
    for (int i = 0; i < ARR_REGION_LEN; ++i)
    {
        printf("\t%s: %d\n", regionCountsArray[i].town, regionCountsArray[i].count);
    }

    // Print town-wise ranking
    printf("Town-wise ranking:\n");
    for (int i = 0; i < ARR_TOWN_LEN; ++i)
    {
        printf("\t%s: %d\n", townCountsArray[i].town, townCountsArray[i].count);
    }
} // function regionsTownWiseRankingVaccinated ends
/**
 * This function gets validated data from the user for adding a record and then invokes makeHousehold function as part
 * of the return statement
 * @return  it returns a household instance that this function creates based on validated user input
 */
Household userInteractionForRecordAddition()
{
    // TODO 07: implement userInteractionForRecordAddition function
    char race[RACE_NAME_LEN];
    char region[REGION_NAME_LEN];
    char town[TOWN_NAME_LEN];
    int householdSize, vaccinatedNumber, positiveNumber, raceChoice, regionChoice, townChoice;

    // Get region from the user
    while(1)
    {
        puts("Enter region: 0 for Durham, 1 for Peel, 2 for York");
        scanf("%d", &regionChoice);
        //printf("DEBUG: After scanf - regionChoice: %d\n", regionChoice);
        if (regionChoice < 0 || regionChoice > 2) {
            puts("Invalid data. Please enter an integer 0 through 2.");
            continue;
        }
        strcpy(region, regionsArr[regionChoice]);
        break;
    }
    // Map the selected region to the corresponding town indices
    int townIndices[ARR_TOWN_LEN / ARR_REGION_LEN];
    for (int i = 0; i < ARR_TOWN_LEN / ARR_REGION_LEN; ++i) {
        townIndices[i] = regionChoice * (ARR_TOWN_LEN / ARR_REGION_LEN) + i;
    }

    // Get town from the user based on the selected region
    while(1)
    {
        printf("Enter town: 0 for %s, 1 for %s\n", townsArr[townIndices[0]], townsArr[townIndices[1]]);
        scanf("%d", &townChoice);
        //printf("DEBUG: After scanf - townChoice: %d\n", townChoice);
        if (townChoice < 0 || townChoice > 1) {
            puts("Invalid data. Please enter an integer 0 or 1.");
            continue;
        }
        strcpy(town, townsArr[townIndices[townChoice]]);
        break;
    }

    // Get race from the user
    while(1)
    {
        puts("Enter race");
        puts("Please enter 0 for Caucasian, 1 for Indigenous, 2 for Afro-American, 3 for Asian, 4 for Other");
        scanf("%d", &raceChoice);
        //printf("DEBUG: After scanf - raceChoice: %d\n", raceChoice);
        if (raceChoice < 0 || raceChoice > 4) {
            puts("Invalid data. Please enter an integer 0 through 4.");
            continue;
        }
        strcpy(race, racesArr[raceChoice]);
        break;
    }
    // Get household data from the user
    while (1) {
        puts("Please enter");
        puts("1-total people in the household,");
        puts("2-people fully vaccinated,");
        puts("3-people tested Covid positive,");
        puts("  Seperated by space/tab and make sure all of these are valid integers");
        scanf("%d %d %d", &householdSize, &vaccinatedNumber, &positiveNumber);
        //printf("DEBUG: After scanf - householdSize: %d, vaccinatedNumber: %d, positiveNumber: %d\n", householdSize, vaccinatedNumber, positiveNumber);
        if (householdSize < 1 ||
            householdSize > MAX_FAMILYSIZE ||
            vaccinatedNumber > householdSize ||
            positiveNumber > householdSize )
        {
            puts("Total people in the household can't be less than total vaccinated or total Covid positive cases and should be granter than 0 and less than 12 . "
                 "Please re-enter values.");
            continue;
        }
        else
            break;
    }
    // Create and return a Household instance using the makeHousehold()
    Household newRecord = makeHousehold(race, region, town, householdSize, positiveNumber, vaccinatedNumber);
    return newRecord;
}
/**
 *
 * @param top top of the list to be passed by reference
 * @param region passed as a character array
 * @param town passed as a character array
 * @param race passed as a character array
 */
void deleteNodesGivenCriteria(NodePtr* top, char region[], char town[], char race[]) {
    //TODO 08: implement deleteNodesGivenCriteria function
    //Check if the list is empty
    if (*top == NULL)
    {
        printf("List is empty. No records to delete.\n");
        return;
    }
    // Create a temporary pointer to traverse the list
    NodePtr current = *top;
    NodePtr previous = NULL;
    int recordCtr = 0;
    // Traverse the list and delete nodes that match the criteria
    while (current != NULL) {
        if (strcmp(current->data.region, region) == 0 &&
            strcmp(current->data.town, town) == 0 &&
            strcmp(current->data.race, race) == 0) {
            // Node matches the criteria, delete it

            // If it's the first node, update top
            if (previous == NULL)
            {
                *top = current->next;
            }
            else
            {
                // Update the next pointer of the previous node
                previous->next = current->next;
            }
            // Free the memory of the deleted node
            free(current);
            // Increment the counter for deleted records
            recordCtr++;
            // Move to the next node
            current = current->next;
        }
        else
        {
            // Node does not match the criteria, move to the next node
            previous = current;
            current = current->next;
        }
    }
    printf("%d matching records deleted.\n", recordCtr);
}// deleteNodeCriteria function ends
/**
 * This function prints the entire list of data. It invokes printRecord function
 * @param ptr is the top of the list
 */
void printList(NodePtr ptr)
{
    // TODO 09: implement printList function
    //function printRecord is invoked
    int serialNumber = 1;  // Initialize the serial number

    // Print the header before printing the records
    printf("%4s%5s%17s%22s%14s%7s%12s\n",
           "S.No", "Size", "Total Vaccinated","Total tested positive", "Race", "Region", "Town");;

    // Traverse the linked list and print each record
    while (ptr != NULL) {
        // Invoke the printRecord function to print a single record
        printRecord(serialNumber, ptr);

        // Move to the next node
        ptr = ptr->next;

        // Increment the serial number for the next record
        serialNumber++;
    }
}
/**
 * It prints a single record starting with a serial number to keep a count of number of records printed
 * @param ctr serial number of the record
 * @param ptr top of the list
 */
void printRecord(int ctr, NodePtr ptr){
    // TODO 13: implement printRecord function
    // Check if the pointer is not NULL
    if (ptr != NULL) {
        printf("%4d%5d%17d%22d%14s%7s%12s\n",
               ctr,                             // Serial number
               ptr->data.familySize,            // "Size"
               ptr->data.fullyVaccinated,      // "Total Vaccinated"
               ptr->data.testedPositive,        // "Total tested positive",
               ptr->data.race,                  // "Race",
               ptr->data.region,                // "Region",
               ptr->data.town);                 // "Town");
    }
    else {
        printf("Error: Null pointer passed to printRecord.\n");
    }
}
/**
 * This function takes data items of a Household record and sets members of a locally declared Household instance and returns it
 * @param race
 * @param region
 * @param town
 * @param familySize
 * @param totPosCovid
 * @param fullyVac
 * @return a Household instance
 */
Household makeHousehold(char race[], char region[], char town[], int familySize, int totPosCovid, int fullyVac ){
    // TODO 14: implement makeHousehold function
    Household newHousehold;

    // Copy values to the members of the new Household instance
    strcpy(newHousehold.race, race);
    strcpy(newHousehold.region, region);
    strcpy(newHousehold.town, town);
    newHousehold.familySize = familySize;
    newHousehold.fullyVaccinated = fullyVac;
    newHousehold.testedPositive = totPosCovid;

    return newHousehold;
}
/**
 * makeNode function allocates dynamic memory to create a node, populates with the data based on its argument of type Household
 * and returns the populated node
 * @param num
 * @return
 */
NodePtr makeNode(Household num){
    // TODO 15: implement makeNode function
    NodePtr newNodePtr = malloc(sizeof(*newNodePtr));

    if (newNodePtr == NULL) {
        puts("Memory allocation failure");
        return NULL;
    }
    newNodePtr->data = num;
    newNodePtr->next = NULL;

    return newNodePtr;
}
/**
 * Add node takes a Household instance, creates a node from it and then adds it to the front of the list that it takes as
 * its other argument
 * @param tom
 * @param num
 */
void addNode(NodePtr* top, Household num){
    // TODO 16: implement addNode function
    NodePtr newNode = makeNode(num);
    // If the list is empty, make the new node the top
    if (*top == NULL) {
        *top = newNode;
        return;
    }

    // Traverse the list to find the last node
    NodePtr current = *top;
    while (current->next != NULL) {
        current = current->next;
    }

    // Add the new node after the last node
    current->next = newNode;
}
/**
 * THis function deletes a node from the list
 * @param tom takes top of the list as a reference
 */
void deleteNode(NodePtr* tom){
    // TODO 17: implement deleteNode function
    // Check if the list is empty
    if (*tom == NULL) {
        printf("List is empty. No records to delete.\n");
        return;
    }

    // Create a temporary pointer to store the node to be deleted
    NodePtr temp = *tom;

    // Update the top pointer to the next node
    *tom = (*tom)->next;

    // Free the memory of the deleted node
    free(temp);

    printf("First record deleted successfully.\n");
}
/**
 * This function deletes all nodes (records) of the list
 * @param tom
 */
void deleteAllNodes(NodePtr* tom){
    // TODO 18: implement deleteAllNodes function
    // Traverse the linked list and free the memory for each node
    while (*tom != NULL)
    {
        NodePtr temp = *tom; // Save the current node
        *tom = (*tom)->next; // Move to the next node
        free(temp);          // Free the memory of the saved node
    }
}
/**
 * It write all the records to a file. As a sample, clients.txt file is saved in the data folder as part of the project folder
 * @param top
 * @param fileName
 */
void writeListToFile(NodePtr top, char fileName[])
{
    // TODO 19: implement writeListToFile function
    FILE *cfPtr;   //cfPtr = test.dat file pointer
    int size = 0; // Variable to store the size of the linked list
    // fopen opens file. Exit program if unable to create file
    if ((cfPtr = fopen(fileName, "w")) == NULL) {
        printf("File could not be opened\n");
    }
    else
    {
        NodePtr current = top;
        //Traverse the linked list and write records to the file with cfPtr
        while (current != NULL)
        {
            fprintf(cfPtr, "%s %s %s %d %d %d\n",
                    current->data.race, current->data.region, current->data.town,
                    current->data.familySize, current->data.fullyVaccinated, current->data.testedPositive);
            current = current->next;
            size++; // Increment the size for each record
        }
        fclose(cfPtr); // fclose closes the file
        printf("%d records and the sentinel record were written to %s successfully\n", size, fileName);
    }
}
/**
 * It reads all records from a file
 * @param fileName
 */
void displayRecordsFromFile(char fileName[])
{
    // TODO 20: implement displayRecordsFromFile function
    FILE *filePtr; // filePtr = test.dat file pointer

    // fopen opens file. Exit program if unable to open file
    if ((filePtr = fopen(fileName, "r")) == NULL) {
        printf("File could not be opened\n");
    } else {
        char race[RACE_NAME_LEN];
        char region[REGION_NAME_LEN];
        char town[TOWN_NAME_LEN];
        int familySize, fullyVaccinated, testedPositive;
        int ctr = 1;
        printf("%4s%5s%17s%22s%14s%7s%12s\n",
               "S.No", "Size", "Total Vaccinated","Total tested positive", "Race", "Region", "Town");;

        //Read records from the file with filePtr
        while (fscanf(filePtr, "%s%s%s%d%d%d",
                      race, region, town, &familySize, &fullyVaccinated, &testedPositive) != EOF)
        {
            printf("%4d%5d%17d%22d%14s%7s%12s\n",
                   ctr++,                 //s.No
                   familySize,            // "Size"
                   fullyVaccinated,       // "Total Vaccinated"
                   testedPositive,        // "Total tested positive",
                   race,                  // "Race",
                   region,                // "Region",
                   town);                 // "Town");
        }
        fclose(filePtr); // fclose closes the file
    }
}