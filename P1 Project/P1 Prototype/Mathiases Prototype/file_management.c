#include "main.h"
#include "file_management.h"

store_t * open_stores() {
    char filename1[20];
    FILE *myFile1;
    store_t* lists1 = malloc(MAX_STORES * sizeof *lists1);

    for (int k = 0; k < MAX_STORES; k++) {
        sprintf(filename1, "%d_info.txt", k);
        myFile1 = fopen(filename1, "r");
        lists1[k] = make_stores(myFile1);
        fclose(myFile1);
    }

    return lists1;
}

groceries_list * open_files() {
    char filename[20];
    FILE *myFile;
    groceries_list* lists = malloc(MAX_STORES * sizeof *lists);

    for (int i = 0; i < MAX_STORES; i++) {
        sprintf(filename, "%d_groceries.txt", i);
        myFile = fopen(filename, "r");
        lists[i] = make_groceries(myFile);
        fclose(myFile);
    }
    return lists;
}

groceries_list make_groceries (FILE *fp) {
    groceries_list list;

    if (fp == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    } else {
        for (int i = 0; i < MAX; i++) {
            fscanf(fp, " %lf", &list.cost[i]);
            list.id[i] = i;
            list.name[i] = product_names[i];
        }
    }
    return list;
}

store_t make_stores(FILE *fp1) {
    store_t list1;

    if (fp1 == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    else {
        fscanf(fp1, "%s %s %lf %lf", list1.name, list1.address, &list1.x_coordinates, &list1.y_coordinates);
    }
    return list1;
}