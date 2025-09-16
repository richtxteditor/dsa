# Initial Playground (C++ Practice Files)

This directory serves as a collection of small, independent C++ practice programs. Each file explores a different fundamental concept or language feature, acting as a personal sandbox for learning and experimentation.

## Contents

*   **`arrays.cpp`**
    *   **Description:** Demonstrates basic C-style arrays and the use of range-based for loops in C++. It also includes an example of a Variable-Length Array (VLA), which is a GCC extension.
    *   **Concepts:** Array declaration, iteration, basic input/output.

*   **`cppClassesPractice.cpp`**
    *   **Description:** Implements a `Rectangle` class, showcasing object-oriented programming principles. It includes constructors, a destructor, private member variables, and public methods for setting/getting dimensions and calculating area/perimeter.
    *   **Concepts:** Classes, objects, encapsulation, constructors, destructors, member functions, `this` pointer.

*   **`funcs.cpp`**
    *   **Description:** Explores a C-style approach to structuring data and functions. It defines a `struct Rectangle` and uses standalone functions to initialize, calculate area, and calculate perimeter, passing the struct by value or by pointer.
    *   **Concepts:** C-style structs, functions, pass-by-value, pass-by-pointer.

*   **`templateClass.cpp`**
    *   **Description:** Illustrates the power of C++ templates by defining a generic `Arithmetic` class. This class can perform basic arithmetic operations (addition, subtraction) on various data types, making the code reusable.
    *   **Concepts:** Function templates, class templates, generic programming.

## How to Compile and Run

Each `.cpp` file in this directory is a standalone program. To compile and run any of them, navigate to the `InitialPlayground` directory and use a C++ compiler like `g++`.

For example, to compile and run `cppClassesPractice.cpp`:

```bash
# Navigate to the directory
cd InitialPlayground

# Compile the desired file
g++ cppClassesPractice.cpp -o cpp_classes_demo

# Run the executable
./cpp_classes_demo
```

Replace `cppClassesPractice.cpp` and `cpp_classes_demo` with the respective filenames for other programs you wish to compile and run.
