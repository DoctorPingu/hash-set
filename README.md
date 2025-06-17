# C++ Hash Set Implementation

This project is a custom, from-scratch implementation of a Hash Set data structure in C++. It is designed to store unique integer keys with efficient average-case time complexity for insertions, deletions, and lookups, mimicking the functionality of `std::unordered_set`.

The implementation uses the separate chaining method to handle hash collisions. The hash table automatically resizes and rehashes its elements when the load factor exceeds a specified threshold, ensuring that performance remains optimal as the number of elements grows.

## Core Features

-   **O(1) Average Time Complexity**: Achieves constant time performance on average for `insert`, `erase`, and `contains` operations.
-   **Dynamic Rehashing**: The underlying table automatically grows and rehashes elements to maintain a low load factor, preventing performance degradation.
-   **Customisable Load Factor**: The maximum load factor that triggers a rehash can be inspected and modified at runtime.
-   **Full Iterator Support**: Implements C++ iterators, allowing for standard operations like range-based `for` loops (`for (int val : mySet)`).
-   **Standard Library Compliance**: Provides an interface similar to the C++ standard library containers, including `size()`, `empty()`, `begin()`, `end()`, `find()`, and a copy-and-swap implementation for safe assignment.

## Implementation Details

-   **Buckets**: The hash table is implemented as a `std::vector` of iterators (`std::vector<std::list<int>::iterator>`). Each index in the vector acts as a bucket, pointing to the head of a chain in the shared linked list.
-   **Separate Chaining with a Single List**: All elements are stored in a single `std::list<int>`. This approach provides iterator stability, as inserting or erasing elements in one bucket's chain does not invalidate iterators pointing to elements in other chains.
-   **Hashing Function**: A simple and fast modulo hash function is used. The table sizes are chosen from a pre-defined list of prime numbers to help distribute keys more uniformly and reduce collisions.

## How to Build and Run Tests

The project includes a comprehensive test suite using the Google Test framework to verify correctness and performance.

### Prerequisites

-   A C++ compiler that supports the C++20 standard (e.g., GCC 10+, Clang 12+).
-   [Google Test](https://github.com/google/googletest) (gtest) installed and accessible by the compiler.

### Compiling and Running

1.  Navigate to the project's root directory in your terminal.
2.  Compile the source files using the following command. You may need to adjust the include (`-I`) and library (`-L`) paths to match your Google Test installation.

    ```bash
    g++ -std=c++20 main.cpp hash.cpp -o run_tests -I/path/to/googletest/include -L/path/to/googletest/lib -lgtest -lgtest_main -pthread
    ```

3.  Execute the compiled test runner:

    ```bash
    ./run_tests
    ```

    All tests should pass, confirming that the implementation is working correctly.

## Example Usage

Here is a simple example demonstrating how to use the `HashSet` class.

```cpp
#include <iostream>
#include "hash.hpp"

int main() {
    // 1. Create a new hash set
    HashSet mySet;

    // 2. Insert some elements
    mySet.insert(42);
    mySet.insert(100);
    mySet.insert(-5);
    mySet.insert(42); // Duplicates are automatically ignored

    // 3. Check if an element exists
    if (mySet.contains(100)) {
        std::cout << "Set contains 100." << std::endl;
    }

    // 4. Erase an element
    mySet.erase(100);
    std::cout << "Erased 100 from the set." << std::endl;


    // 5. Print the number of elements
    std::cout << "Current size: " << mySet.size() << std::endl;

    // 6. Iterate through the set using a range-based for loop
    std::cout << "Elements in set: ";
    for (int value : mySet) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### Expected Output

```
Set contains 100.
Erased 100 from the set.
Current size: 2
Elements in set: -5 42
```

*(Note: The order of elements in the output may vary due to the nature of hash sets.)*
