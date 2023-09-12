#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
#include "TemperatureData.h"
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {
	// Implement this function
}

LinkedList::~LinkedList() {
	// Implement this function
	this->clear();
}

LinkedList::LinkedList(const LinkedList& source) : head(nullptr), tail(nullptr) {
	// Implement this function

	Node* node = source.head;
	Node* temp;

    while (node != nullptr) {
	   this->insert(node->data.id, node->data.year, node->data.month, node->data.temperature);
	   temp = node;
	   node = node->next;
    }

	this->tail = temp;
	node = nullptr;
	temp = nullptr;
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// Implement this function

	this->clear();
	Node* node = source.head;
	Node* temp;
	
	while (node != nullptr) {
		this->insert(node->data.id, node->data.year, node->data.month, node->data.temperature);
		temp = node;
		node = node->next;
	}

	this->tail = temp;
	node = nullptr;
	temp = nullptr;
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	// Implement this function

	if (temperature == -99.99) {
		return;
	}

	Node* node = new Node(location, year, month, temperature);

	if (head == nullptr && tail == nullptr) { //nothing in list
		head = node;
		tail = node;
	} else if (node->data < head->data) { //less than head
		node->next = head;
		head = node;
	} else if (tail->data < node->data) { //greater than tail
		tail->next = node;
		tail = node;
	} else {
		Node* curr = head;
		Node* currnext = head->next;

		while (curr->data < node->data && currnext->data < node->data) {
			curr = currnext;
			currnext = currnext->next;
		}

		node->next = currnext;
		curr->next = node;
	}
}

void LinkedList::clear() {
	// Implement this function

	Node* node = head;
	while (node != nullptr) {
		Node* temp = node;
		node = node->next;
		delete temp;
	}

	head = nullptr;
	tail = nullptr;
	delete node;
}

Node* LinkedList::getHead() const {
	// Implement this function it will be used to help grade other functions
	return head;
}

string LinkedList::print() const {
	string outputString;
	// Implement this function

	Node* temp = head;
	stringstream ss;
	while(temp != nullptr){
		ss << temp->data.id << " " << temp->data.year << " " << temp->data.month << " " << temp->data.temperature << endl;
		temp = temp->next;
	}
	outputString = ss.str();

	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
