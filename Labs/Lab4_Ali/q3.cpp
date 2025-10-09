#include <iostream>
#include <string>

using namespace std;

int main() {
   
    string line;
    cin >> line;
    char curr;
    bool repeated = false;
    for (int i=0; i < line.length(); i++) {
       curr = line[i];
       repeated = false;
       for (int j=0; j < line.length(); j++) {
           if (line[j] == curr && j != i) {
               repeated = true;
               break;
           }
       }
       if (!repeated) {
           cout << curr;
       }
    }
    

    return 0;
}