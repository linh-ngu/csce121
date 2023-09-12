#include <iostream>

bool f(bool x, bool y, bool z) {
  // write your code to compute f(x,y,z) here
  bool value; // TODO: change this line
  if (x == 0 && y == 0 && z == 0) {
    value = false;
  }
  else if (x == 1 && y == 0 && z == 1) {
    value = false;
  }
  else if (x == 1 && y == 1 && z == 0) {
    value = false;
  }
  else {
    value = true;
  }
  return value;
}