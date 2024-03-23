#ifndef Q3_H
#define Q3_H

#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

namespace q3 {
	struct Flight
	{
		std::string flight_number;
		size_t duration;
		size_t connections;
		size_t connection_times;
		size_t price;

	};

	bool operator < (const Flight& f1, const Flight& f2);

	std::priority_queue<Flight> gather_flights(std::string filename);

}
#endif //Q3_H