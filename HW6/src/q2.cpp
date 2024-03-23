#include "q2.h"
namespace q2 {

	std::vector<Patient> read_file(std::string filename)
	{
		std::ifstream fin;
		fin.open(filename, std::ios::in);
		if (fin.is_open()) {
			std::vector<Patient> patients;

			std::string buffer;

			std::getline(fin, buffer);
			std::getline(fin, buffer);
			while (std::getline(fin, buffer)) {
				std::istringstream iss(buffer);
				Patient p;
				std::string name, surname, age, smokes, areaQ, aklhol;
				std::getline(iss, name, ',');
				std::getline(iss, surname, ',');
				std::getline(iss, age, ',');
				std::getline(iss, smokes, ',');
				std::getline(iss, areaQ, ',');
				std::getline(iss, aklhol, ',');
				name.erase(0, name.find_first_not_of(" "));
				name.erase(name.find_last_not_of(" ") + 1);
				surname.erase(0, surname.find_first_not_of(" "));
				surname.erase(surname.find_last_not_of(" ") + 1);
				p.name = name + " " + surname;
				p.age = std::stoi(age);
				p.smokes = std::stoi(smokes);
				p.area_q = std::stoi(areaQ);
				p.alkhol = std::stoi(aklhol);
				patients.push_back(p);
			}
			return patients;
		}
		else {
			std::cerr << "Cannot open file " << filename << std::endl;
			return std::vector<Patient>();
		}
	}

	void sort(std::vector<Patient>& patients)
	{
		std::function<bool(const Patient&, const Patient&)> compare = [](const Patient& p1, const Patient& p2) {
			size_t p1Proba = 3 * p1.age + 5 * p1.smokes + 2 * p1.area_q + 4 * p1.alkhol;
			size_t p2Proba = 3 * p2.age + 5 * p2.smokes + 2 * p2.area_q + 4 * p2.alkhol;
			return p1Proba > p2Proba;
		};
		std::sort(patients.begin(), patients.end(), compare);
	}

}
