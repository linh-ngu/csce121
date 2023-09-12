#include "TemperatureDatabase.h"

#include <fstream>
#include <sstream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// Implement this function for part 1
	
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Error: Unable to open " << filename << ".dat" << endl;
		return;
    }

	string line;

	while (getline(file, line)) {
		string id; int year; int month; double temperature;
		istringstream ss(line);
		ss >> id;
		if (ss.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		}
		ss >> year;
		if (ss.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		} else if (year < 1800 || year > 2022) {
			cout << "Error: Invalid year " << year << endl;
			continue;
		}
		ss >> month;
		if (ss.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		} else if (month < 1 || month > 12) {
			cout << "Error: Invalid month " << month << endl;
			continue;
		}
		ss >> temperature;
		if (ss.fail()) {
			cout << "Error: Other invalid input" << endl;
			continue;
		} else if ((temperature < -50.0 || temperature > 50.0) && temperature != -99.99) {
			cout << "Error: Invalid temperature " << temperature << endl;
			continue;
		}

		records.insert(id, year, month, temperature);
	}
}

// Do not modify
void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

// void TemperatureDatabase::performQuery(const string& filename) {
// 	// Implement this function for part 2
// 	//  Leave it blank for part 1
// }
