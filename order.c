#include <stdio.h>
#include <string.h>
#include "order.h"
#include "menu.h"

// Function to get the price of an item by its ID
float getItemPrice(int itemId) {
    FILE *file = fopen("menu.txt", "r"); // Open the menu file in read mode
    if (file == NULL) {
        printf("Error opening menu file!\n");
        return -1; 
    }
    char line[100];
    MenuItem item;
    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %49s %f", &item.id, item.name, &item.price);
        // If the item ID matches, return the price
        if (item.id == itemId) {
            fclose(file);
            return item.price;
        }
    }
    fclose(file);
    return -1; // Return -1 if the item is not found
}

// Function to check if an order ID already exists
int orderIdExists(int orderId) {
    FILE *file = fopen("orders.txt", "r");
    if (file == NULL) {
        printf("Error opening orders file!\n");
        return 0;
    }
    Order order;
    while (fscanf(file, "%d %d %d %d %f", &order.id, &order.customerId, &order.itemId, &order.quantity, &order.totalPrice) == 5) {
        if (order.id == orderId) {
            fclose(file);
            return 1; // Order ID exists
        }
    }
    fclose(file);
    return 0; // Order ID does not exist
}

// Function to add an order
void addOrder(Order order) {
    if (orderIdExists(order.id)) {
        printf("Duplicate ID not allowed. Please enter a new order ID.\n");
        return;
    }

    float itemPrice = getItemPrice(order.itemId); 
    if (itemPrice == -1) {
        printf("Item ID not found!\n");
        getchar();
        return;  
    }
    
    if (order.quantity <= 0) {
        printf("Invalid quantity!\n");
        return;   
    }

    // Calculate the total price
    order.totalPrice = itemPrice * order.quantity;

    FILE *file = fopen("orders.txt", "a"); // Open the orders file in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return; 
    }
    // Write the order details to the file
    fprintf(file, "%d %d %d %d %.2f\n", order.id, order.customerId, order.itemId, order.quantity, order.totalPrice);
    fclose(file);
}

// Function to display all orders
void displayOrders() {
    FILE *file = fopen("orders.txt", "r"); // Open the orders file in read mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return; 
    }
    Order order;

    
    printf("+----------+-------------+-------------+----------+-------------+\n");
    printf("| Order ID | Customer ID | Menu Item ID| Quantity | Total Price |\n");
    printf("+----------+-------------+-------------+----------+-------------+\n");

    // Read each order from the file and print it 
    while (fscanf(file, "%d %d %d %d %f", &order.id, &order.customerId, &order.itemId, &order.quantity, &order.totalPrice) == 5) {
        printf("| %-8d | %-11d | %-11d | %-8d | %-11.2f |\n", order.id, order.customerId, order.itemId, order.quantity, order.totalPrice);
    }

    // Print the table footer
    printf("+----------+-------------+-------------+----------+-------------+\n");
    fclose(file);
}

// Function to delete an order by ID
void deleteOrder(int orderId) {
    FILE *file = fopen("orders.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    Order order;
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %d %d %d %f", &order.id, &order.customerId, &order.itemId, &order.quantity, &order.totalPrice);
        if (order.id != orderId) {
            fprintf(tempFile, "%d %d %d %d %.2f\n", order.id, order.customerId, order.itemId, order.quantity, order.totalPrice);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("orders.txt");
    rename("temp.txt", "orders.txt");

    if (found) {
        printf("Order deleted successfully!\n");
    } else {
        printf("Order ID not found!\n");
    }
}

Order getOrderById(int orderId) {
    FILE *file = fopen("orders.txt", "r");
    Order order;
    order.id = -1; // Initialize with invalid ID

    if (file == NULL) {
        printf("Error opening orders file!\n");
        return order;
    }

    while (fscanf(file, "%d %d %d %d %f", &order.id, &order.customerId, &order.itemId, &order.quantity, &order.totalPrice) == 5) {
        if (order.id == orderId) {
            fclose(file);
            return order;
        }
    }

    fclose(file);
    order.id = -1; // Set to invalid ID if not found
    return order;
}