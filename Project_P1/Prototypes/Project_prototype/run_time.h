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
void sort_stores(store_db store_info[], int s);
void sum_of_products(groceries_db store_prices[], store_db store_info[]);
void set_on_sale(groceries_db store_prices[]);
int random_sale_decider();
void check_shoppinglist(userdata user);
void print_promotions(groceries_db list[], int store);
int check_product(int shoppinglist);