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
        validate_file_pointer(db);
        arrayOfStoreInfo[k] = collect_store_info(db);
        arrayOfStoreInfo[k].distance = distance(session.location_x, session.location_y,
                                                arrayOfStoreInfo[k].x_coordinates, arrayOfStoreInfo[k].y_coordinates);
        fclose(db);
    }
    create_price_database(arrayOfStoreInfo);
    return arrayOfStoreInfo;
}

void create_price_database(store_db arrayOfStorePrices[])
{
    char filename[20];
    FILE *db;

    for (int i = 0; i < MAX_STORES; i++) {
        sprintf(filename, "%d_groceries.txt", i);
        db = fopen(filename, "r");
        validate_file_pointer(db);
        collect_list_of_groceries(db, arrayOfStorePrices, i);
        fclose(db);
    }
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

void collect_list_of_groceries(FILE *db, store_db arrayOfStorePrices[], int number)
{
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        fscanf(db, " %lf", &arrayOfStorePrices[number].product_cost[i]);
        arrayOfStorePrices[number].product_name[i] = find_product_name(i);
    }
}

store_db collect_store_info(FILE *db)
{
    store_db storeInfo;

    fscanf(db, "%s %s %lf %lf", storeInfo.name, storeInfo.address, &storeInfo.x_coordinates, &storeInfo.y_coordinates);

    return storeInfo;
}