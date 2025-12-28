// g++ -std=c++17 test.cpp -o tests && ./tests ->test case command
//#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

void swap (int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
    //cout << *a << ":" << *b << endl;
}


int main() {
    int *p = new int[3]{1, 2, 3};
    int *q = p;
    cout << *q;
    //cout << a << " " << b << endl;
    //cout << *p << " " << *q << endl;
    

    return 0;
}
