#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    string input;
    string ans;
    // TODO(student): implement the UI
    while (true){
        cout << ">> ";
        getline(cin, input);
        cout << endl;
        if (input == "quit" || input == "q"){
            cout << "farvel!";
            break;
        }
        else {
            string lhs;
            string rhs;
            if(input.find("+") != string::npos) {
                lhs = input.substr(0, input.find("+") - 1);
                rhs = input.substr(input.find("+") + 2, input.length());
                ans = add(lhs, rhs);
            }
            else if (input.find("*") != string::npos) {
                lhs = input.substr(0, input.find("*") - 1);
                rhs = input.substr(input.find("*") + 2, input.length());
                ans = multiply(lhs, rhs);
            }
            else {
                throw std::invalid_argument("Argument is not valid");
            }
            cout << "ans =" << endl << endl << "    " << ans << endl << endl;
        }
    }
    return 0;
}