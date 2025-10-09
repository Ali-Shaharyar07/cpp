#include <iostream>

using namespace std;

int main()
{
    //cout << "Hello, World!" << endl;
    cout << "int: " << sizeof(int)*8 << endl;
    cout << "char: " << sizeof(char)*8 << endl;
    cout << "float: " << sizeof(float)*8 << endl;
    cout << "double: " << sizeof(double)*8 << endl;
    cout << "string: " << sizeof(string)*8 << endl;
    cout << "long: " << sizeof(long)*8 << endl;
    cout << "bool: " << sizeof(bool)*8 << endl;
    return 0;
}