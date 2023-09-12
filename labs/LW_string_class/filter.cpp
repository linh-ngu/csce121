#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

void replaceWords(string& sentence, string filler, string replaceWord) {
    size_t position = sentence.find(filler);
    while (position != string::npos) {
        sentence.replace(position, filler.size(), replaceWord);
        position = sentence.find(filler, position + replaceWord.size());
    }
}

int main() {
    string sentence;
    string filler;
    cout << "Please enter the sentence: ";
    getline(cin, sentence);
    cout << "Please enter the filter word: ";
    cin >> filler;

    string replaceWord = "";
    for (unsigned int i = 0; i < filler.length(); i++) {
        replaceWord += "#";
    }

    replaceWords(sentence, filler, replaceWord);
    cout << "Filtered sentence: " << sentence << endl;
    return 0;
}
