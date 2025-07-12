#include <iostream>
#include <fstream>
#include <string>
#include "LostItem.h"
using namespace std;

const int SIZE = 5; // number of items to track

// Function to show sizes of common data types
void printDataSizes() {
    cout << "📦 Welcome to the Lost & Found Tracker!\n";
    cout << "\n🔍 Data Type Sizes:\n";
    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "Size of float: " << sizeof(float) << " bytes\n";
    cout << "Size of char: " << sizeof(char) << " bytes\n\n";
}

// Basic binary search function to find an item by its ID
int binarySearchById(LostItem* arr[], int size, int targetId) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid]->getId() == targetId) return mid;
        if (arr[mid]->getId() < targetId) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // not found
}

int main() {
    printDataSizes(); // show data type sizes

    // create dynamic array to store pointers to LostItem objects
    LostItem** inventory = new LostItem*[SIZE];

    // loop to input items
    for (int i = 0; i < SIZE; i++) {
        string name;
        int id, type;

        cout << "\n--- Item " << (i + 1) << " ---\n";

        cout << "Enter item name: ";
        cin.ignore(); // clears leftover newline
        getline(cin, name); // allows spaces in name

        cout << "Enter item ID (number): ";
        cin >> id;

        cout << "Select item type:\n";
        cout << "1 = Valuable\n";
        cout << "2 = Non-Valuable\n";
        cout << "Your choice: ";
        cin >> type;


        // decide which kind of object to create
        if (type == 1)
            inventory[i] = new ValuableItem(name, id);
        else
            inventory[i] = new NonValuableItem(name, id);
    }

    // show all items
    cout << "\n📋 All Logged Items:\n";
    for (int i = 0; i < SIZE; i++) {
        inventory[i]->display(); // polymorphic call
    }

    // ask user to search by ID
    int searchId;
    cout << "\n🔎 Enter ID to search: ";
    cin >> searchId;

    int index = binarySearchById(inventory, SIZE, searchId);
    if (index != -1) {
        cout << "✅ Item found:\n";
        inventory[index]->display();

        // log the claimed item to file
        ofstream out("transactions.txt", ios::app);
        if (out.is_open()) {
            out << "Claimed: " << inventory[index]->getName() << ", ID: " << inventory[index]->getId() << endl;
            out.close();
        } else {
            cout << "⚠️ Could not open transactions.txt for writing.\n";
        }
    } else {
        cout << "❌ Item not found.\n";
    }

    // delete dynamic memory
    for (int i = 0; i < SIZE; i++) {
        delete inventory[i];
    }
    delete[] inventory;

    return 0;
}

