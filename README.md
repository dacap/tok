# tok

A minimalist C++ library to iterate through string tokens:

```c++
#include <iostream>
#include <string>
#include "tok.h"

int main() {
  std::string str = "this,is,a,string";
  for (auto& tok : tok::split_tokens(str, ',')) {
    std::cout << "\"" << tok << "\"\n";
  }
}
```
