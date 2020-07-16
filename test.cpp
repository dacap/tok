// tok.h
// Copyright (c) 2020 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include <iostream>
#include <string>
#include <vector>
#include "tok.h"

using strings = std::vector<std::string>;

template<typename T>
void EXPECT_EQ(T a, T b) {
  if (a != b) {
    std::cout << "Expected a == b:\n"
              << "  a = \"" << a << "\"\n"
              << "  b = \"" << b << "\"\n";
    std::abort();
  }
}

int main() {
  int i = 0;
  strings a_result = { "This", "is", "a", "phrase.", "Several", "whitespaces", "are", "ignored." };
  std::string a = "This is a phrase.   Several whitespaces are ignored.";
  for (auto& tok : tok::split_tokens(a, ' ')) {
    std::cout << "\"" << tok << "\"\n";
    EXPECT_EQ(tok, a_result[i++]);
  }

  i = 0;
  strings b_result = { "In comma", "separated", "", "values", "", "", "empties are included" };
  std::string b = "In comma,separated,,values,,,empties are included";
  for (auto& tok : tok::csv(b, ',')) {
    std::cout << "\"" << tok << "\"\n";
    EXPECT_EQ(tok, b_result[i++]);
  }
}
