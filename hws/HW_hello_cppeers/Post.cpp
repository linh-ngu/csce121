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
#include <sstream>
#include <string>
#include <stdexcept>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post

  vector<string> valid;
  std::stringstream s(postText);
  string word;

  while (!s.eof()) {

    s >> word;

    if (word.empty()) {
      break;
    }
    
    if (word[0] == '#') {
      string tag = "#";

      for (int i = 1; i < word.size(); i++) {

        if (isalpha(word[i])) {
          tag += tolower(word[i]);
        } else if (word[i] == '.' || word[i] == ',' || word[i] == '!' || word[i] == '?') {
          if(isalpha(word[i+1]) || isdigit(word[i+1])){
            tag += word[i];
          }
        } else {
          tag += word[i];
        }
      }

      valid.push_back(tag);
    }
  }

  return valid;
}
