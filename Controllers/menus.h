#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"

void mainMenu();
void navigate(int prompt);
void addMenu();
void removeMenu();
void addCustomer();
void searchCustomer();
void viewWarteg();
void order();
void payment();
void exit();

void mainMenu(){
    printf("System: ");
    printf("%s\n", detectOS());
    date();

    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");

    int prompt;
    printf(">> ");
    scanf("%d", &prompt);
    getchar();
    navigate(prompt);
}

void navigate(int prompt){
    switch(prompt){
        case 1:
            system("CLS");
            addMenu();
            break;
        case 2:
            system("CLS");
            removeMenu();
            break;
        case 3:
            system("CLS");
            addCustomer();
            break;
        case 4:
            system("CLS");
            searchCustomer();
            break;
        case 5:
            system("CLS");
            viewWarteg();
            break;
        case 6:
            system("CLS");
            order();
            break;
        case 7:
            system("CLS");
            payment();
            break;
        case 8:
            system("CLS");
            exit();
            return;
        default:
            system("CLS");
            mainMenu();
    }
    system("CLS");
    mainMenu();
}

void addMenu(){
    char menuName[255];
    int price,quantity;

    while(1){
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", &menuName);
        getchar();

        bool flag=true;
        for(int i=0;i<strlen(menuName);i++){
            if(menuName[i] < 'a' || menuName[i] > 'z'){
                if(menuName[i] != ' '){
                    flag=false;
                    break;
                }
            }
        }

        if(flag) break;
    }
    
    while(1){
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price);

        if(price >= 1000 && price <= 50000) break;
    }

    while(1){
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quantity);

        if(quantity >= 1 && quantity <= 999) break;
    }

    appendMenu(menuName,price,quantity);
    puts("The dish has been added!");
    getchar();
    puts("Press enter to continue...");
    getchar();
}

void removeMenu(){
    puts("                  Bude's Menu");
    puts("=================================================");
    puts("  No.          Name          Quantity    Price  ");
    puts("=================================================");

    int count=1;
    currMenu=headMenu;
    while(currMenu){
        printf("%3d.   ", count);
        centering(currMenu->menuName);
        printf("    %03d     Rp%8d", currMenu->quantity, currMenu->price);
        puts("");

        currMenu=currMenu->next;
        count++;
    }

    char menuName[255];
    while(1){
        printf("Insert dish's name to be deleted: ");
        scanf("%[^\n]", &menuName);
        getchar();
        if(popMenu(menuName)){
            break;
        }
    }
    
    puts("The dish has been removed!");
    puts("Press enter to continue...");
    getchar();
}

void addCustomer(){
    char customerName[255];

    while(1){
        printf("Insert the customer's name [Without space]:");
        scanf("%[^\n]", &customerName);
        getchar();

        bool flag=true;
        for(int i=0;i<strlen(customerName);i++){
            if(customerName[i] < 'a' || customerName[i] > 'z'){
                if(customerName[i] < 'A' || customerName[i] > 'Z'){
                    flag=false;
                    break;
                }
            }
        }

        if(flag) break;
    }

    insertCustomer(customerName);
    puts("Customer has been added!");
    puts("Press enter to continue...");
    getchar();
}

void searchCustomer(){
    char customerName[255];
    
    while(1){
        printf("Insert the customer's name to be searched: ");
        scanf("%[^\n]", &customerName);
        getchar();

        bool flag=true;
        for(int i=0;i<strlen(customerName);i++){
            if(customerName[i] < 'a' || customerName[i] > 'z'){
                if(customerName[i] < 'A' || customerName[i] > 'Z'){
                    flag=false;
                    break;
                }
            }
        }

        if(flag) break;
    }

    if(search(customerName)){
        printf("%s is present\n", customerName);
    }
    else{
        printf("%s is not present\n", customerName);
    }

    puts("Press enter to continue...");
    getchar();
}

void viewWarteg(){
    puts("Customer's List");
    view();
    puts("Press enter to continue...");
    getchar();
}

void order(){
    char customerName[255];
    int quantity;

    while(1){
        printf("Insert the customer's name: ");
        scanf("%[^\n]", &customerName);
        getchar();

        bool flag=true;
        for(int i=0;i<strlen(customerName);i++){
            if(customerName[i] < 'a' || customerName[i] > 'z'){
                if(customerName[i] < 'A' || customerName[i] > 'Z'){
                    flag=false;
                    break;
                }
            }
        }

        if(flag){
            if(!search(customerName)){
                printf("%s is not present\n", customerName);
            }
            else break;
        }
    }

    printf("Insert the amount of dish: ");
    scanf("%d", &quantity);
    
    char orderName[255];
    int orderQuantity;

    int i=1;
    while(i<=quantity){
        printf("[%d] Insert the dish's name and quantity: ", i);
        scanf("%[^x]", &orderName);
        getchar();
        orderName[strlen(orderName)-1]='\0';
        scanf("%d", &orderQuantity);

        if(validateOrder(orderName, orderQuantity)){
            addOrder(customerName,orderName,orderQuantity);
            i++;
        }
    }

    puts("Order Success!");
    puts("Press enter to continue...");
    getchar();
}

void payment(){
    int index;

    while(1){
        printf("Insert the customer's index: ");
        scanf("%d", &index);

        if(validateIndex(index)) break;
    }
    
    printPayment(index);
    puts("Press enter to continue...");
    getchar();
}

void exit(){
    FILE *file = fopen("../Warung Bude/splash-screen.txt", "r");
    char input[255];
    while(fscanf(file,"%[^\n]\n", input) != EOF){
        printf("%s\n", input);
    }
    fclose(file);
}