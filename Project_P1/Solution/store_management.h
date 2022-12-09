#ifndef P1_PROTOTYPE_FILE_MANAGEMENT_H
#define P1_PROTOTYPE_FILE_MANAGEMENT_H

#endif //P1_PROTOTYPE_FILE_MANAGEMENT_H


void update_store_database_with_prices(store_db arrayOfStorePrices[]);
store_db * create_store_database(userdata session);
void collect_list_of_groceries(FILE *db, store_db arrayOfStorePrices[], int number);
store_db collect_store_info(FILE *db);