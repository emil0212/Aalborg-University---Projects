#include "run_time.h"


//The function run time uses all the different functions and holds all the data
void run_time() {

    //start

    groceries_list all_store_groceries[MAX_STORES];
    groceries_list *ptrToAllStoreGroceries = all_store_groceries;
    ptrToAllStoreGroceries = open_files();

    store_t all_store_list[MAX_STORES];
    store_t *ptrToAllStoreList = all_store_list;
    ptrToAllStoreList = open_stores();

    //end


    userdata user = create_user();

    int numberOfStores = find_amount_of_eliminated_stores(user, ptrToAllStoreList); //This value holds

    store_t final_store_list[MAX_STORES];
    store_t *ptrToFinalStoreList = final_store_list;
    ptrToFinalStoreList = eliminate_stores(user, ptrToAllStoreList, numberOfStores);

    groceries_list final_groceries_list[MAX_STORES];
    groceries_list *ptrToFinalGroceriesList = final_groceries_list;
    ptrToFinalGroceriesList = eliminate_groceries(user, ptrToAllStoreList, ptrToAllStoreGroceries, numberOfStores);
    free(ptrToAllStoreList);
    free(ptrToAllStoreGroceries);

    double sumArray[MAX_STORES];
    double *ptrToSumArray = sumArray;

    //printf("%lf", sumOfProducts(ptrToFinalGroceriesList, numberOfStores, user));

    ptrToSumArray = sumOfProducts(ptrToFinalGroceriesList, numberOfStores, user);

    print(ptrToFinalGroceriesList, user, ptrToFinalStoreList, numberOfStores, ptrToSumArray);
}

/*double sumOfProducts(groceries_list groceriesList[], int num, userdata user) {
    double sum = 0;


        for (int k = 0; k < user.amount; k++) {
            for(int j = 0; j < MAX; j++)
            {
                if(*groceriesList[0].name[j] == *userproducts[k])
                    sum += groceriesList[0].cost[j];
            }
        }
    return sum;
}*/

double * sumOfProducts(groceries_list groceries_list[], int num, userdata user) {
    double sum;
    double* arrayOfSum = malloc(num * sizeof *arrayOfSum);

    for (int i = 0; i < num; i++) {
        sum = 0;
        for (int k = 0; k < user.amount; k++) {

            for(int j = 0; j < MAX; j++)
            {
                if(userproducts[k] == groceries_list[i].name[j])
                    arrayOfSum[i] += groceries_list[i].cost[j];
            }



            /*if(valueinarray(k, i, groceries_list)) {
                sum += groceries_list[i].cost[k];
            }



            if (userproducts[k] == groceries_list[i].name[k]) {
                sum += groceries_list[i].cost[k];
            }*/
        }
    }
    return arrayOfSum;
}


int valueinarray(int product, int store_id, groceries_list groceries_list[])
{
    int j;
    for(j = 0; j < MAX; j++)
    {
        if(groceries_list[store_id].name[j] == userproducts[product])
            return 1;
    }
    return 0;
}

int find_amount_of_eliminated_stores(userdata user, store_t store_list[]) {
    int i, k = 0;
    for (i = 0; i < MAX_STORES; i++) {
        if (distance(user.location_x, user.location_y, store_list[i].x_coordinates, store_list[i].y_coordinates) < user.distance) {
            k++;
        }
    }
    return k;
}

store_t * eliminate_stores(userdata user, store_t store_list[], int num) {
    int i, k = 0;

    store_t* lists2 = malloc(num * sizeof *lists2);
    for (i = 0; i < MAX_STORES; i++) {
        if (distance(user.location_x, user.location_y, store_list[i].x_coordinates, store_list[i].y_coordinates) < user.distance) {
            lists2[k] = store_list[i];
            k++;
        }
    }
    return lists2;
}

groceries_list * eliminate_groceries(userdata user, store_t store_list[], groceries_list groceries[], int num) {
    int i, k = 0;

    groceries_list *lists2 = malloc(num * sizeof *lists2);
    for (i = 0; i < MAX_STORES; i++) {
        if (distance(user.location_x, user.location_y, store_list[i].x_coordinates, store_list[i].y_coordinates) <
            user.distance) {
            lists2[k] = groceries[i];
            k++;
        }
    }
    return lists2;
}

void print(groceries_list grocery_list[], userdata user, store_t new_stores[], int num, double arr[]) {
    printf("\nYour name is set to: %s "
           "\nYour location is: %lf %lf"
           "\nYour preferred mode of transport is %s and your max travel distance is set to %lf km."
           "\nYou have %d item(s) in your shopping list:", user.name, user.location_x, user.location_y, transport_names[user.mode - 1], user.distance, user.amount);

    for (int i = 0; i < user.amount; i++) {
        printf("\n%s", userproducts[i]);
    }

    printf("\nStores found within %lf km from your location:", user.distance);
    for (int i = 0; i < num; i++) {
        printf("\nThe store %s has been found and is located %lf km away from you,\nand has these products and prices:", new_stores[i].name, distance(user.location_x, user.location_y, new_stores[i].x_coordinates, new_stores[i].y_coordinates));

        for (int k = 0; k < MAX; k++) {
            printf("\nProduct %d:\nName: %s \nPrice: %lf\n", grocery_list[i].id[k], grocery_list[i].name[k], grocery_list[i].cost[k]);
        }
    }

    for (int j = 0; j < num; j++) {
    printf("\n%lf", arr[j]);
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