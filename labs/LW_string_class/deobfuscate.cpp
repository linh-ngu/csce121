#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

void deobfuscate(string& sentence, string& details) {
    int index = 0;
    for (unsigned int i = 0; i < details.length(); i++) {
        index += (int(details[i]) - 48);
        sentence.insert(index, " ");
        index += 1;
    }
}

int main() {
    string sentence;
    string details;
    cout << "Please enter obfuscated sentence: ";
    cin >> sentence;
    cout << "Please enter deobfuscation details: ";
    cin >> details;

    deobfuscate(sentence, details);
    cout << "Deobfuscated sentence: " << sentence << endl;
    return 0;
}