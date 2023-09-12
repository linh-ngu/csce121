#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)
  int i = 0;
  while (true) {
    if (str[i] != '\0') {
      i++;
    }
    else {
      return (i);
    }
  }
}

unsigned int find(char str[], char character) {
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
  for (unsigned int i = 0; i < length(str); i++) {
    if (str[i] == character) {
      return i;
    }
  }
  return length(str);
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not
  if (length(str1) != length(str2)) {
    return false;
  }
  for (unsigned int i = 0; i < length(str1); i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}