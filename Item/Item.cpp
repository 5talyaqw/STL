#include "Item.h"
#include <stdexcept>

//constructor
Item::Item(std::string name, std::string serialNumber, double unitPrice, ItemCategory category) : _name(name), _serialNumber(serialNumber), _unitPrice(unitPrice), _category(category), _count(1)
{
	if (unitPrice < 0)
	{
		throw std::invalid_argument("price cannot be negative");
	}

	if (serialNumber.size() != 5)
	{
		throw std::invalid_argument("serial number cannot be over 5 characters long");
	}
}

void Item::increaseCount(int num)
{
	_count += num;
}

void Item::decreaseCount(int num)
{
	_count -= num;
}

double Item::totalPrice() const
{
	return _count * _unitPrice;
}

void Item::setCount(int newCount)
{
	if (newCount < 0)
	{
		throw std::invalid_argument("count cannot be negative");
	}
	_count = newCount;
}

bool Item::operator<(const Item& other) const
{
	return _serialNumber < other._serialNumber;
}

bool Item::operator>(const Item& other) const
{
	return _serialNumber > other._serialNumber;
}

bool Item::operator==(const Item& other) const
{
	return _serialNumber == other._serialNumber;;
}

std::string Item::getName() const
{
	return _name;
}

std::string Item::getSerial() const
{
	return _serialNumber;
}

int Item::getCount() const
{
	return _count;
}

double Item::getPrice() const
{
	return _unitPrice;
}

ItemCategory Item::getCategory() const
{
	return _category;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << "[Serial: " << item.getSerial()
		<< ", Name: " << item.getName()
		<< ", Category: " << getItemCategoryString(item.getCategory())
		<< ", Price: " << item.getPrice()
		<< ", Amount: " << item.getCount() << "]";

	return os;
}
