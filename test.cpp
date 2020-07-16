// tok.h
// Copyright (c) 2020 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include <iostream>
#include <string>
#include "tok.h"

void test_split_tokens(const std::string& str) {
  std::cout << "-- split_tokens(\"" << str << "\") --\n";
  for (auto& tok : tok::split_tokens(str, ',')) {
    std::cout << "\"" << tok << "\"\n";
  }
}

int main() {
  test_split_tokens("a,b,");
  test_split_tokens("this,is,a,string");
  test_split_tokens("");
  test_split_tokens(",,,");
  test_split_tokens(",hi there!,");
}
