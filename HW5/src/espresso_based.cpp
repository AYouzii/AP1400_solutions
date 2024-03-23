#include "espresso_based.h"

std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
	return this->ingredients;
}

EspressoBased::EspressoBased()
	: ingredients(std::vector<Ingredient*>()), name("") {}

EspressoBased::EspressoBased(const EspressoBased& esp)
	: ingredients(std::vector<Ingredient*>()), name(esp.name)
{
	if (this != &esp) {
		for (auto cit = esp.ingredients.cbegin(); cit != esp.ingredients.cend(); ++cit) {
			ingredients.push_back((*cit)->clone());
		}
	}
}

void EspressoBased::operator=(const EspressoBased& esp)
{
	if (this != &esp) {
		ingredients = std::vector<Ingredient*>();
		name = esp.name;
		for (auto cit = esp.ingredients.cbegin(); cit != esp.ingredients.cend(); ++cit) {
			ingredients.push_back((*cit)->clone());
		}
	}
}

EspressoBased::~EspressoBased()
{
	for (auto& i : ingredients)
	{
		delete i;
	}
//	ingredients.clear();
	std::vector<Ingredient*>().swap(ingredients);
}

void EspressoBased::brew()
{
	// side items not included
	const auto& ings = get_ingredients();
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 50, 10 };

	Sleep(500);

	for (auto cit = ings.crbegin(); cit != ings.crend(); ++cit) {
		SetConsoleCursorPosition(hd, pos);
		std::cout << "|" << std::setw(20)
			<< std::setfill(' ') << (*cit)->get_name()
			<< "|" << std::endl;
		Sleep(500);
		pos.Y--;
	}

	system("cls");
}
