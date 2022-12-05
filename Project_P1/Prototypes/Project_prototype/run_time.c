#include "run_time.h"
#include <unistd.h>

//The function run time uses all the different functions and holds all the data
void run_time()
{
    srand(time(NULL));
    //Getting all user data
    userdata user = create_user();

    //Getting all stores
    groceries_db *ptrToAllStoreGroceries = create_price_database();

    checkForInvalidProducts(ptrToAllStoreGroceries, user);

    setOnSale(ptrToAllStoreGroceries);

    //Getting all groceries from each store
    store_db *ptrToAllStoreList = create_store_database(user);

    sumOfProducts(ptrToAllStoreGroceries, ptrToAllStoreList);
    bsortDesc(ptrToAllStoreList, MAX_STORES);

    print(ptrToAllStoreGroceries, user, ptrToAllStoreList);
}

void checkForInvalidProducts(groceries_db store_prices[], userdata user) {
    int check = 0;
    int j = 0;

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (strcmp(user_groceries[j], store_prices[1].name[i]) == 0) {
            i = 0;
            check += 1;
            j++;
        }
    }

    if (check != user.amount) {
        printf("1 or more item in your shoppinglist is invalid. Please check for spelling mistakes!");
        exit(EXIT_FAILURE);
    }
}

void sumOfProducts(groceries_db store_prices[], store_db store_info[]) {
    double sum;
    int j;

    for (int i = 0; i < MAX_STORES; i++) {
        j = 0, sum = 0;
        for (int k = 0; k < MAX_PRODUCTS; k++) {
            if (strcmp(user_groceries[j], store_prices[i].name[k]) == 0) {
                sum += store_prices[i].cost[k];
                k = 0; // Resetting the loop, so we can find products before the found one
                j++;
            }
        }
        store_info[i].sum = sum;
    }
}

void setOnSale(groceries_db store_prices[]) {
    for (int i = 0; i < MAX_STORES; i++) {
        for (int k = 0; k < MAX_PRODUCTS; k++) {
            store_prices[i].onSale[k] = random2();
        }
    }
}

/* Return 0 and 1 with 75% and 25% probability, respectively, using the specified function and bitwise AND operator */
int random2() {
    int x = random1();
    int y = random1();

    return (x & y);
}

int random1()
{
    // `rand()` produces a random number
    int random = rand();

    // if the random number is even, return 0; otherwise, return 1
    return (random % 2);
}

/* This function sorts all the store_info after lowest price */
void bsortDesc(store_db store_info[], int s)
{
    int i, j;
    store_db temp;

    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (store_info[j].sum > store_info[j + 1].sum)
            {
                temp = store_info[j];
                store_info[j] = store_info[j + 1];
                store_info[j + 1] = temp;
            }
        }
    }
}

void print_promotions(groceries_db list[], int store) {
    int i, j = 0;


    for (i = 0; i < MAX_PRODUCTS; i++) {
        if (strcmp(user_groceries[j], list[store].name[i]) == 0) {
            j++;
            if (list[store].onSale[i] == 1) {
                printf("%s is on sale for %.2lf DKK!\n", list[store].name[i], list[store].cost[i]);
            }
            i = 0;
        }
    }
}

void print(groceries_db store_prices[], userdata user, store_db store_info[]) {
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
    printf("\nPlease enter your location in a coordinate format >> latitude, longitude : ");
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