#include "run_time.h"
#include <unistd.h>

//The function run time uses all the different functions and holds all the data
void run_time()
{
    srand(time(NULL));
    //Getting all user data
    userdata user = create_user();

    //Getting all stores
    store_db *ptrToAllStoreGroceries = create_price_database();

    check_shoppinglist(user, ptrToAllStoreGroceries);

    set_on_sale(ptrToAllStoreGroceries);

    //Getting all groceries from each store
    store_db *ptrToAllStoreList = create_store_database(user);

    sum_of_products(ptrToAllStoreGroceries, ptrToAllStoreList);
    sort_stores(ptrToAllStoreList, MAX_STORES);

    print(ptrToAllStoreGroceries, user, ptrToAllStoreList);
}


int check_product(int shoppinglist, store_db store_info[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (strcmp(user_groceries[shoppinglist], store_info[1].product_name[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void check_shoppinglist(userdata user, store_db store_info[]) {
    for (int i = 0; i < user.amount; i++) {
        if (check_product(i, store_info) == 0) {
            printf("\nItem: %s is invalid, please update here: ", user_groceries[i]);
            scanf(" %s", user_groceries[i]);
            printf("\nThis will not update the product in shoppinglist.txt, please consider correcting your mistake in the file!");
        }
    }
    printf("\n\n===================================\n=Shoppinglist loaded successfully!=\n===================================\n");
    sleep(1);
}

/**
 * This is a void function with no return value.
 * It's purpose is to assign values to each object in the store_info array
 * @param store_prices | array of type groceries_db consisting of objects of type groceries_db
 * @param store_info   | array of type store_db consisting of objects of type store_db
 */
void sum_of_products(store_db store_prices[], store_db store_info[])
{
    //Variable declarations
    double sum;
    int j;

    //Loop going through all of the stores
    for (int i = 0; i < MAX_STORES; i++)
    {
        //Variable definitions
        j = 0, sum = 0;
        //Nested loop going through all of the products in each store
        for (int k = 0; k < MAX_PRODUCTS; k++)
        {
            //Comparison function (strcmp = stringcompare), compares each product in shoppinglist with each product in the total list of products)
            //If return value of strcmp is 0 then there's no difference between the two compared elements
            if (strcmp(user_groceries[j], store_prices[i].product_name[k]) == 0)
            {
                //Incrementing the local sum variable by the product_cost of the product that was just found
                sum += store_prices[i].product_cost[k];
                //Resetting variable k, so we can loop through all of the products for next store again.
                k = 0;
                //Incrementing j by one, so we can compare next product in the shoppinglist with all of the products in the store
                j++;
            }
        }
        //Return value to the array in the parameter
        store_info[i].sum = sum;
    }
}

void set_on_sale(store_db store_prices[]) {
    for (int i = 0; i < MAX_STORES; i++) {
        for (int k = 0; k < MAX_PRODUCTS; k++) {
            store_prices[i].product_onSale[k] = random_sale_decider();
        }
    }
}

int random_sale_decider(){
    int x;

    x = rand()%4;

    if (x == 1)
        return 1;

    return 0;
}

/* This function sorts all the store_info after lowest price*/
void sort_stores(store_db store_info[], int stores_amount)
{
    //Quicksort method
    qsort(store_info, stores_amount, sizeof(*store_info), comparator);

    //Bubblesort method
    /*store_db temp;
    for (int i = 0; i < stores_amount - 1; i++)
    {
        for (int j = 0; j < (stores_amount - 1-i); j++)
        {
            if (store_info[j].sum > store_info[j + 1].sum)
            {
                temp = store_info[j];
                store_info[j] = store_info[j + 1];
                store_info[j + 1] = temp;
            }
        }
    }*/
}

int comparator (const void * p1, const void * p2)
{
    store_db * store1 = (store_db*)p1;
    store_db * store2 = (store_db*)p2;

    if (store1->sum > store2->sum)
        return store2 - store1;
    else
        return store1 - store2;
}

void print_promotions(store_db list[], int store) {
    int i, j = 0;

    for (i = 0; i < MAX_PRODUCTS; i++) {
        if (strcmp(user_groceries[j], list[store].product_name[i]) == 0) {
            j++;
            if (list[store].product_onSale[i] == 1) {
                printf("%s is on sale for %.2lf DKK!\n", list[store].product_name[i], list[store].product_cost[i]);
            }
            i = 0;
        }
    }
}

void print(store_db store_prices[], userdata user, store_db store_info[]) {
    printf("\nYour name is set to: %s "
           "\nYour location is set to: %lf %lf"
           "\nYour preferred mode of transport is set to %s and your max travel distance is set to %lf km."
           "\n\nYou have %d item(s) in your shopping list:", user.name, user.location_x, user.location_y, transport_names[user.mode - 1], user.distance, user.amount);

    for (int i = 0; i < user.amount; i++) {
        printf("\n%s", user_groceries[i]);
    }

    printf("\n\nStores found within %lf km from your location:", user.distance);
    for (int i = 0; i < MAX_STORES; i++) {
        if (store_info[i].distance <= user.distance) {
            printf("\n%s %s | TOTAL PRICE: %.2lf | %.2lf KM AWAY\n", store_info[i].name, store_info[i].address, store_info[i].sum, store_info[i].distance);
            print_promotions(store_prices, i);
        }
        printf("---------------------------------------------------------\n");
    }
}

userdata create_user() {
    userdata session;
    printf("\nEnter name please: ");
    scanf(" %s", session.name);
    printf("\nPlease enter your location in a coordinate format: ");
    scanf(" %lf, %lf", &session.location_x, &session.location_y);
    printf("\nPlease enter the number of your preferred mode of transport:\n(1) On foot\n(2) Bike\n(3) Car\n");
    scanf(" %d", &session.mode);
    printf("\nHow far are you willing to travel %s in kilometers: ", transport_names[session.mode - 1]);
    scanf(" %lf", &session.distance);

    char filename[30] = "shoppinglist.txt";
    FILE *shoppingList;

    shoppingList = fopen(filename, "r");
    session.amount = load_shoppinglist(shoppingList);

    return session;
}

int load_shoppinglist(FILE *list) {
    int i = 0;
    int k;

    if (list == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    } else {
        while (!feof(list)) {
            fscanf(list, "%s", user_groceries[i]);
            i++;
        }
        k = i;

        while (k < 100) {
            strcpy(user_groceries[k], "0");
            k++;
        }

    }
    return i;
}