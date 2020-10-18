#include <iostream>

using namespace std;

extern "C" void logop(int32_t val)
{
    cout << val << endl;
}