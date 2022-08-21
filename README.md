# C++ Python Style Library

A C++ library containing a collection of functions and containers similar to how the Python language is structured.

```cpp
#include <psl_list.h>

#include <iostream>

int main() {
    psl::list<int> l;

    l.push_back(1);

    // What? Adding items with +=?
    l += 2;
    l += 3;

    // What? Negative indexing? 
    std::cout << l[0] << ' ' << l[-1] << std::endl;

    return 0;
}
```

```Output
1 3
```

## License

Copyright (c) Brandon Pacewic

SPDX-License-Identifier: MIT
