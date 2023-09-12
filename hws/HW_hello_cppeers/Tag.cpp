/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) : tagName(tagName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks

  if (tagName.size() < 2) {
    throw std::invalid_argument("tag name too short");
  }

  if (tagName[0] != '#') {
    throw std::invalid_argument("tag name doesn't start with #");
  }

  if (!isalpha(tagName[1])) {
    throw std::invalid_argument("tag name starts with non-letter");
  }

  for (int i = 1; i < tagName.size(); i++) {
    if (isupper(tagName[i])) {
      throw std::invalid_argument("tag name must container only lowercase letters");
    }
  }

  if (tagName[tagName.size() - 1] == '.' || tagName[tagName.size() - 1] == ',' || tagName[tagName.size() - 1] == '!' || tagName[tagName.size() - 1] == '?') {
    throw std::invalid_argument("punctuation");
  }
}

string Tag::getTagName() {
  // TODO(student): implement getter

  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter

  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts

  if (post == nullptr) {
    throw std::invalid_argument("post is nullptr");
  }
  
  tagPosts.push_back(post);
}
