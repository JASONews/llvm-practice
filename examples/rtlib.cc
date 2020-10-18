#include <iostream>

using namespace std;

extern "C" void logdiv(int32_t lineno)
{
    cout << "Float div called at line " << lineno << endl;
}