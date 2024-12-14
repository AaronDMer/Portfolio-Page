#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct MenuItem {
    int id;
    string name;
    double price;
};

void placeCakeOrder(const MenuItem menu[], int size, int orders[], int& orderCount, int maxOrders);
void placeLayerOrder(const MenuItem layerMenu[], int size, int layerOrders[], int& layerOrderCount, int maxLayers);
void generateBill(const MenuItem menu[], int orders[], int orderCount, const MenuItem layerMenu[], int layerOrders[], int layerOrderCount);
void deleteCakeOrder(int orders[], int& orderCount);

int main() {
    MenuItem menu[] = {
        {1, "Chiffon Cake", 3.50},
        {2, "Buttered Cake", 2.49},
        {3, "Moist Cake", 1.50},
        {4, "Sponge Cake", 0.99}
    };

    MenuItem layerMenu[] = {
        {1, "1 Layer", 0.75},
        {2, "2 Layers", 1.00},
        {3, "3 Layers", 1.65}
    };

    const int maxOrders = 10;  // Maximum number of cake orders
    const int maxLayers = 10;  // Maximum number of layer orders
    int orders[maxOrders] = {0}, orderCount = 0;
    int layerOrders[maxLayers] = {0}, layerOrderCount = 0;

    string name;
    int choice;

    cout << "WELCOME to PURRfect Pastries🐈! We are pleased to serve you.\n";
    cout << "Kindly state your name for smooth transaction.\n\n";
    cout << "Enter your name here: ";
    cin.ignore();
    getline(cin, name);
    cout << "\nThank you, " << name << "! What would you like to do today?\n";

    do {
        cout << "\nMain Menu:\n"
             << "1. Place Cake Order\n"
             << "2. Add Cake Layer(s)\n"
             << "3. Delete Cake Order\n"
             << "4. Generate Bill\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                placeCakeOrder(menu, 4, orders, orderCount, maxOrders);
                break;
            case 2:
                placeLayerOrder(layerMenu, 3, layerOrders, layerOrderCount, maxLayers);
                break;
            case 3:
                deleteCakeOrder(orders, orderCount);
                break;
            case 4:
                generateBill(menu, orders, orderCount, layerMenu, layerOrders, layerOrderCount);
                break;
            case 5:
                cout << "\nThank you for visiting PURRfect Pastries!\n"
                     << "Where every bite is a whisker of delight!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void placeCakeOrder(const MenuItem menu[], int size, int orders[], int& orderCount, int maxOrders) {
    if (orderCount >= maxOrders) {
        cout << "You have reached the maximum number of orders.\n";
        return;
    }

    int id;
    char more;

    cout << "\nCake Menu:\n";
    cout << left << setw(5) << "ID" << setw(20) << "Item" << "Price\n";
    cout << "-----------------------------------\n";
    for (int i = 0; i < size; ++i) {
        cout << left << setw(5) << menu[i].id << setw(20) << menu[i].name
             << "$" << fixed << setprecision(2) << menu[i].price << "\n";
    }
    cout << "-----------------------------------\n";

    do {
        cout << "\nEnter the ID of the cake you want to order: ";
        cin >> id;

        bool found = false;
        for (int i = 0; i < size; ++i) {
            if (menu[i].id == id) {
                orders[orderCount++] = id;
                cout << menu[i].name << " has been added to your order.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid ID. Please try again.\n";
        }

        if (orderCount < maxOrders) {
            cout << "Do you want to order more cakes? (y/n): ";
            cin >> more;
        } else {
            cout << "You have reached the maximum number of orders.\n";
            break;
        }
    } while (more == 'y' || more == 'Y');
}

void placeLayerOrder(const MenuItem layerMenu[], int size, int layerOrders[], int& layerOrderCount, int maxLayers) {
    if (layerOrderCount >= maxLayers) {
        cout << "You have reached the maximum number of layer orders.\n";
        return;
    }

    int id;
    char more;
    do {
        cout << "\nLayer Options:\n";
        cout << left << setw(5) << "ID" << setw(20) << "Item" << "Price\n";
        cout << "-----------------------------------\n";
        for (int i = 0; i < size; ++i) {
            cout << left << setw(5) << layerMenu[i].id << setw(20) << layerMenu[i].name
                 << "$" << fixed << setprecision(2) << layerMenu[i].price << "\n";
        }
        cout << "-----------------------------------\n";

        cout << "\nEnter the ID of the layer option you want to add: ";
        cin >> id;

        bool found = false;
        for (int i = 0; i < size; ++i) {
            if (layerMenu[i].id == id) {
                layerOrders[layerOrderCount++] = id;
                cout << layerMenu[i].name << " has been added to your cake.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid ID. Please try again.\n";
        }

        if (layerOrderCount < maxLayers) {
            cout << "Do you want to add more layers? (y/n): ";
            cin >> more;
        } else {
            cout << "You have reached the maximum number of layer orders.\n";
            break;
        }
    } while (more == 'y' || more == 'Y');
}

void deleteCakeOrder(int orders[], int& orderCount) {
    if (orderCount == 0) {
        cout << "\nNo orders to delete.\n";
        return;
    }

    int id, index = -1;
    cout << "\nCurrent Cake Orders:\n";
    for (int i = 0; i < orderCount; ++i) {
        cout << "ID: " << orders[i] << "\n";
    }

    cout << "\nEnter the ID of the cake you want to delete: ";
    cin >> id;

    for (int i = 0; i < orderCount; ++i) {
        if (orders[i] == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "No such cake found in your order.\n";
        return;
    }

    for (int i = index; i < orderCount - 1; ++i) {
        orders[i] = orders[i + 1];
    }

    --orderCount;
    cout << "Cake with ID " << id << " has been deleted from your order.\n";
}

void generateBill(const MenuItem menu[], int orders[], int orderCount, const MenuItem layerMenu[], int layerOrders[], int layerOrderCount) {
    if (orderCount == 0 && layerOrderCount == 0) {
        cout << "\nYou have not placed any orders yet.\n";
        return;
    }

    double total = 0;
    cout << "\nYour Order Summary:\n";
    cout << left << setw(20) << "Item" << "Price\n";
    cout << "-------------------------------\n";

    for (int i = 0; i < orderCount; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (menu[j].id == orders[i]) {
                cout << left << setw(20) << menu[j].name << "$" << fixed << setprecision(2) << menu[j].price << "\n";
                total += menu[j].price;
                break;
            }
        }
    }

    for (int i = 0; i < layerOrderCount; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (layerMenu[j].id == layerOrders[i]) {
                cout << left << setw(20) << layerMenu[j].name << "$" << fixed << setprecision(2) << layerMenu[j].price << "\n";
                total += layerMenu[j].price;
                break;
            }
        }
    }

    cout << "-------------------------------\n";
    cout << left << setw(20) << "Total" << "$" << fixed << setprecision(2) << total << "\n";
}
