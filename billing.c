#include <stdio.h>
#include "order.h"
#include "customer.h"
#include "menu.h"
#include "billing.h"

void printBill(int orderId) {
    Order order = getOrderById(orderId);
    Customer customer = getCustomerById(order.customerId);
    MenuItem item = getMenuItemById(order.itemId);

    printf("\n");
    printf("\t===============================================================================================\n");
    printf("\t                                     Restaurant Bill\n");
    printf("\t===============================================================================================\n");
    printf("\tOrder ID: %d\n", order.id);
    printf("\tCustomer Name: %s\n", customer.name);
    printf("\tCustomer Phone: %s\n", customer.phone);
    printf("\t-----------------------------------------------------------------------------------------------\n");
    printf("\tItem Name\t\tQuantity\tPrice\t\tTotal\n");
    printf("\t-----------------------------------------------------------------------------------------------\n");
    printf("\t%-16s\t%d\t\t%.2f\t\t%.2f\n", item.name, order.quantity, item.price, item.price * order.quantity);
    printf("\t-----------------------------------------------------------------------------------------------\n");
    printf("\tTotal Amount:\t\t\t\t\t%.2f\n", item.price * order.quantity);
    printf("\t===============================================================================================\n");
    printf("\tThank you for dining with us!\n");
    printf("\t_______________________________________________________________________________________________\n");
}