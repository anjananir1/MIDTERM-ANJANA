#pragma once
#include <string>
#include <iostream>
using namespace std;

// Base class for all lost items
class LostItem {
protected:
    string name;
    int id;

public:
    LostItem(string n, int i) : name(n), id(i) {}
    virtual void display() = 0; // must be implemented by child classes

    int getId() { return id; }
    string getName() { return name; }

    virtual ~LostItem() {}
};

// Class for more valuable items like phones or wallets
class ValuableItem : public LostItem {
public:
    ValuableItem(string n, int i) : LostItem(n, i) {}
    void display() override; // defined in LostItem.cpp
};

// Class for basic items like bottles or notebooks
class NonValuableItem : public LostItem {
public:
    NonValuableItem(string n, int i) : LostItem(n, i) {}

    void display() override {
        cout << name << " (Non-Valuable), ID: " << id << endl;
    }
};

