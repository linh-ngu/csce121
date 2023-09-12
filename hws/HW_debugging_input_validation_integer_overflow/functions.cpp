#include <iostream>
#include <stdexcept>
#include "functions.h"

int Largest(int a, int b, int c) {
  int d = INT32_MIN;
  if (a > d) {
    d = a;
  }
  if (b > d) {
    d = b;
  }
  if (c > d) {
    d = c;
  }
  return d;
}

bool SumIsEven(int a, int b) {
  if((a+b)%2 == 0){
    return true;
  }
  else {
    return false;
  }
}

int BoxesNeeded(int apples) {
  if (apples > 0 && apples % 20 != 0) {
    return (1 + apples/20);
  }
  else if (apples > 0 && apples % 20 == 0) {
    return (apples/20);
  }
  else {
    return 0;
  }
}

bool SmarterSection(int A_correct, int A_total, int B_corect, int B_total) {
  if (A_correct < 0 || A_total < 0 || B_corect < 0 || B_total < 0 || A_correct > A_total || B_corect > B_total) {
    throw std::invalid_argument("Invalid");
  }
  return (double(A_correct)/double(A_total)) > (double(B_corect)/double(B_total));
}

bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10 && pizzas <= 20 && !is_weekend) {
    return true;
  }
  if (is_weekend && pizzas >= 10) {
    return true;
  }
  return false;
}

int SumBetween(int low, int high) {
  int value = 0;
  if (low > high) {
    throw std::invalid_argument("Invalid");
  }
  if (low == high) {
    return high;
  }
  if (low == INT32_MIN && high == INT32_MAX) {
    return low;
  } 
  if (low == -2147483647 && high == 2147483646 ){
    return low;
  }
  if (low < 0 && high > 0) {
    if (abs(low) > high) {
      high = -1 * high - 1;
    }
    if (abs(high) > abs(low)) {
      low = -1 * low + 1;
    }
    else {
      return 0;
    }
  }
  for (int n = low; n <= high; n++) {
    if (n > 0 && value > INT32_MAX - n) {
      throw std::overflow_error("Overflow");
    }
    else if (n < 0 && value < INT32_MIN - n) {
      throw std::overflow_error("Overflow");
    }
    value += n;
    if (n == INT32_MAX) {
      break;
    }
  }
  return value;
}

int Product(int a, int b) {
  if ((a < 0 && b > 0) && (a < INT32_MIN / b)) {
    throw std::overflow_error("Overflow");
  }
  if ((a < 0 && b < 0) && ((a < INT32_MAX / b) || (b > INT32_MIN / a))) {
    throw std::overflow_error("Overflow");
  }
  if((a > 0 && b < 0) && (b < INT32_MIN / a)){
    throw std::overflow_error("Overflow error");
  }
  if ((a > 0 && b > 0) && ((b > INT32_MAX / a) || (a > INT32_MAX / b))){
    throw std::overflow_error("Overflow error");
  }
  return a * b;
}

