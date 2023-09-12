#include <iostream>
#include <stdexcept>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    if (isalpha(digit) || (int(digit) - 48) / 10 != 0 || (int(digit) - 48) < 0) {
        throw std::invalid_argument("Invalid");
    }
    return int(digit) - 48;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    if (decimal >= 10) {
        throw std::invalid_argument("Invalid");
    }
    return static_cast<char>(decimal + 48);
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    unsigned int temp = 0;
    if (num.find("-") != string::npos) {
        for (unsigned int i = 1; i < num.length(); i++) {
            if (num[i] != '0') {
                break;
            }
            temp += 1;
        }
        num = num.erase(1, temp);
    }
    else {
        for (unsigned int i = 0; i < num.length(); i++) {
            if (num[i] != '0') {
                break;
            }
            temp += 1;
        }
        if (temp == num.length()) {
            return "0";
        }
        num.erase(0, temp);
    }
    if (num[0] == '-' && num.length() == 1) {
        return "0";
    }
    return num;
}

string add(string lhs, string rhs) {
    // TODO(student): implement

    if(rhs.at(0) == '0' && rhs.size() == 1) {
        return lhs;
    }
    if(lhs.at(0) == '0' && lhs.size() == 1) {
        return rhs;
    }

    string ans = "";
    int carry = 0;

    //positive positive
    if (lhs.find("-") == string::npos && rhs.find("-") == string::npos) {

        if (lhs.size() > rhs.size()) {
            lhs.insert(0, "0");
            for (unsigned int i = 0; i < lhs.size(); i++) {
                while (lhs.size() != rhs.size()) {
                    rhs.insert(0, "0");
                }
            }
        }
        else if(lhs.size() < rhs.size()) {                                               
            rhs.insert(0, "0");
            for (unsigned int i = 0; i < rhs.size(); i++) {
                while (lhs.size() != rhs.size()) {
                    lhs.insert(0, "0");
                }
            }
        }
        else {
            lhs.insert(0, "0");
            rhs.insert(0, "0");
        }

        for (int i = lhs.size() - 1; i >= 0; i--) {
            int ldigit = digit_to_decimal(lhs[i]);
            int rdigit = digit_to_decimal(rhs[i]);
            int tempans = (ldigit + rdigit) + carry;
            if (tempans > 9) {
                carry = tempans / 10;
            }
            else {
                carry = 0;
            }
            ans.insert(0, std::to_string(tempans % 10));
        }
        return trim_leading_zeros(ans);
    }

    //negative negative
    else if (lhs.find("-") != string::npos && rhs.find("-") != string::npos) {

        if (lhs.size() > rhs.size()) {
            lhs.insert(1, "0");
            for (unsigned int i = 0; i < lhs.size(); i++) {
                while (lhs.size() != rhs.size()) {
                    rhs.insert(1, "0");
                }
            }
        }
        else if(lhs.size() < rhs.size()) {                                               
            rhs.insert(1, "0");
            for (unsigned int i = 0; i < rhs.size(); i++) {
                while (lhs.size() != rhs.size()) {
                    lhs.insert(1, "0");
                }
            }
        }
        else {
            lhs.insert(1, "0");
            rhs.insert(1, "0");
        }

        for (int i = lhs.size() - 1; i > 0; i--) {
            int ldigit = digit_to_decimal(lhs[i]);
            int rdigit = digit_to_decimal(rhs[i]);
            int tempans = (ldigit + rdigit) + carry;
            if (tempans > 9) {
                carry = tempans / 10;
            }
            else {
                carry = 0;
            }
            ans.insert(0, std::to_string(tempans % 10));
        }
        return trim_leading_zeros(ans.insert(0, "-"));
    }

    return 0;
}

string multiply(string lhs, string rhs) {
    string ans = "";
    int carry = 0;
    int counter = 0;
    bool neg = false;

    if (lhs[0] == '-' && rhs[0] == '-') {
        lhs.at(0) = '0';
        rhs.at(0) = '0';
    }
    else if (lhs[0] == '-') {
        neg = true;
        lhs.at(0) = '0';
    }
    else if (rhs[0] == '-') {
        neg = true;
        rhs.at(0) = '0';
    }

    lhs.insert(0, "0");
    rhs.insert(0, "0");

    if (lhs.length() <= rhs.length()) {
        for (int i = lhs.length() - 1; i >= 0; i--) {
            if (counter != 0) {
                for (int k = 0; k < counter; k++) {
                    ans.insert(0, "0");
                }
            }
            int idigit = digit_to_decimal(lhs[i]);
            for (int j = rhs.length() - 1; j >= 0; j--) {
                int jdigit = digit_to_decimal(rhs[j]);
                int tempans = (idigit * jdigit) + carry;
                if (tempans > 9) {
                    carry = tempans / 10;
                }
                else {
                    carry = 0;
                }
                ans.insert(0, std::to_string(tempans % 10));
            }
            ans.insert(0, " + ");
            counter += 1;
        }
        ans = ans.substr(3, ans.length());

        while (ans.find("+") != string::npos) {
            lhs = ans.substr(0, ans.find("+") - 1);
            ans = ans.substr(ans.find("+") + 2, ans.length());
            rhs = ans.substr(0, ans.find("+") - 1);
            ans.insert(ans.length(), " + " + add(lhs, rhs));
            ans = ans.substr(ans.find("+") + 2, ans.length());
            if (ans == " + " + add(lhs, rhs)) {
                break;
            }
        }
        if (neg) {
            return trim_leading_zeros(ans).insert(0, "-");
        }
        return trim_leading_zeros(ans);
    }
    
    if (lhs.length() > rhs.length()) {
        for (int i = rhs.length() - 1; i >= 0; i--) {
            if (counter != 0) {
                for (int k = 0; k < counter; k++) {
                    ans.insert(0, "0");
                }
            }
            int idigit = digit_to_decimal(rhs[i]);
            for (int j = lhs.length() - 1; j >= 0; j--) {
                int jdigit = digit_to_decimal(lhs[j]);
                int tempans = (idigit * jdigit) + carry;
                if (tempans > 9) {
                    carry = tempans / 10;
                }
                else {
                    carry = 0;
                }
                ans.insert(0, std::to_string(tempans % 10));
            }
            ans.insert(0, " + ");
            counter += 1;
        }
        ans = ans.substr(3, ans.length());

        while (ans.find("+") != string::npos) {
            lhs = ans.substr(0, ans.find("+") - 1);
            ans = ans.substr(ans.find("+") + 2, ans.length());
            rhs = ans.substr(0, ans.find("+") - 1);
            ans.insert(ans.length(), " + " + add(lhs, rhs));
            ans = ans.substr(ans.find("+") + 2, ans.length());
            if (ans == " + " + add(lhs, rhs)) {
                break;
            }
        }
        if (neg) {
            return trim_leading_zeros(ans).insert(0, "-");
        }
        return trim_leading_zeros(ans);
    }
    return 0;
}