#include "mocha.h"

Mocha::Mocha()
	: EspressoBased(), side_items(std::vector<Ingredient*>())
{
	name = std::string("Mocha");

	ingredients.push_back(new Espresso(2));
	ingredients.push_back(new Milk(2));
	ingredients.push_back(new MilkFoam(1));
	ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& mocha)
	: EspressoBased(mocha), side_items(std::vector<Ingredient*>())
{
	for (auto cit = mocha.side_items.cbegin(); cit != mocha.side_items.cend(); ++cit) {
		side_items.push_back((*cit)->clone());
	}
}

Mocha::~Mocha()
{
	for (auto& si : side_items) {
		delete si;
	}
	std::vector<Ingredient*>().swap(side_items);
//	side_items.clear();

}

void Mocha::operator=(const Mocha& mocha)
{
	if (this != &mocha) {
		EspressoBased::operator=(mocha);
		side_items = std::vector<Ingredient*>();
		for (auto cit = mocha.side_items.cbegin(); cit != mocha.side_items.cend(); ++cit) {
			side_items.push_back((*cit)->clone());
		}
	}
}

std::string Mocha::get_name()
{
	return name;
}

double Mocha::price()
{
	double total = 0;
	for (std::vector<Ingredient*>::const_iterator ci = ingredients.cbegin(); ci != ingredients.cend(); ++ci) {
		total += (*ci)->price();
	}

	for (auto ci = side_items.cbegin(); ci != side_items.cend(); ++ci) {
		total += (*ci)->price();
	}

	return total;
}

void Mocha::add_side_item(Ingredient* side)
{
	side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items()
{
	return side_items;
}
