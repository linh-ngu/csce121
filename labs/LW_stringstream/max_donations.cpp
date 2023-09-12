#include <iostream>
#include <sstream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::ifstream;
using std::istringstream;

int main() {
  string filename;
  cout << "Enter donation filename: ";
  cin >> filename;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Failed to open file " << filename << "." << endl;
    return 1;
  }
  
  double maxTotalDonation = 0;
  int maxTotalCollector = 0;
  
  // read data

  while (!ifs.eof())  {
    string temp;
    getline(ifs, temp);

    //cout << temp << endl;

    istringstream sin(temp);

    int uin = 0;
    double val = 0;
    double sum = 0;
    int count = 0;

    sin >> uin;
    sin >> val;
    while (!sin.fail()){
      sum += val;
      count++;
      //cout << "value: " << val << " sum: " << sum << " count: " << count << endl;
      sin >> val;
    }
    
    if (maxTotalDonation < sum && count > 1) {
      maxTotalCollector = uin;
      maxTotalDonation = sum;
    }
  }

  if (maxTotalDonation == 0){
    cout << "No donations.";
  }
  else {
  
    cout << "Highest donation total: " << maxTotalDonation << endl;
    cout << "-- collected by id: " << maxTotalCollector << endl;
  }
}