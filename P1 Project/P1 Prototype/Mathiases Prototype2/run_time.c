#include "run_time.h"


//The function run time uses all the different functions and holds all the data
void run_time() {

    //Getting all user data
    userdata user = create_user();

    //Getting all stores
    groceries_list all_store_groceries[MAX_STORES];
    groceries_list *ptrToAllStoreGroceries = all_store_groceries;
    ptrToAllStoreGroceries = open_files();

    //Getting all groceries from each store
    store_t all_store_list[MAX_STORES];
    store_t *ptrToAllStoreList = all_store_list;
    ptrToAllStoreList = open_stores(user);

    sumOfProducts(ptrToAllStoreGroceries, ptrToAllStoreList);
    bsortDesc(ptrToAllStoreList, MAX_STORES);

    print(ptrToAllStoreGroceries, user, ptrToAllStoreList, MAX_STORES);
}

void sumOfProducts(groceries_list list[], store_t store[]) {
    double sum;
    int j;

    for (int i = 0; i < MAX_STORES; i++) {
        j = 0, sum = 0;
        for (int k = 0; k < MAX; k++) {
            if (strcmp(userproducts[j], list[i].name[k]) == 0) {
                sum += list[i].cost[k];
                j++;
            }
        }
        store[i].sum = sum;
    }
}


/* This function sorts all the stores after lowest price */
void bsortDesc(store_t stores[], int s)
{
    int i, j;
    store_t temp;

    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (stores[j].sum > stores[j + 1].sum)
            {
                temp = stores[j];
                stores[j] = stores[j + 1];
                stores[j + 1] = temp;
            }
        }
    }
}

void print(groceries_list grocery_list[], userdata user, store_t new_stores[]) {
    printf("\nYour name is set to: %s "
           "\nYour location is set to: %lf %lf"
           "\nYour preferred mode of transport is set to %s and your max travel distance is set to %lf km."
           "\n\nYou have %d item(s) in your shopping list:", user.name, user.location_x, user.location_y, transport_names[user.mode - 1], user.distance, user.amount);

    for (int i = 0; i < user.amount; i++) {
        printf("\n%s", userproducts[i]);
    }

    printf("\n\nStores found within %lf km from your location:", user.distance);
    for (int i = 0; i < MAX_STORES; i++) {
        if (new_stores[i].distance <= user.distance) {
            printf("\n%s %s | TOTAL PRICE: %lf | %.2lf KM AWAY\n", new_stores[i].name, new_stores[i].address, new_stores[i].sum, new_stores[i].distance);
        }
    }
}

userdata create_user() {
    userdata session;
    printf("\nEnter name please: ");
    scanf(" %s", session.name);
    printf("\nPlease enter your location in a coordinate format (latitude / longitude): ");
    scanf(" %lf %lf", &session.location_x, &session.location_y);
    printf("\nPlease enter the number of your preferred mode of transport:\n(1) On foot\n(2) Bike\n(3) Car\n");
    scanf(" %d", &session.mode);
    printf("\nHow far are you willing to travel %s in kilometers", transport_names[session.mode - 1]);
    scanf(" %lf", &session.distance);

    char filename[30] = "shoppinglist.txt";
    FILE *myFile;

    myFile = fopen(filename, "r");
    session.amount = create_shoppinglist(myFile);

    return session;
}


int create_shoppinglist(FILE *list) {
    int i = 0;

    if (list == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    } else {
        while (!feof(list)) {
            fscanf(list, "%s", userproducts[i]);
            i++;
        }
    }
    return i;
}