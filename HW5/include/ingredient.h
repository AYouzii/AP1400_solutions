#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient
{
public:
	double get_price_unit() const;
	size_t get_units() const;
	virtual std::string get_name() const = 0; // pure virtual function
	virtual Ingredient* clone() const = 0; 

	double price() const; 

protected:
	Ingredient(double price_unit, size_t units)
		: price_unit(price_unit), units(units), name("") {}

	double price_unit;
	size_t units;
	std::string name;
};

inline double Ingredient::get_price_unit() const
{
	return price_unit;
}

inline size_t Ingredient::get_units() const
{
	return units;
}

inline double Ingredient::price() const
{
	return price_unit * units;
}

#endif // INGREDIENT_H