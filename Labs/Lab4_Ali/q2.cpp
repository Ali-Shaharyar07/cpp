#include <iostream>
#include <string>

using namespace std;

int main() {
   
    string line;
    cin >> line;
    char curr = line[0];
    int count = 1;

    for (int i=1; i < line.length(); i++) {
        if (line[i] == curr) {
            count++;
        } else {
            cout << curr << count;
            curr = line[i];
            count = 1;
        }
    }
    cout << curr << count;

    return 0;
}