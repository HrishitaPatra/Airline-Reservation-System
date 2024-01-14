// File: flight_info.h
#ifndef FLIGHT_INFO_H
#define FLIGHT_INFO_H

#define MAX 60

#define MAX 60

typedef struct flight_node
{
    char fl_name[50];
    char *src;
    char *dest;
    int duration;
    int fare;
    int st;
    int et;
    List seatList;
    struct flight_node *left; // Change 'node' to 'flight_node'
    struct flight_node *right; // Change 'node' to 'flight_node'
} NODE;



typedef struct tree
{
    struct flight_node *root; // Change 'node' to 'flight_node'
} TREE;

void initTree(TREE *pt);
void createTree(TREE *pt);
void inorder(NODE *r, char *src, char *dest);
void inorder_call(TREE *pt, char *u_src, char *u_dest);
void storeFlightNode(NODE *node, const char *filename);
#endif // FLIGHT_INFO_H
