#include <iostream>
#include <string>

using namespace std;

int main() {
    
    int rows, max;
    cin >> rows; // cin 6 -> 12x12 
    max = rows * 2; // max = 12
    string line = "";
    for (int i = 0; i < max; i++) {
        line += " ";
    }

    for (int i = 0; i < rows; i++) {
        line[i] = '*';
        line[max - i - 1] = '*';
        cout << line << endl;
    }
    for (int i = rows-1; i >= 0; i--) {
        cout << line << endl;
        line[i] = ' ';
        line[max - i - 1] = ' ';
        
    }

    return 0;
}