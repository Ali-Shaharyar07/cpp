#include <iostream>

using namespace std;

int** subMatrix(int**mat, int rows, int cols, int rpos, int cpos)
{   //Temp init
    int** tempMatrix = new int*[rows-1];
    for (int i = 0; i < rows-1; i++)
    {
        for (int j = 0; j < cols-1; j++)
        {
            tempMatrix[i] = new int[cols-1];
        }
    }
    int c = 0;
    int r = 0;
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


int detMatrix(int** mat, int rows, int cols)
{
    
    if (rows == 2 && cols == 2)
    {
        return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    }
    else
    {
        int det = 0;
        for (int i=0; i<cols; i++)
        {
            if (i%2==0)
            {
                det += mat[0][i]*detMatrix(subMatrix(mat, rows, cols, 0, i), rows-1, cols-1);
                cout << "i: " << i << " det: " << det << endl;
            }
            else
            {
                det -= mat[0][i]*detMatrix(subMatrix(mat, rows, cols, 0, i), rows-1, cols-1);
                cout << "i: " << i << " det: " << det << endl;
            }
        }
        return det;
    }
}




int main()
{
    // User input for matrix dimensions
    int rows1, cols1, rows2, cols2;
    cout << "Enter number of rows for matrix 1: ";
    cin >> rows1;
    cout << "Enter number of columns for matrix 1: ";
    cin >> cols1;
    cout << '\n';

    int** mat1 = new int*[rows1];
    for (int i = 0; i < rows1; i++)
    {
        mat1[i] = new int[cols1];
    }
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            cin >> mat1[i][j];
        }
    }
    cout << '\n';

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            cout << mat1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "det: " << detMatrix(mat1, rows1, cols1) << endl;

    return 0;
}