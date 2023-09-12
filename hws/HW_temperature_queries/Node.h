#ifndef NODE
#define NODE

#include "TemperatureData.h"

struct Node {
	Node* next;
	TemperatureData data;

	// Default constructor
	Node(); // remember to initialize next to nullptr
	Node(std::string id, int year, int month, double temperature); // remember to initialize next to nullptr

	// This operator will allow you to just ask if a node is smaller than another
	//  rather than looking at all of the location, temperature and date information
	bool operator<(const Node& b);

  // The function below is written. Do not modify it
	virtual ~Node() {}
};

#endif
