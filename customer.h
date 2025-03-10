#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
    int id;
    char name[50];
    char phone[15];
} Customer;

int customerIdExists(int customerId);
void addCustomer(Customer customer);
void displayCustomers();
void deleteCustomer(int customerId);
Customer getCustomerById(int customerId); 

#endif // CUSTOMER_H