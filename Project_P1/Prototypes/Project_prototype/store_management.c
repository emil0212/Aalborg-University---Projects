#include "main.h"
#include "utilities.h"
#include "store_management.h"


/**
 * This is a pointer of type store_db function.
 * It's purpose is to initialize the file management system creating an dynamically allocated array of type store_db.
 * This is array is then filled with information using several sister functions.
 * @param session  | Of type userdata consisting of all information the user put as an input
 * @return | The function is a pointer of type store_db which means it will return a pointer to the allocated array arrayOfStoreInfo
 */
store_db * create_store_database(userdata session)
{
    //Variable declarations
    char filename[20];
    FILE *db;

    //Allocating space in the memory for MAX_STORES amount of type store_db
    store_db* arrayOfStoreInfo = malloc(MAX_STORES * sizeof *arrayOfStoreInfo);


    //Loop through each store
    for (int k = 0; k < MAX_STORES; k++)
    {
        sprintf(filename, "%d_info.txt", k); //Change the file name to the desired store
        db = fopen(filename, "r");          //Open the file
        validate_file_pointer(db);                    //Validate file
        arrayOfStoreInfo[k] = collect_store_info(db);
        arrayOfStoreInfo[k].distance = distance(session.location_x, session.location_y,
                                                arrayOfStoreInfo[k].x_coordinates, arrayOfStoreInfo[k].y_coordinates);
        fclose(db);
    }
    update_store_database_with_prices(arrayOfStoreInfo);
    return arrayOfStoreInfo;
}

/**
 * This is a void function with no return value.
 * It's purpose is to assign prices to all stores in the parameter using a sister function.
 * @param arrayOfStorePrices | array of type store_db consisting of objects of type store_db
 */
void update_store_database_with_prices(store_db arrayOfStorePrices[])
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

/**
 * This is a pointer of type char function.
 * It's purpose is to find the specific line the product name is located and return it.
 * @param id    | An integer used to indicate the specific line where the product name is located
 * @return      | This function returns a pointer to an array of characters pointing at the specific product name
 */
char * find_product_name(int id)
{
    //Allocating memory for an array of chars
    char *temp = malloc(30 * sizeof(char));

    //Open datafile with the product names
    FILE * file = fopen("productslist.txt", "r");

    //Validate file
    validate_file_pointer(file);

    //Run through the lines in the file up to the given id without scanning the product names
    for (int i = 0; i < id; i++) {
        fscanf(file, " %*s");
    }

    //Here we continue from the loop and scan the line number given from the id
    fscanf(file," %s", temp);
    fclose(file);

    return temp;
}

/**
 * This is a void function with no return value.
 * It's purpose is to scan store grocery prices from a file and assign the specific grocery name through another function.
 * @param db                | A file pointer pointing at a specific store file containing data about groceries
 * @param arrayOfStoreInfo  | array of type store_db consisting of objects of type store_db
 * @param number            | An integer used to indicate the specific store from 0 to MAX_STORES
 */
void collect_list_of_groceries(FILE *db, store_db arrayOfStoreInfo[], int number)
{
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        fscanf(db, " %lf", &arrayOfStoreInfo[number].product_cost[i]);
        arrayOfStoreInfo[number].product_name[i] = find_product_name(i);
    }
}

/**
 * This is a function of type store_db
 * It's purpose is to scan store information from a file
 * @param db    | A file pointer pointing at a specific store file containing data about store info
 * @return      | The function returns a struct of store_db containing information about a store
 */
store_db collect_store_info(FILE *db)
{
    store_db storeInfo;

    fscanf(db, "%s %s %lf %lf", storeInfo.name, storeInfo.address, &storeInfo.x_coordinates, &storeInfo.y_coordinates);

    return storeInfo;
}