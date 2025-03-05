#ifndef MENU_H
#define MENU_H

typedef struct {
    int id;
    char name[50];
    float price;
} MenuItem;

void addMenuItem(MenuItem item);
void displayMenu();
void deleteMenuItem(int itemId);
MenuItem getMenuItemById(int itemId); 

#endif 