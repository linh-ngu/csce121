// TODO: Implement this source file

#include <iostream>
#include <stdexcept>
#include "MyString.h"

using namespace std;

//constructor
MyString::MyString() : stringSize(0), stringCapacity(1), character(new char[1]) {
    character[stringSize] = '\0';
}

MyString::MyString(const MyString& str) : stringSize(str.size()), stringCapacity(str.capacity()), character(new char[str.capacity()]) {
    for (size_t i = 0; i < stringSize; i++) {
        character[i] = str.character[i];
    }
    character[stringSize] = '\0';
}

MyString::MyString(const char* str) : stringSize(0), stringCapacity(1), character(0) {
    size_t i = 0;
    while (str[i] != '\0') {
        i++;
    }
    stringSize = i;
    stringCapacity = i + 1;
    delete[] character;
    character = new char[stringCapacity];
    for (size_t i = 0; i < stringSize; i++) {
        character[i] = str[i];
    }
    character[stringSize] = '\0';
}

MyString::~MyString() {
    delete[] character;
}

void MyString::resize(size_t n) {
    char* oldcharacter = character;
    if (n >= stringCapacity) {
        stringCapacity = n;
        delete[] character;
        character = new char[n];
        for (size_t i = 0; i < stringSize; i++) {
            character[i] = oldcharacter[i];
        }
        stringSize = n - 1;
    }
    delete[] oldcharacter;
}

size_t MyString::capacity() const {
    return stringCapacity;
}

size_t MyString::size() const {
    return stringSize;
}

size_t MyString::length() const {
    return stringSize;
}

char* MyString::data() const {
    return character;
}

bool MyString::empty() const {
    if(character[0] == '\0'|| stringCapacity == 1) {
        return true;
    }
    return false;
}

const char& MyString::front() const {
    return character[0];
}

const char& MyString::at(size_t pos) const {
    if (pos >= stringSize) {
        throw invalid_argument("at: out of range");
    }
    return this->character[pos];
}

void MyString::clear() {
    for (size_t i = 0; i < stringSize; i++) {
        character[i] = '\0';
    }
    stringSize = 0;
    stringCapacity = 1;
}

ostream& operator<<(ostream& out, const MyString& str) {
    out << str.data();
    return out;
}

MyString& MyString::operator=(const MyString& str) {

    delete[] character;
    character = new char[str.capacity()];
    
    for (size_t i = 0; i < str.size(); i++) {
        this->character[i] = str.character[i];
    }
    
    stringSize = str.size();
    stringCapacity = str.capacity();
    character[stringSize] = '\0';

    return *this;
}

MyString& MyString::operator+=(const MyString& str) {
    if (str.at(0) == '\0') {
        return *this;
    }

    size_t idx = 0;
    while (str.character[idx] != '\0') {
        idx++;
    }
    char* newcharacter = new char[idx + stringCapacity];

    for (size_t i = 0; i < stringSize; i++) {
        newcharacter[i] = character[i];
    }

    for (size_t i = stringSize; i < stringSize + idx; i++) {
        newcharacter[i] = str.character[i - stringSize];
    }

    newcharacter[stringSize + idx] = '\0';

    delete [] character;
    character = newcharacter;
    stringSize = stringSize + idx;
    stringCapacity = stringCapacity + idx;
    
    return *this;
}

size_t MyString::find(const MyString& str, size_t pos) const {
    if (pos >= stringSize || stringSize < str.size()) {
        return -1;
    }
    size_t counter = 0;
    for (size_t i = pos; i < stringSize; i++) {
        bool found = true;
        for (size_t j = 0; j < stringSize; j++) {
            if (character[i + j] != str.at(j)) {
                found = false;
                break;
            } 
            counter += 1;
            if (counter == str.size()) {
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}