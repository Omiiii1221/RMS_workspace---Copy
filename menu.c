#include <stdio.h>
#include <string.h>
#include "menu.h"

int itemIdExists(int itemId) {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("Error opening menu file!\n");
        return 0;
    }
    MenuItem item;
    while (fscanf(file, "%d %49s %f", &item.id, item.name, &item.price) == 3) {
        if (item.id == itemId) {
            fclose(file);
            return 1; // Item ID exists
        }
    }
    fclose(file);
    return 0; // Item ID does not exist
}

// Function to add a menu item to the menu file
void addMenuItem(MenuItem item) {
    FILE *file = fopen("menu.txt", "a");//open in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return; 
    }
    // writing the menu item details to the file
    fprintf(file, "%d %s %.2f\n", item.id, item.name, item.price);
    fclose(file); 
}

// Function to display all menu items in a table format
void displayMenu() {
    FILE *file = fopen("menu.txt", "r"); // we are Opening the menu file in read mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return; 
    }
    char line[100]; 
    MenuItem item;

    // Print the table header
    printf("+----+------------------------------+--------+\n");
    printf("| ID | Name                         | Price  |\n");
    printf("+----+------------------------------+--------+\n");

    // in this loop we are reading each line from the file and printing the menu item details
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %49s %f", &item.id, item.name, &item.price);
        printf("| %-2d | %-28s | %-6.2f |\n", item.id, item.name, item.price);
    }

    // Print the table footer
    printf("+----+------------------------------+--------+\n");
    fclose(file); // Close the file
}

// Function to delete a menu item by ID
void deleteMenuItem(int itemId) {
    FILE *file = fopen("menu.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    MenuItem item;
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %49s %f", &item.id, item.name, &item.price);
        if (item.id != itemId) {
            fprintf(tempFile, "%d %s %.2f\n", item.id, item.name, item.price);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("menu.txt");
    rename("temp.txt", "menu.txt");

    if (found) {
        printf("Menu item deleted successfully!\n");
    } else {
        printf("Menu item ID not found!\n");
    }
}

MenuItem getMenuItemById(int itemId) {
    FILE *file = fopen("menu.txt", "r");
    MenuItem item;
    item.id = -1; // Initialize with invalid ID

    if (file == NULL) {
        printf("Error opening menu file!\n");
        return item;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %49s %f", &item.id, item.name, &item.price);
        if (item.id == itemId) {
            fclose(file);
            return item;
        }
    }

    fclose(file);
    item.id = -1; // Set to invalid ID if not found
    return item;
}