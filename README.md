# tok

A minimalist C++ library to iterate through string tokens:

```c++
#include <iostream>
#include <string>
#include "tok.h"

int main() {
  // Prints:
  // "This"
  // "is"
  // "a"
  // "phrase."
  // "Several"
  // "whitespaces"
  // "are"
  // "ignored."
  std::string a = "This is a phrase.   Several whitespaces are ignored.";
  for (auto& tok : tok::split_tokens(a, ' ')) {
    std::cout << "\"" << tok << "\"\n";
  }

  // Prints:
  // "In comma"
  // "separated"
  // ""
  // "values"
  // ""
  // ""
  // "empties are included"
  std::string b = "In comma,separated,,values,,,empties are included";
  for (auto& tok : tok::csv(b)) {
    std::cout << "\"" << tok << "\"\n";
  }
}
```
