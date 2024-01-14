// File: main.c
#include "seat_reservation.h"
#include "flight_info.h"
#include "passenger_info.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void writePassengerToFile(FLIGHT_NAME flight);

void storeInOrder(NODE *root, NODE *arr, int *index) {
    if (root != NULL) {
        storeInOrder(root->left, arr, index);

        // Copy the current node to the array
        arr[*index] = *root;
        (*index)++;

        storeInOrder(root->right, arr, index);
    }
}

void storeTreeInArray(TREE *tree, NODE *arr, int *size) {
    int index = 0;
    storeInOrder(tree->root, arr, &index);
    *size = index;
}

void writeArrayToFile(NODE *arr, int size, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(arr, sizeof(NODE), size, file);

    fclose(file);
}

NODE *readNodeFromFile(FILE *file) {
    NODE *node = malloc(sizeof(NODE));
    if (node == NULL) {
        perror("Memory allocation error");
        //exit(EXIT_FAILURE);
    }

    fread(node, sizeof(NODE), 1, file);

    return node;
}


void buildTreeFromArray(NODE **root, NODE *arr, int start, int end, FILE *file) {
    if (start <= end) {
        int mid = (start + end) / 2;
        *root = readNodeFromFile(file);  // Pass the file pointer, not the node
    
        buildTreeFromArray(&(*root)->left, arr, start, mid - 1, file);
        buildTreeFromArray(&(*root)->right, arr, mid + 1, end, file);
    }
}

void readArrayFromFile(NODE **root, const char *filename, int size) {
    printf("entered fn readArrayFrom File\n");
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    NODE *treeArray = malloc(sizeof(NODE) * size);
    fread(treeArray, sizeof(NODE), size, file);
    fclose(file);

    buildTreeFromArray(root, treeArray, 0, size - 1, file);  // Use the same file pointer

    free(treeArray);  // Don't forget to free the allocated memory
    
    printf("read from file\n");
}


void handleSeatSelection(NODE *r)
{
        char chosenSeat[4];

        printf("\nEnter the seat you want to choose (e.g., A1): ");
        scanf("%s", chosenSeat);

       /* while (strcmp(chosenSeat, "exit") != 0) {
        while (isSeatTaken(&r->seatList, chosenSeat)) {*/
            printf("Seat %s is already taken. Choose another seat: ", chosenSeat);
            scanf("%s", chosenSeat);
        

        markChosenSeat(&r->seatList, chosenSeat);

        //printf("\nUpdated seat arrangement:\n");
        //printSeats(&r->seatList);

        //printf("\nEnter the seat you want to choose (e.g., A1), or type 'exit' to quit: ");
        //scanf("%s", chosenSeat);

        printf("your chosen seat: %s\n",chosenSeat);
        

}


int searchNode(NODE *r, char *user_fl_name) {
    if (r != NULL) {
        if (strcmp(user_fl_name, r->fl_name) == 0) {
            printf("Initial seat arrangement:\n");
            //printSeats(&r->seatList);
            handleSeatSelection(r);

            return 1;
        } else if (strcmp(user_fl_name, r->fl_name) < 0) {
            return searchNode(r->left, user_fl_name);
        } else {
            return searchNode(r->right, user_fl_name);
        }
    }
    return 0;
}




int searchRecursive(TREE *pt,char *user_fl_name)
{
	return searchNode(pt->root,user_fl_name);
}

void printTreeElements(NODE *root) {
    if (root != NULL) {
        printTreeElements(root->left);

        // Print information for the current node
        printf("Flight Name: %s\n", root->fl_name);
        // Print other relevant information

        printTreeElements(root->right);
    }
}

void insertNode(NODE **root, const char flight_no[], const char src[], const char dest[], int duration, int fare, int st, int et)
{
    if (*root == NULL)
    {
        // Create a new node and assign values
        *root = (NODE *)malloc(sizeof(NODE));
        strcpy((*root)->fl_name, flight_no);
        (*root)->src = strdup(src); // Use strdup to allocate memory for strings
        (*root)->dest = strdup(dest);
        (*root)->duration = duration;
        (*root)->fare = fare;
        (*root)->st = st;
        (*root)->et = et;
        initSeatList(&(*root)->seatList); // Initialize the seatList
        createSeat(&(*root)->seatList);

        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else
    {
        // Recursively insert based on flight number or any other criteria
        if (strcmp(flight_no, (*root)->fl_name) < 0)
        {
            insertNode(&(*root)->left, flight_no, src, dest, duration, fare, st, et);
        }
        else
        {
            insertNode(&(*root)->right, flight_no, src, dest, duration, fare, st, et);
        }
    }
}

void parseAndInsertFromFile(const char *filename, TREE *root)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char flight_no[20], src[20], dest[20];
        int duration, fare, st, et;

        // Assuming the format is: flight_no src dest duration fare st et
        sscanf(line, "%s %s %s %d %d %d %d", flight_no, src, dest, &duration, &fare, &st, &et);

        // Insert the parsed data into the tree
        insertNode(&root->root, flight_no, src, dest, duration, fare, st, et);
    }

    fclose(file);
}



int main()
{
    int choice;
    printf("Do you want to eneter a file?\n");
    scanf("%d",&choice);

    while (choice)
    {
        NODE *temp = malloc(sizeof(NODE));
        temp->left = temp->right = NULL;
        printf("enter the flight name\n");
        scanf("%s", temp->fl_name);
        // For 'src' and 'dest', allocate memory and use strcpy
        temp->src = malloc(50);
        temp->dest = malloc(50);
        printf("enter the source\n");
        scanf("%s", temp->src);
        printf("enter the destination\n");
        scanf("%s", temp->dest);
        printf("enter the duration\n");
        scanf("%d", &temp->duration);
        printf("enter the flight fare\n");
        scanf("%d", &temp->fare);
        // For 'st' and 'et', use char arrays and scanf strings
        printf("enter the start time\n");
        scanf("%d", &temp->st);
        printf("enter the end time\n");
        scanf("%d", &temp->et);
        //NODE *treeArray = malloc(sizeof(NODE) * 100); //linked list 
        temp->seatList.head = NULL;
        createSeat(&temp->seatList);
        storeFlightNode(temp, "flight_data.txt");
        printf("Do you want to eneter a file?\n");
        scanf("%d",&choice);
    }

    
    TREE tobj;

    initTree(&tobj);

    //createTree(&tobj);
    parseAndInsertFromFile("flight_data.txt", &tobj);
    int size;
    NODE *treeArray = malloc(sizeof(NODE) * 100); // Adjust the size accordingly
    //storeTreeInArray(&tobj, treeArray, &size);
    //writeArrayToFile(treeArray, size, "tree_data.dat");
    
    printf("Sorted by fares\n");
    TREE tobj2;
    int size2;
    NODE *treeArray2;
    readArrayFromFile(&tobj2.root, "tree_data.dat", size2);
    printTreeElements(tobj2.root);
     // Pass the root of the tree to inorder
    printf("Enter source\n");
    char u_src[50]; // Declare character arrays for source and destination
    char u_dest[50];
    scanf("%s",u_src);
    printf("Enter destination\n");
    scanf("%s",u_dest);
    printf("Here are your available flights:\n");
    inorder_call(&tobj,u_src,u_dest);
    printf("Please type in the flight you want to go in!\n");
    char user_fl_name[50];
    scanf("%s",user_fl_name);

    searchRecursive(&tobj, user_fl_name);
    printf("done!\n");
    FLIGHT_NAME flight;
    PASSENGER_INFO passenger = book_flight();
    strcpy(flight.fl_name, user_fl_name);
    flight.passenger_list = insertPassenger(flight.passenger_list, passenger);

    // Write passenger information to file
    writePassengerToFile(flight);


    
    return 0;
}