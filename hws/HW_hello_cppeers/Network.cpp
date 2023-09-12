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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;
using namespace std;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file

  std::ifstream s(fileName);

  if (!s.is_open()) {
    throw std::invalid_argument("file can't be opened");
  }

  while (!s.eof()) {

  string input, username, posttext;
  int postid;

    s >> input;
    if (input.empty()) {
      break;
    } else if (input == "User") {
      try {
        s >> username;
        addUser(username);
      }
      catch (std::exception& e) {
        throw std::runtime_error("user failed");
      }
    } else if (input == "Post") {
      try {
        s >> postid >> username;
        getline(s, posttext);
        if (posttext[0] == ' ') {
          posttext = posttext.substr(1, posttext.size());
        }
        addPost(postid, username, posttext);
      }
      catch (std::exception& e) {
        std::cout << postid << " " << username << " " << posttext << std::endl;
        throw std::runtime_error("bad format");
      }
    } else {
      throw std::runtime_error("bad");
    }
  }
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network

  for (int i = 0; i < userName.size(); i++) {
    userName[i] = tolower(userName[i]);
  }

  for (int i = 0; i < users.size(); i++) {
    if (userName == users[i]->getUserName()) {
      throw std::invalid_argument("user already exists");
    }
  }

  users.push_back(new User(userName));
  std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network

  for (unsigned int i = 0; i < posts.size(); i++) {
    if (posts[i]->getPostId() == postId) {
      std::cout << "1" << std::endl;
      throw std::invalid_argument("post id already exists");
    }
  }
  
  Post* newpost = new Post(postId, userName, postText);
  bool found = false;
  for (unsigned int i = 0; i < users.size(); i++) {
    if (users[i]->getUserName() == userName) {
      posts.push_back(newpost);
      users[i]->addUserPost(newpost);
      found = true;
    }
  }
  if (!found) {
    std::cout << "2" << std::endl;
    throw std::invalid_argument("user does not exist");
  }

  vector<string> taglist = newpost->findTags();
  bool exist = false;

  for (unsigned int i = 0; i < taglist.size(); i++) {
    exist = false;
    for (unsigned int j = 0; j < tags.size(); j++) {
      if (tags[j]->getTagName() == taglist[i]) {
        tags[j]->addTagPost(newpost);
        exist = true;
      }
    }
    if (!exist) {
      try {
        Tag* newtag = new Tag(taglist[i]);
        tags.push_back(newtag);
        newtag->addTagPost(newpost);
      } catch (std::invalid_argument& excpt) {}
    }
  }

  std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user

  if (userName.empty()) {
    throw std::invalid_argument("User name cannot be empty");
  }

  for (int i = 0; i < users.size(); i++) {
    if (userName == users[i]->getUserName()) {
      return users[i]->getUserPosts();
    }
  }

  throw std::invalid_argument("user not found");
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag

  if (tagName.empty()) {
    throw std::invalid_argument("tag name cannot be empty");
  }

  for (int i = 0; i < tags.size(); i++) {
    if (tagName == tags[i]->getTagName()) {
      return tags[i]->getTagPosts();
    }
  }
  
  throw std::invalid_argument("tag does not exist");
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts

  vector<string> popular;

  if (tags.size() == 0) {
    return popular;
  }

  int max = 0;
  for (int i = 0; i < tags.size(); i++) {
    if (tags[i]->getTagPosts().size() > max) {
      max = tags[i]->getTagPosts().size();
    }
  }

  for (int i = 0; i < tags.size(); i++) {
    if (tags[i]->getTagPosts().size() == max) {
      popular.push_back(tags[i]->getTagName());
    }
  }

  return popular;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}