#include <iostream>
#include <iomanip>

using namespace std;

/*
Manipluators: Help control how data is displayed
Examples:
    endl - inserts a newline character and flushes the output buffer (basically next line)
    setw(n) - sets the width of the next input/output field to n characters (if n > length of data, adds spaces to the left. If n < length of data, no effect)
    width(n) - sets the width of the next input/output field to n characters (if n > length of data, adds spaces to the left. If n < length of data, no effect)
    setfill(c) - sets the fill character to c (default is space) STAYS UNTIL CHANGED
    setprecision(n) - sets the decimal precision to n digits (for floating point numbers)
    default (no fixed) - setprecision(n) sets the total number of significant digits
    fixed - setprecision(n) sets the number of digits to the right of the decimal point
    scientific - sets the float to scientific notation (eg. 1.23e+03 for 1230)
    boolalpha - displays boolean values as true or false instead of 1 or 0
    nonboolalpha - displays boolean values as 1 or 0 instead of true or false
    noskipws - do not skip whitespace characters when reading input
    skipws - skip whitespace characters when reading input (default behavior)
*/


int main() {
    /*
    cout << "Hello" << endl << "World" << endl; // endl manipulator
    cout << setw(5) << 123 << endl; // setw manipulator
    cout << setw(5) << 12345 << endl; // setw manipulator

    int x=5;
    float y=5.56789f;
    double z=1234567.89;
    cout.width(10);
    cout << x << endl; 
    cout << setfill('*'); // setfill manipulator
    cout << setw(10) << x << endl;
    cout << setfill(' '); // setfill manipulator

    cout << "Normal: " << y << " | Default precision(3): " << setprecision(3) << y 
    << " | Fixed precision(3): " << fixed << setprecision(3) << y << endl; // setprecision manipulator
    cout << "Default: " << z << endl;
    cout << "Scientific: " << scientific << z << endl; // scientific manipulator
    cout << "Scientific with precision 1 (with scientific setprecision works like fixed): " << scientific << setprecision(1) << z << endl; 
    cout << "Scientific with fixed precision 2: " << scientific << fixed << setprecision(2) << z << "  fixed forces num to go till decimal point" << endl; 

    cout << boolalpha;
    bool b1=true, b2=false;
    cout << "Boolalpha: " << b1 << " " << b2 << endl; // boolalpha manipulator
    cout << noboolalpha;
    cout << "Noboolalpha: " << b1 << " " << b2 << endl; // noboolalpha manipulator
    */

    double n = 12345.6789;
    cout << n << endl;
    cout << scientific << n << endl;
    cout << fixed << n << endl;
    return 0;
}