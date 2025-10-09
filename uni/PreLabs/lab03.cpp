#include <iostream>
#include <limits>

using namespace std;

/*
sizeof(type) - returns the size of a data type in bytes

#include <limits> - includes the limits library which provides information about the properties of fundamental data types
numeric_limits<type>::min() - returns the minimum value that can be represented by a data type
numeric_limits<type>::max() - returns the maximum value that can be represented by a data

Datatype conversion


*/

int main()
{
    cout << "Size of char: " << sizeof(char) << " byte(s)" << endl;
    cout << "Size of int: " << sizeof(int) << " byte(s)" << endl;
    cout << "Size of float: " << sizeof(float) << " byte(s)" << endl;
    cout << "Size of double: " << sizeof(double) << " byte(s)" << endl;

    cout << "Minimum value of int: " << numeric_limits<int>::min() << endl;
    cout << "Maximum value of int: " << numeric_limits<int>::max() << endl;

    cout << "Minimum value of float: " << numeric_limits<float>::min() << endl;
    cout << "Maximum value of float: " << numeric_limits<float>::max() << endl;

    cout << "Minimum value of double: " << numeric_limits<double>::min() << endl;
    cout << "Maximum value of double: " << numeric_limits<double>::max() << endl;

    int value = 65;
    char character = static_cast<char>(value); // Explicit conversion from int to char
    cout << "The character representation of ASCII value " << value << " is: " << character << endl;
    float decimalValue = 65.99f;
    int intValue = static_cast<int>(decimalValue); // Explicit conversion from float to int
    cout << "The integer representation of float value " << decimalValue << " is: " << intValue << endl;

    return 0;
}