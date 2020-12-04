const int MAX_ELEMENT=26;

struct Menu {
    char menuName[255];
    int price,quantity;
    Menu *next, *prev;
} *headMenu, *currMenu, *tailMenu;

struct Order {
    char orderName[255];
    int quantity;
    Order *next, *prev;
};

struct Customer {
    char customerName[255];
    Order *orders;
    Customer *next;
} *headCustomer[MAX_ELEMENT], *tailCustomer[MAX_ELEMENT];