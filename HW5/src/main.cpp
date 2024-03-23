#include <iostream>
#include <gtest/gtest.h>
#include "ingredient.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "cappuccino.h"
#include "mocha.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        Cappuccino cap;
        cap.add_side_item(new Chocolate(2));
        Cappuccino copy(cap);
        const auto& ingredients = copy.get_side_items();
        for (auto cit = ingredients.cbegin(); cit != ingredients.cend(); ++cit) {
            std::cout << (*cit)->get_name() << " " << (*cit)->price() << '\n';
        }
        std::cout << "total price: " << copy.price() << std::endl;
		//std::cin.get();
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}