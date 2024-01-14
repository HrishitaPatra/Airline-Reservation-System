#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct passenger_address {
    char street[100];
    char city[50];
    char state[50];
    char postalCode[20];
    char country[50];
} PASSENG_ADDR;

typedef struct CreditCard {
    char cardNumber[17];
    char cardHolderName[100];
    char expirationDate[6];
    char securityCode[4];
} CREDIT_CARD;

typedef struct passenger_info {
    char name[50];
    char gender[30];
    char seat_no[50];
    char email_id[50];
    char nationality[50];
    int ph_no;
    int emergency_cont;
    PASSENG_ADDR p_a;
    CREDIT_CARD c_a;
} PASSENGER_INFO;

typedef struct flight_name {
    char fl_name[50];
    struct NOD *passenger_list;
} FLIGHT_NAME;

typedef struct NOD {
    PASSENGER_INFO passenger_data;
    struct NOD *next;
} NOD;

NOD *insertPassenger(NOD *head, PASSENGER_INFO passenger_data) {
    NOD *newNode = (NOD *)malloc(sizeof(NOD));
    if (newNode == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    newNode->passenger_data = passenger_data;
    newNode->next = head;

    return newNode;
}

PASSENGER_INFO book_flight() {
    PASSENGER_INFO passenger;

    printf("Enter the name: ");
    scanf("%s", passenger.name);

    printf("Enter your gender: ");
    scanf("%s", passenger.gender);

    printf("Enter your email ID: ");
    scanf("%s", passenger.email_id);

    printf("Enter your nationality: ");
    scanf("%s", passenger.nationality);

    printf("Enter your phone number: ");
    scanf("%d", &passenger.ph_no);

    printf("Enter your emergency contact: ");
    scanf("%d", &passenger.emergency_cont);

    printf("Enter your street address: ");
    scanf("%s", passenger.p_a.street);

    printf("Enter your city: ");
    scanf("%s", passenger.p_a.city);

    printf("Enter your state or region: ");
    scanf("%s", passenger.p_a.state);

    printf("Enter your postal code: ");
    scanf(" %[^\n]", passenger.p_a.postalCode);

    printf("Enter your country: ");
    scanf(" %[^\n]", passenger.p_a.country);

    printf("Enter your card number: ");
    scanf("%s", passenger.c_a.cardNumber);

    printf("Enter your card holder name: ");
    scanf("%s", passenger.c_a.cardHolderName);

    printf("Enter your card expiration date (MM/YY): ");
    scanf("%s", passenger.c_a.expirationDate);

    printf("Enter your security code: ");
    scanf("%s", passenger.c_a.securityCode);

    return passenger;
}


void writePassengerToFile(PASSENGER_INFO passenger) {
    FILE *file = fopen("passenger_info.txt", "a");  // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        //exit(EXIT_FAILURE);
    }

    // Print passenger information to file
    if (fprintf(file, "Name: %s\n", passenger.name) < 0 ||
        fprintf(file, "Gender: %s\n", passenger.gender) < 0 ||
        fprintf(file, "Email ID: %s\n", passenger.email_id) < 0 ||
        fprintf(file, "Nationality: %s\n", passenger.nationality) < 0 ||
        fprintf(file, "Phone Number: %d\n", passenger.ph_no) < 0 ||
        fprintf(file, "Emergency Contact: %d\n", passenger.emergency_cont) < 0 ||
        fprintf(file, "Street Address: %s\n", passenger.p_a.street) < 0 ||
        fprintf(file, "City: %s\n", passenger.p_a.city) < 0 ||
        fprintf(file, "State/Region: %s\n", passenger.p_a.state) < 0 ||
        fprintf(file, "Postal Code: %s\n", passenger.p_a.postalCode) < 0 ||
        fprintf(file, "Country: %s\n", passenger.p_a.country) < 0 ||
        fprintf(file, "Card Number: %s\n", passenger.c_a.cardNumber) < 0 ||
        fprintf(file, "Card Holder Name: %s\n", passenger.c_a.cardHolderName) < 0 ||
        fprintf(file, "Expiration Date: %s\n", passenger.c_a.expirationDate) < 0 ||
        fprintf(file, "Security Code: %s\n", passenger.c_a.securityCode) < 0) {
        perror("Error writing to file");
    } else {
        fprintf(file, "\n");  // Add a newline to separate entries
        printf("Passenger information written to file successfully.\n");
    }

    fclose(file);
}