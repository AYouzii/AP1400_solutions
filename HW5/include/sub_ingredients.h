#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFCLASS(className, pricePerUnit) \
class className : public Ingredient\
{\
public: \
	className(size_t units) : Ingredient(pricePerUnit, units) \
	{ \
		name = #className; \
	} \
\
	className(const className& other) : Ingredient(other) \
	{ \
		price_unit = other.price_unit; \
		units = other.units; \
		name = other.name; \
	} \
	virtual std::string get_name() const override { return this->name; } \
\
	virtual className* clone() const override { return new className(*this); } \
}


DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H