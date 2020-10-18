# LLVM HW

Basing on [llvm-pass-skeleton](https://github.com/sampsyo/llvm-pass-skeleton) code.

Build:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ ./build/example/main

This extension prints out the line number when a float point division operation
is encountered if the code is compiled with flag -g.

For instance, for the following code, it would print line number 9 and 10
because floating point division are used there.
```
(py3) ➜  llvm-practice git:(llvm-hw) ✗ cat examples/tmp.cc
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
        int x = 20;
        int y = x + 5;
        float c = x / 1.2 + y;
        cout << c / 0.5 << endl;
        return 0;
}%
```
Results:
```
(py3) ➜  llvm-practice git:(llvm-hw) ✗ ./build/examples/main
Float div called at line 9
Float div called at line 10
83.3333
```
