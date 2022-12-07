#ifndef P1_PROTOTYPE_FILE_MANAGEMENT_H
#define P1_PROTOTYPE_FILE_MANAGEMENT_H

#endif //P1_PROTOTYPE_FILE_MANAGEMENT_H


groceries_db * create_price_database();
store_db * create_store_database(userdata session);
groceries_db collect_list_of_groceries (FILE *db);
store_db collect_store_info(FILE *db);