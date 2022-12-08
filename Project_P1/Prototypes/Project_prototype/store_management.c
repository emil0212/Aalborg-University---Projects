#include "main.h"
#include "utilities.h"
#include "store_management.h"

store_db * create_store_database(userdata session)
{
    char filename[20];
    FILE *db;
    store_db* arrayOfStoreInfo = malloc(MAX_STORES * sizeof *arrayOfStoreInfo);

    for (int k = 0; k < MAX_STORES; k++)
    {
        sprintf(filename, "%d_info.txt", k);
        db = fopen(filename, "r");
        arrayOfStoreInfo[k] = collect_store_info(db);
        arrayOfStoreInfo[k].distance = distance(session.location_x, session.location_y,
                                                arrayOfStoreInfo[k].x_coordinates, arrayOfStoreInfo[k].y_coordinates);
        fclose(db);
    }

    return arrayOfStoreInfo;
}

store_db * create_price_database()
{
    char filename[20];
    FILE *db;
    store_db* arrayOfStorePrices = malloc(MAX_STORES * sizeof *arrayOfStorePrices);

    for (int i = 0; i < MAX_STORES; i++) {
        sprintf(filename, "%d_groceries.txt", i);
        db = fopen(filename, "r");
        arrayOfStorePrices[i] = collect_list_of_groceries(db);
        fclose(db);
    }

    return arrayOfStorePrices;
}

char * find_product_name(int id)
{
    char *temp = malloc(MAX_PRODUCTS * sizeof(char));

    FILE * file = fopen("productslist.txt", "r");
    validate_file_pointer(file);

    for (int i = 0; i < id; i++) {
        fscanf(file, " %*s");
    }

    fscanf(file," %s", temp);

    return temp;
}

store_db collect_list_of_groceries(FILE *db)
{
    store_db productList;

    validate_file_pointer(db);

    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        fscanf(db, " %lf", &productList.product_cost[i]);
        productList.product_name[i] = find_product_name(i);
    }

    return productList;
}

store_db collect_store_info(FILE *db)
{
    store_db storeInfo;

    validate_file_pointer(db);

    fscanf(db, "%s %s %lf %lf", storeInfo.name, storeInfo.address, &storeInfo.x_coordinates, &storeInfo.y_coordinates);

    return storeInfo;
}