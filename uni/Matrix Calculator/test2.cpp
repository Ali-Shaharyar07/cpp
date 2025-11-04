


#include <iostream>

using namespace std;

int** subMatrix(int**mat, int rows, int cols, int rpos, int cpos)
{
    //Temp init
    int** tempMatrix = new int*[rows-1];
    for (int i = 0; i < rows-1; i++)
    {
        for (int j = 0; j < cols-1; j++)
        {
            tempMatrix[i] = new int[cols-1];
        }
    }

    int c, r;
    c = 0;
    r = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i!=rpos && j != cpos)
                {
                    tempMatrix[r][c] = mat[i][j];
                    c++;
                    if (c==cols-1)
                    {
                        r++;
                    }
                }
        }
        c = 0;
    }
    return tempMatrix;
}


int main()
{
    // User input for matrix dimensions
    int rows, cols;
    cout << "Enter number of rows for matrix 1: ";
    cin >> rows;
    cout << "Enter number of columns for matrix 1: ";
    cin >> cols;
    cout << '\n';

    int** mat = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> mat[i][j];
        }
    }
    cout << '\n';

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    int** tempMatrix = subMatrix(mat, rows, cols, 0, 2);

    cout << "\nTEMP:\n" << endl;
    for (int d = 0; d < rows-1; d++)
        {
            for (int e = 0; e < cols-1; e++)
                {
                    cout << tempMatrix[d][e] << " ";
                }
            cout << endl;
        }
    return 0;
}
    