#include "Customer.h"

//constructor
Customer::Customer(std::string name) : _name(name){}

//default construtor
Customer::Customer() : _name(""){}

//destructor
Customer::~Customer()
{
	for (auto it = _shoppingCarts.begin(); it != _shoppingCarts.end(); ++it)
	{
		delete it->second; //deleting dynam allocated carts
	}
}

//creating new shopping cart
void Customer::createNewShoppingCart(std::string shoppingCartName)
{
	_shoppingCarts[shoppingCartName] = new std::set<Item>();
}

//calculating the sum of a shopping cart
double Customer::shoppingCartSum(std::string shoppingCartName)
{
	double sum = 0.0;
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end())
	{
		for (const auto& item: *(it->second))
		{
			sum += item.getPrice() * item.getCount();
		}
	}
	return sum;
}

//calculating the total of all shopping carts
double Customer::totalSum() const
{
	double total = 0.0;
	for (auto it = _shoppingCarts.begin(); it != _shoppingCarts.end(); ++it)
	{
		for (auto itemIt = it->second->begin(); itemIt != it->second->end(); ++itemIt)
		{
			total += itemIt->getPrice() * itemIt->getCount();
		}
	}
	return total;
}

//adding item
void Customer::addItem(const Item& item, std::string shoppingCartName)
{
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end() && it->second)
	{
		auto& cart = *(it->second);
		auto itemIt = cart.find(item);
		if (itemIt != cart.end())
		{
			Item updatedItem = *itemIt;
			updatedItem.setCount(updatedItem.getCount() + 1);
			cart.erase(itemIt); //remove the old item
			cart.insert(updatedItem); //insert the updated item
		}
		else
		{
			Item newItem = item;
			newItem.setCount(1);
			cart.insert(newItem);
		}
	}
}

//removing item
void Customer::removeItem(const Item& item, std::string shoppingCartName)
{
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end() && it->second)
	{
		auto& cart = *(it->second);
		auto itemIt = cart.find(item);
		if (itemIt != cart.end())
		{
			Item updatedItem = *itemIt;
			if (updatedItem.getCount() > 1)
			{
				updatedItem.setCount(updatedItem.getCount() - 1);
				cart.erase(itemIt); //remove the old item
				cart.insert(updatedItem); //insert the updated item
			}
			else
			{
				//if count is 1 remove the item from the cart
				cart.erase(itemIt);
			}
		}
	}
}

//getting name of the stroe
std::string Customer::getName() const
{
	return _name;
}

//getting the shopping cart
std::set<Item>* Customer::getShoppingCart(std::string shoppingCartName) const
{
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end())
	{
		return it->second;
	}
	return nullptr;
}
