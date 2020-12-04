#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../Models/model.h"

const char* detectOS() {
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

void date(){
    time_t todaytime;
    time(&todaytime);
    printf("%s\n", ctime(&todaytime));
}

unsigned long DJB2(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
      hash = ((hash << 5) + hash) + c;
    return hash % MAX_ELEMENT;
}

void centering(char string[]){//, 1 menu, 2 quantity, 3 price
    for(int i=0;i<(20-strlen(string))/2;i++){
        printf(" ");
    }
    printf("%s", string);
    for(int i=0;i<(20-strlen(string))/2;i++){
        printf(" ");
    }
    if(strlen(string)%2==1){
        printf(" ");
    }
}

Menu* createMenu(char menuName[], int price, int quantity){
    Menu* newMenu = (Menu*)malloc(sizeof(Menu));

    strcpy(newMenu->menuName, menuName);
    newMenu->price=price;
    newMenu->quantity=quantity;

    newMenu->prev=newMenu->next=NULL;
    return newMenu;
}

void appendMenu(char menuName[], int price, int quantity){
    Menu* temp = createMenu(menuName, price, quantity);

    if(!headMenu){
        headMenu=tailMenu=temp;
    }
    else{
        temp->prev=tailMenu;
        tailMenu->next=temp;
        tailMenu=temp;
    }
}

bool popMenu(char menuName[]){
    if(!headMenu){
        return false;
    }
    else if(!strcmp(headMenu->menuName, menuName)){
        if(headMenu && headMenu == tailMenu){
            headMenu=tailMenu=NULL;
            free(headMenu);
        }
        else{
            Menu* temp=headMenu->next;
            temp->prev=headMenu->next=NULL;
            free(headMenu);
            headMenu=temp;
        }
    }
    else if(!strcmp(tailMenu->menuName, menuName)){
        if(headMenu && headMenu == tailMenu){
            headMenu=tailMenu=NULL;
            free(headMenu);
        }
        else{
            Menu* temp=tailMenu->prev;
            temp->next=tailMenu->prev=NULL;
            free(tailMenu);
            tailMenu=temp;
        }
    }
    else{
        currMenu=headMenu;

        while(currMenu && strcmp(currMenu->menuName,menuName)){
            currMenu= currMenu->next;
        }

        if(!currMenu){
            return false;
        }
        currMenu->prev->next=currMenu->next;
        currMenu->next->prev=currMenu->prev;

        currMenu->prev=currMenu->next=NULL;
        free(currMenu);
    }
    return true;
}

Customer* createCustomer(char customerName[]){
    Customer* temp=(Customer*)malloc(sizeof(Customer));
    strcpy(temp->customerName, customerName);
    temp->next=NULL;
    return temp;
}

void insertCustomer(char customerName[]){
    int index=DJB2(customerName);

    if(headCustomer[index]){
        Customer* temp=createCustomer(customerName);
        tailCustomer[index]->next=temp;
        tailCustomer[index]=temp;
    }
    else{
        headCustomer[index]=tailCustomer[index]=createCustomer(customerName);
    }
}

bool search(char customerName[]){
    for(int i=0;i<MAX_ELEMENT;i++){
        if(headCustomer[i]){
            Customer* curr=headCustomer[i];
            while(curr){
                if(!strcmp(curr->customerName, customerName)) return true;
                curr=curr->next;
            }
        }
    }
    return false;
}

void view(){
    for(int i=0;i<MAX_ELEMENT;i++){
        if(headCustomer[i]){
            printf("%d. ", i);
            Customer* curr=headCustomer[i];
            while(curr){
                printf("%s", curr->customerName);
                if(curr->next){
                    printf(", ");
                    curr=curr->next;
                }
                else{
                    break;
                }
            }
            puts("");
        }
    }
}

Order* createOrder(char orderName[], int quantity){
    Order* temp=(Order*)malloc(sizeof(Order));

    strcpy(temp->orderName, orderName);
    temp->quantity=quantity;
    temp->next=temp->prev=NULL;
    return temp;
}

bool validateOrder(char orderName[], int orderQuantity){
    currMenu=headMenu;

    while(currMenu){
        if(!strcmp(currMenu->menuName, orderName)){
            if(orderQuantity>0 && orderQuantity <= currMenu->quantity) return true;
        }
        currMenu=currMenu->next;
    }

    return false;
}

void addOrder(char customerName[], char orderName[], int quantity){
    Order* temp=createOrder(orderName, quantity);

    for(int i=0;i<MAX_ELEMENT;i++){
        if(headCustomer[i]){
            Customer* currCustomer = headCustomer[i];
            while(currCustomer){
                if(!strcmp(currCustomer->customerName, customerName)){
                    if(!currCustomer->orders){
                        currCustomer->orders=temp;
                    }
                    else{
                        Order* currOrder=currCustomer->orders;

                        while(currOrder->next){
                            currOrder=currOrder->next;
                        }

                        currOrder->next=temp;
                        temp->prev=currOrder;
                    }
                    break;
                }
                currCustomer=currCustomer->next;
            }
        }
    }
}

bool validateIndex(int index){
    if(headCustomer[index]) return true;
    else return false;
}

int calculatePayment(char menuName[], int quantity){
    currMenu=headMenu;
    while(currMenu){
        if(!strcmp(currMenu->menuName,menuName)) break;
    }
    return currMenu->price*quantity;
}

void printPayment(int index){
    Customer* currCustomer=headCustomer[index];

    while(currCustomer){
        printf("%s\n", currCustomer->customerName);

        int i=1;
        int total=0;
        Order* currOrder=currCustomer->orders;
        while(currOrder){
            printf("[%d] %s x%d\n", i, currOrder->orderName, currOrder->quantity);
            total+=calculatePayment(currOrder->orderName, currOrder->quantity);
        }

        printf("Total: Rp%d\n", total);
    }
}