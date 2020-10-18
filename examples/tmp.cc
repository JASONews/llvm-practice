#include <iostream>

using namespace std;

int main(int argc, char **argv) 
{
	int x = 20;
	int y = x + 5;
	float c = x / 1.2 + y;
	cout << c / 0.5 << endl;
	return 0;
}