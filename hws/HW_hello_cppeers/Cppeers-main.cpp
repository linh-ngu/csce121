/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Network.h"

using std::cout, std::cin, std::endl;
using std::string, std::vector;

void printMenu() {
  cout << "Welcome to CPPeers" << endl;
  cout << "The options are: " << endl;
  cout << "1. load data file and add information" << endl;
  cout << "2. show posts by user" << endl;
  cout << "3. show posts with hashtag" << endl;
  cout << "4. show most popular hashtag" << endl;
  cout << "9. quit" << endl;
  cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
  string fileName = "";
  cout << "Enter filename: ";
  cin >> fileName;
  cppeers.loadFromFile(fileName);
}

void processPostsByUser(Network& cppeers) {
  // TODO(student): implement

  string username = "";
  cout << "Enter username: ";
  cin >> username;
  vector<Post * > userposts = cppeers.getPostsByUser(username);
  for (int i = 0; i < userposts.size(); i++) {
    cout << userposts[i]->getPostText() << endl;
  }
}

void processPostsWithHashtags(Network& cppeers) {
  // TODO(student): implement

  string tagname = "";
  cout << "Enter tagname: ";
  cin >> tagname;
  vector<Post * > mostposts = cppeers.getPostsWithTag(tagname);
  for (int i = 0; i < mostposts.size(); i++) {
    cout << mostposts[i]->getPostText() << endl;
  }
}

void processMostPopularHashtag(Network& cppeers) {
  // TODO(student): implement

  vector<string> mostpopular = cppeers.getMostPopularHashtag();
  for(int i = 0; i < mostpopular.size() ; i++) {
    cout << mostpopular[i] << endl;
  }
}

int main() {

  try {
    Network cppeers;

    int choice = 0;

    // present menu
    do {
      printMenu();
      cin >> choice;
      switch(choice) {
        case 1: {
          processLoad(cppeers);
          break;
        }
        case 2: {
          processPostsByUser(cppeers);
          break;
        }
        case 3: {
          processPostsWithHashtags(cppeers);
          break;
        }
        case 4: {
          processMostPopularHashtag(cppeers);
          break;
        }
      }
    } while (choice != 9);
  } catch (std::exception& exc) {
    std::cout << exc.what() << endl;
  }

  return 0;
}
