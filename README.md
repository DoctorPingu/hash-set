# C++ Hash Set Implementation

This repository provides a concise, academic-style implementation of a custom hash set data structure in C++, supporting efficient insertions, deletions, and lookups. The set uses separate chaining with dynamic resizing (rehashing) to ensure consistent average-case performance.

## Core Features

- **Efficient Operations**: O(1) average time complexity for `insert`, `erase`, and `contains`.
- **Automatic Rehashing**: Dynamically resizes when exceeding a specified load factor to maintain performance.
- **Iterator Support**: Fully supports C++ standard iterators for convenient traversal.
- **Standard-Library Compliance**: Familiar interface including methods like `size()`, `empty()`, `begin()`, and `end()`.

## Implementation Details/Technology Used

- **Separate Chaining**: Implemented using a single `std::list<int>` for storing all elements, with bucket indexing managed via `std::vector<std::list<int>::iterator>`.
- **Hashing Strategy**: Utilises a modulo-based hash function. Bucket sizes are prime numbers to enhance distribution uniformity.
- **Built With**:
  - C++20 Standard
  - Standard Template Library (STL) containers
  - Google Test framework for unit testing

## Compilation/Execution Instructions

### Prerequisites

- C++ compiler supporting C++20 (GCC 10+, Clang 12+)
- [Google Test](https://github.com/google/googletest) framework

### Compile and Run Tests

Compile the project by adjusting paths to your Google Test installation:

```bash
g++ -std=c++20 main.cpp hash.cpp -o run_tests -I/path/to/googletest/include -L/path/to/googletest/lib -lgtest -lgtest_main -pthread
```

Execute tests:

```bash
./run_tests
```

All tests should pass, validating the correctness of the implementation.

## Example/Output Description

Demonstrating basic usage of the `HashSet` class:

```cpp
#include <iostream>
#include "hash.hpp"

int main() {
    HashSet mySet;

    mySet.insert(42);
    mySet.insert(100);
    mySet.insert(-5);
    mySet.insert(42); // duplicate ignored

    if (mySet.contains(100)) {
        std::cout << "Set contains 100." << std::endl;
    }

    mySet.erase(100);
    std::cout << "Erased 100 from the set." << std::endl;

    std::cout << "Current size: " << mySet.size() << std::endl;

    std::cout << "Elements in set: ";
    for (int value : mySet) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Expected Output

```
Set contains 100.
Erased 100 from the set.
Current size: 2
Elements in set: -5 42
```

*Note: Output element order may vary due to hashing.*

## Assumptions/Limitations

- Supports integer keys only.
- Duplicates are ignored upon insertion.
- Performance may vary with different load factors and key distributions.
