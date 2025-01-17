#pragma once
#include <string>
#include <iostream>
#include <deque>
#include "Item.h"

/////////////////////////////
// Comparators for Sorting //
/////////////////////////////

// More examples here:
// https://www.geeksforgeeks.org/comparator-class-in-c-with-examples/

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return a.getCategory() < b.getCategory();
	}
} CategoryComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return 	a.getName() < b.getName();
	}
} NameComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return a.getPrice() < b.getPrice();
	}
} PriceComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return a.getSerial() < b.getSerial();
	}
} SerialComparator;

enum SortingCriteria { CATEGORY = 0, NAME = 1, PRICE = 2, SERIAL = 3 };

//////////////////////
// Class Definition //
//////////////////////

class Store
{
public:

	/////////////////
	// Constructor //
	/////////////////

	Store(std::string storeName,std::string inventoryFileName);

	/////////////////////////
	// getters and setters //
	/////////////////////////

	std::string getName()const;
	std::string getSortedProductList(SortingCriteria sortingCritieria)const;
	std::string getProductListFilteredByCategory(ItemCategory category)const;

	///////////////
	// operators //
	///////////////

	// Element access operator for the store's items
	Item operator[](const int itemNumber) const;

	// operator << for easy printing, prints the name of the store and the products
	// with their indexes
	friend std::ostream& operator<<(std::ostream& os, const Store& store);

private:

	// Helper Method, reads a '.csv' file and adding the items to the products list.
	void getInventoryFromFile(const std::string inventoryFileName);

	////////////
	// Fields //
	////////////

	std::string _storeName;
	std::deque<Item> _products;
};
