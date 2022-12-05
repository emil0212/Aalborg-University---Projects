#ifndef P1_PROTOTYPE_RUN_TIME_H
#define P1_PROTOTYPE_RUN_TIME_H

#endif //P1_PROTOTYPE_RUN_TIME_H

#include "main.h"
#include "distance.h"
#include "file_management.h"

char user_groceries[100][15];

int load_shoppinglist(FILE *list);
void print(groceries_db store_prices[], userdata user, store_db store_info[]);
userdata create_user();
void bsortDesc(store_db store_info[], int s);
void sumOfProducts(groceries_db store_prices[], store_db store_info[]);
void setOnSale(groceries_db store_prices[]);
int random1();
int random2();
void checkForInvalidProducts(groceries_db store_prices[], userdata user);
void print_promotions(groceries_db list[], int store);