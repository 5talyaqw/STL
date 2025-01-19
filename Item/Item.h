#pragma once
#include<iostream>
#include<string>

enum ItemCategory { NONE = 0, FOOD = 1, PHARM = 2, CLEANING = 3, HOME = 4 };

static std::string getItemCategoryString(const ItemCategory type)
{
    if (type == NONE)
        return "NONE";
    else if (type == FOOD)
        return "Food";
    else if (type == PHARM)
        return "Pharm";
    else if (type == CLEANING)
        return "Cleaning";
    else if (type == HOME)
        return "Home";
    return "Unknown";
}

class Item
{
public:

    /////////////////
    // Constructor //
    /////////////////

    Item(std::string name, std::string serialNumber, double unitPrice, ItemCategory category);

    /////////////
    // methods //
    /////////////

    double totalPrice() const; //returns _count * _unitPrice

    ///////////////
    // operators //
    ///////////////
    void setCount(int newCount);
    bool operator <(const Item& other) const; //compares the _serialNumber of those items.
    bool operator >(const Item& other) const; //compares the _serialNumber of those items.
    bool operator ==(const Item& other) const; //compares the _serialNumber of those items.
    friend std::ostream& operator<<(std::ostream& os, const Item& item);

    /////////////////////////
    // getters and setters //
    /////////////////////////
    std::string getName()const;
    std::string getSerial()const;
    int getCount()const;
    double getPrice()const;
    ItemCategory getCategory()const;


private:
    std::string _name;
    std::string _serialNumber;
    int _count;
    double _unitPrice;
    ItemCategory _category;
};