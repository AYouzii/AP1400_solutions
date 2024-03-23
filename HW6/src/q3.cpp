#include "q3.h"

namespace q3 {
	std::priority_queue<Flight> gather_flights(std::string filename)
	{
		std::ifstream fin;
		fin.open(filename, std::ios::in);

		if (fin.is_open()) {
			std::priority_queue<Flight> flights;
			std::string buffer;
			std::function<void(std::string&)> removeHeadTailSpaces = [](std::string& s) {
				s.erase(0, s.find_first_not_of(" "));
				s.erase(s.find_last_not_of(" ") + 1);
			};

			std::function<int(const std::string&)> getTimeFromConnectionTime = [](const std::string& time) -> int {
				// time format: %h%m, return connection time in minutes
				size_t positionH = time.find_first_of("h");
				size_t positionM = time.find_first_of("m");
				if (positionH != time.npos) {
					// at least one hour
					std::string hours = time.substr(0, positionH);
					if (positionM != time.npos) {
						std::string minutes = time.substr(positionH + 1, positionM - positionH - 1);
						return std::stoi(hours) * 60 + std::stoi(minutes);
					}
					else {
						return std::stoi(hours) * 60;
					}
				}
				else {
					if (positionM != time.npos) {
						std::string minutes = time.substr(0, positionM);
						return std::stoi(minutes);
					}
					else {
						throw std::runtime_error("Invalid format of connection times");
					}
				}
			};
			while (std::getline(fin, buffer)) {
				Flight f;
				std::istringstream iss(buffer);
				std::string flightNumber, duration, connections, connectionTimes, price;
				std::string id;
				std::getline(iss, id, '-');
				std::getline(iss, flightNumber, '-');
				std::getline(iss, duration, '-');
				std::getline(iss, connections, '-');
				std::getline(iss, connectionTimes, '-');
				std::getline(iss, price, '-');

				removeHeadTailSpaces(flightNumber);
				removeHeadTailSpaces(duration);
				removeHeadTailSpaces(connections);
				removeHeadTailSpaces(connectionTimes);
				removeHeadTailSpaces(price);

				size_t positionOfColon = 0;
				positionOfColon = flightNumber.find_first_of(":");
				flightNumber = flightNumber.substr(positionOfColon + 1, flightNumber.size() - positionOfColon - 1);
				f.flight_number = flightNumber;

				positionOfColon = duration.find_first_of(":");
				duration = duration.substr(positionOfColon + 1, duration.size() - positionOfColon - 1);
				f.duration = getTimeFromConnectionTime(duration);

				positionOfColon = connections.find_first_of(":");
				connections = connections.substr(positionOfColon + 1, connections.size() - positionOfColon - 1);
				f.connections = std::stoi(connections);

				positionOfColon = connectionTimes.find_first_of(":");
				connectionTimes = connectionTimes.substr(positionOfColon + 1, connectionTimes.size() - positionOfColon - 1);
				std::istringstream streamConnectionTimes(connectionTimes);
				std::string time;
				f.connection_times = 0;
				for (unsigned i = 0; i < f.connections; ++i) {
					std::getline(streamConnectionTimes, time, ',');
					f.connection_times += getTimeFromConnectionTime(time);
				}

				positionOfColon = price.find_first_of(":");
				price = price.substr(positionOfColon + 1, price.size() - positionOfColon - 1);
				f.price = std::stoi(price);

				flights.push(f);
			}
			return flights;
		}
		else {
			std::cerr << "Cannot open file " << filename << std::endl;
			return std::priority_queue<Flight>();
		}
	}

	bool operator < (const Flight& f1, const Flight& f2)
	{
		size_t sumF1 = f1.duration + f1.connection_times + 3 * f1.price;
		size_t sumF2 = f2.duration + f2.connection_times + 3 * f2.price;
		return sumF1 > sumF2;
	}

}