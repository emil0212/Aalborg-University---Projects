#ifndef P1_PROTOTYPE_MAIN_H
#define P1_PROTOTYPE_MAIN_H

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 100 // Amount of products
#define MAX_STORES 5     // Amount of stores

typedef struct store {
    double x_coordinates, y_coordinates;
    char name[30];
    char address[30];
    double sum;
    double distance; //distance from user

    double product_cost[MAX_PRODUCTS];
    char *product_name[MAX_PRODUCTS];
    int product_onSale[MAX_PRODUCTS];
} store_db;

typedef struct userdata {
    char name[30];
    double location_x;
    double location_y;
    int amount;
    int mode;
    double distance;
} userdata;

const static char *transport_names[] = {"On foot", "Bike", "Car"};

void run_time();