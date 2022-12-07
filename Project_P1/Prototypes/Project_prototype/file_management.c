#include "main.h"
#include "distance.h"
#include "file_management.h"

store_db * create_store_database(userdata session) {
    char filename[20];
    FILE *db;
    store_db* arrayOfStoreInfo = malloc(MAX_STORES * sizeof *arrayOfStoreInfo);

    for (int k = 0; k < MAX_STORES; k++) {
        sprintf(filename, "%d_info.txt", k);
        db = fopen(filename, "r");
        arrayOfStoreInfo[k] = collect_store_info(db);
        arrayOfStoreInfo[k].distance = distance(session.location_x, session.location_y,
                                                arrayOfStoreInfo[k].x_coordinates, arrayOfStoreInfo[k].y_coordinates);
        fclose(db);
    }

    return arrayOfStoreInfo;
}

groceries_db * create_price_database() {
    char filename[20];
    FILE *db;
    groceries_db* arrayOfStorePrices = malloc(MAX_STORES * sizeof *arrayOfStorePrices);

    for (int i = 0; i < MAX_STORES; i++) {
        sprintf(filename, "%d_groceries.txt", i);
        db = fopen(filename, "r");
        arrayOfStorePrices[i] = collect_list_of_groceries(db);
        fclose(db);
    }
    return arrayOfStorePrices;
}

groceries_db collect_list_of_groceries(FILE *db) {
    groceries_db productList;

    if (db == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    } else {
        for (int i = 0; i < MAX_PRODUCTS; i++) {
            fscanf(db, " %lf", &productList.cost[i]);
            productList.id[i] = i;
            productList.name[i] = product_names[i];
        }
    }
    return productList;
}

store_db collect_store_info(FILE *db) {
    store_db storeInfo;

    if (db == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    else {
        fscanf(db, "%s %s %lf %lf", storeInfo.name, storeInfo.address, &storeInfo.x_coordinates, &storeInfo.y_coordinates);
    }
    return storeInfo;
}