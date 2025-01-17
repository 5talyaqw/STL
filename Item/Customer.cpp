#include "Customer.h"

Customer::Customer(std::string name) : _name(name){}

Customer::Customer() : _name(""){}

Customer::~Customer()
{
	for (auto& cart : _shoppingCarts)
	{
		delete cart.second; //deleting dynamically allocated carys
	}
}

void Customer::createNewShoppingCart(std::string shoppingCartName)
{
	_shoppingCarts[shoppingCartName] = new std::set<Item>();
}

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

double Customer::totalSum()
{
	double total = 0.0;
	for (auto& cart : _shoppingCarts)
	{
		for (auto& item : *(cart.second))
		{
			total += item.getPrice() * item.getCount();
		}
	}
	return total;
}

void Customer::addItem(const Item& item, std::string shoppingCartName)
{
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end())
	{
		auto& cart = it->second;
		auto itemIt = cart->find(item);
		if (itemIt != cart->end())
		{
			if (itemIt->getCount() > 1)
			{
				itemIt->increaseCount(1);
			}
			else
			{
				cart->erase(itemIt);
			}
		}
	}
}

void Customer::removeItem(const Item& item, std::string shoppingCartName)
{
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end())
	{
		auto& cart = it->second;
		auto itemIt = cart->find(item);
		if (itemIt != cart->end())
		{
			if (itemIt->getCount() > 1)
			{
				itemIt->decreaseCount(1);
			}
			else
			{
				cart->erase(itemIt);
			}
		}
	}
}

std::string Customer::getName() const
{
	return _name;
}

std::set<Item>* Customer::getShoppingCart(std::string shoppingCartName) const
{
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end())
	{
		return it->second;
	}
	return nullptr;
}
