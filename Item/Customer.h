#pragma once
#include"Item.h"
#include<set>
#include<map>

class Customer
{
public:
	// constructors
	Customer(std::string name);
	Customer();

	// destructors
	~Customer();

	// methods
	void createNewShoppingCart(std::string shoppingCartName);

	double shoppingCartSum(std::string shoppingCartName); // returns the payment sum for a given shopping cart;
	double totalSum();//returns the total sum for payment

	void addItem(const Item& item, std::string shoppingCartName);//add item to the set
	void removeItem(const Item& item, std::string shoppingCartName);//remove item from the set

	//get and set functions

	std::string getName()const;	// returns the customer name
	std::set<Item>* getShoppingCart(std::string shoppingCartName)const; // returns the shopping cart with the given name

private:
	std::string _name; // Customer name
	std::map<std::string, std::set<Item>*> _shoppingCarts; // Shopping carts


};