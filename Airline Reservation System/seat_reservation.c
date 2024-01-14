// File: seat_reservation.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 60

typedef struct Seat {
    char st[4];
    int no;
    struct Seat *next;
} Seat;

typedef struct List {
    Seat *head;
} List;

//linked list of seat numbers

void createSeat(List *pl);
int isSeatTaken(List *pl, const char *chosenSeat);
void markChosenSeat(List *pl, const char *chosenSeat);
void printSeats(List *pl);

void createSeat(List *pl) {
    
    for (char row = 'A'; row <= 'F'; row++) {
        for (int seatNum = 30; seatNum >= 1; seatNum--) {
            Seat *temp = malloc(sizeof(Seat));
            temp->next = NULL;

            // Use sprintf to create a string combining a letter and a number
            sprintf(temp->st, "%c%d", row, seatNum);

            // Assign a unique seat number
            temp->no = (row - 'A') * 30 + seatNum;

            // Add the new Seat to the linked list
            temp->next = pl->head;
            pl->head = temp;
        }
    }
}

int isSeatTaken(List *pl, const char *chosenSeat) {
    Seat *current = pl->head;
    while (current != NULL) {
        if (strcmp(current->st, chosenSeat) == 0) {
            // Check if the seat is already taken
            if (strcmp(current->st, "X") == 0) {
                return 1; // Seat is taken
            }
            return 0; // Seat is available
        }
        current = current->next;
    }
    return 1; // Invalid seat
}

void markChosenSeat(List *pl, const char *chosenSeat) {
    Seat *current = pl->head;
    while (current != NULL) {
        if (strcmp(current->st, chosenSeat) == 0) {
            // Mark the chosen seat with 'X'
            strcpy(current->st, "X");
            break;
        }
        current = current->next;
    }
}





void printSeats(List *pl) {
    Seat *current = pl->head;

    while (current != NULL) {
        printf("%s ", current->st);
        
        // Add a new line after every 10 seats for better readability
        if (current->no % 10 == 0) {
            printf("\n");
        }

        current = current->next;
        
    }
    printf("reached the end!\n");
}