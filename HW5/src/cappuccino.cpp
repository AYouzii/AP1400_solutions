#include "cappuccino.h"

Cappuccino::Cappuccino()
	: EspressoBased(), side_items(std::vector<Ingredient*>())
{
	name = std::string("Cappuccino");

	ingredients.push_back(new Espresso(2));
	ingredients.push_back(new Milk(2));
	ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& cap)
	: EspressoBased(cap), side_items(std::vector<Ingredient*>())
{
	for (auto cit = cap.side_items.cbegin(); cit != cap.side_items.cend(); ++cit) {
		side_items.push_back((*cit)->clone());
	}
}

Cappuccino::~Cappuccino()
{
	for (auto& si : side_items) {
		delete si;
	}
	std::vector<Ingredient*>().swap(side_items);
//	side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap)
{
	if (this != &cap) {
		EspressoBased::operator=(cap);
		side_items = std::vector<Ingredient*>();
		for (auto cit = cap.side_items.cbegin(); cit != cap.side_items.cend(); ++cit) {
			side_items.push_back((*cit)->clone());
		}
	}
}

std::string Cappuccino::get_name()
{
	return name;
}

double Cappuccino::price()
{
	double total = 0;
	for (std::vector<Ingredient*>::const_iterator ci = ingredients.cbegin(); ci != ingredients.cend(); ++ci) {
		total += (*ci)->price();
	}

	for (std::vector<Ingredient*>::const_iterator ci = side_items.cbegin(); ci != side_items.cend(); ++ci) {
		total += (*ci)->price();
	}

	return total;
}

void Cappuccino::add_side_item(Ingredient* side)
{
	side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items()
{
	return side_items;
}
