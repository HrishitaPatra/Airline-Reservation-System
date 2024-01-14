// File: seat_reservation.h
#ifndef SEAT_RESERVATION_H
#define SEAT_RESERVATION_H

#define MAX 60

typedef struct Seat {
    char st[4];
    int no;
    struct Seat *next;
} Seat;

typedef struct List {
    Seat *head;
} List;

void createSeat(List *pl);
int isSeatTaken(List *pl, const char *chosenSeat);
void markChosenSeat(List *pl, const char *chosenSeat);
void printSeats(List *pl);

#endif // SEAT_RESERVATION_H
