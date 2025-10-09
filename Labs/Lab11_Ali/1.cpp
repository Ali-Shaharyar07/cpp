#include <iostream>
#include <string>

using namespace std;

int main() {
   
    int n;
    cin >> n;
    char arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    if (checkTicTacToeWinner(arr, n) == 'X') {
        cout << "X" << endl;
    } else if (checkTicTacToeWinner(arr, n) == 'O') {
        cout << "O" << endl;
    } else {
        cout << "Draw" << endl;
    }
    return 0;
}

char checkTicTacToeWinner(char board[n][n], int n){


}