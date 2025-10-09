#include <iostream>
#include <string>

using namespace std;

int main() {
    string line = "";
    int rows, c = 1, check;
    bool isPrime = false;
    cout << "Enter number of rows: ";
    cin >> rows;

    for (int i = 1; i<= rows; i++) {
        check = 3;
        for (int j = 1; j <= i; j++){
            while (!isPrime) {
                isPrime = true;
                for (int k = 2; k <= check/2; k++) {
    
                    if (check % k == 0) {
                        
                        isPrime = false;
                        check++;
                        break;
                    }
                }
            }
            cout << check << " ";
            check++;
            isPrime = false;
        }
        cout << endl;
    }


    return 0;
}