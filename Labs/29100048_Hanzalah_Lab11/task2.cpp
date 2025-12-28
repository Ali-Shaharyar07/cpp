// g++ -std=c++17 test.cpp -o tests && ./tests. ->test case command

#include <iostream>
using namespace std;

/*
 * Reads an n x n matrix from the user using pointer arithmetic.
 * base points to the first element (matrix[0][0]).
 */
void readMatrix(int *base, int n) {
    // TODO
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
          cin >> *(base+i*n+j);
        }   
    }
}

/*
 * Prints an n x n matrix using pointer arithmetic.
 */
void printMatrix(int *base, int n) {
    // TODO
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
          cout << *(base+i*n+j) << " ";  
        }   
        cout << endl;
    }
}

/*
 * Swaps the left  and right  diagonal elements.
 */
void swapDiagonals(int *base, int n) {
    int j=0;
    for (int i=0; i<n; i++)
    {
            int temp = *(base+i*n+j);
            *(base+i*n+j) = *(base+i*n+n-1-j);
            *(base+i*n+n-1-j) = temp;
            j++;
    }
}

int main() {
    int matrix[5][5];
    int n = 1;
    cout << "Enter size of matrix (negative to exit): ";
    cin >> n;
    while (n > 0)
    {
        if (n<2 || n>5)
        {
            cout << "Invalid size. Please enter a value between 2 and 5: ";
            cin >> n;
        }

        cout << "Enter " << n*n << " integers:" << endl;
        readMatrix(*matrix, n);

        cout << "Original Matrix:" << endl;
        printMatrix(*matrix, n);

        cout << "Matrix after swapping diagonals:" << endl;
        swapDiagonals(*matrix, n);
        printMatrix(*matrix, n);
        cout << endl;

        cout << "Enter size of matrix (negative to exit): ";
        cin >> n;
    }
    cout << "Exiting program." << endl;


    return 0;
}


