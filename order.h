#ifndef ORDER_H
#define ORDER_H

typedef struct {
    int id;
    int customerId;
    int itemId;
    int quantity;
    float totalPrice;
} Order;
int orderIdExists(int orderId);
void addOrder(Order order);
void displayOrders();
float getItemPrice(int itemId);
void deleteOrder(int orderId);
Order getOrderById(int orderId); // Add this line

#endif // ORDER_H