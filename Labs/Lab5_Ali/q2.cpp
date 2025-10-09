#include <iostream>
#include <string>

using namespace std;

int main() {
    int num, hashCount = 0,strCount = 0;
    cin >> num;
    string line;
    for (int i = 0; i<num; i++){
        cin >> line;
        while (line.length() != num){
            cout << "Please enter a string of length " << num << ": ";
            cin >> line;
        }
        for (int j = 0; j < line.length(); j++) {
            if (line[j] == '#') {
                hashCount++;
            }
        }
        if (hashCount >= 5) {
            hashCount = 0;
            strCount++;
        }
    }
    cout << strCount << endl;
    return 0;
}