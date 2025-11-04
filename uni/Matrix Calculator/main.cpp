#include <iostream>

using namespace std;

// Addition Logic
int** addMatrices(int** mat1, int**mat2, int rows1, int cols1, int rows2, int cols2)
{
    //Checking Dimension constraints
    if (rows1 != rows2 || cols1 != cols2)
    {
        cout << "Matrices must have the same dimensions for addition." << endl;
        return nullptr;
    }
    else
    {
        // Addition
        int** result = new int*[rows1];
        for (int i = 0; i < rows1; i++)
        {
            result[i] = new int[cols1];
            for (int j = 0; j < cols1; j++)
            {
                result[i][j] = mat1[i][j] + mat2[i][j];
            }
        }

        return result;
    }  
}

// Subtraction Logic
int** subtractMatrices(int** mat1, int**mat2, int rows1, int cols1, int rows2, int cols2)
{
    //Checking Dimension constraints
    if (rows1 != rows2 || cols1 != cols2)
    {
        cout << "Error: Matrices must have the same dimensions for subtraction." << endl;
        return nullptr;
    }
    else
    {
        // Subtraction
        int** result = new int*[rows1];
        for (int i = 0; i < rows1; i++)
        {
            result[i] = new int[cols1];
            for (int j = 0; j < cols1; j++)
            {
                result[i][j] = mat1[i][j] - mat2[i][j];
            }
        }

        return result;
    }
}

int** multiplyMatrices(int** mat1, int**mat2, int rows1, int cols1, int rows2, int cols2)
{
    // Checking Dimension constraints
    if (cols1 != rows2)
    {
        cout << "Number of columns in the first matrix must be equal to the number of rows in the second matrix." << endl;
        return nullptr;
    }
    else
    {
        // Multiplication
        int** result = new int*[rows1];
        //result initialization to 0
        for (int i = 0; i < rows1; i++)
        {
            result[i] = new int[cols2];
            for (int j = 0; j < cols2; j++)
            {
                result[i][j] = 0;
            }

        }
        // Multiplication logic
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols2; j++)
            {
                for (int k = 0; k < rows2; k++)
                {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }



        return result;
    }
}

int** transposeMatrix(int**mat, int rows, int cols)
{
    //Result initialization
    int** result = new int*[cols];
    for (int i = 0; i < cols; i++)
    {
        result[i] = new int[rows];
    }

    //Transpose
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[j][i] = mat[i][j];
        }
    }

    return result;
}

int** subMatrix(int**mat, int rows, int cols, int rpos, int cpos)
{   //Temp initialization
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

    //Filling the sub-matrix
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
        //Calculating determinant
        int det = 0;
        for (int i=0; i<cols; i++)
        {
            if (i%2==0)
            {
                det += mat[0][i]*detMatrix(subMatrix(mat, rows, cols, 0, i), rows-1, cols-1);
            }
            else
            {
                det -= mat[0][i]*detMatrix(subMatrix(mat, rows, cols, 0, i), rows-1, cols-1);
            }
        }
        return det;
    }
}

int** inverseMatrix(int** mat, int rows, int cols)
{
    //Result Matrix initialization
    int** result = new int*[rows];
    for (int i=0; i<rows; i++)
    {
        result[i] = new int[cols];
        for (int j=0; j<cols; j++)
        {
            result[i][j] = 0;
        }
    }

    //Calculating the cofactors
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            if((i%2==0 && j%2==0) || (i%2==1 && j%2==1))
            {
                result[i][j] = detMatrix(subMatrix(mat, rows, cols, i, j), rows, cols);
            }
            else
            {
                result[i][j] = -detMatrix(subMatrix(mat, rows, cols, i, j), rows, cols);
            }
        }
    }
    //Transposing 
    result = transposeMatrix(result, rows, cols);
    return result;

}


//Function to clear the input stream
void clearInput()
{
    cin.clear();
    cin.ignore(1000, '\n');
}



int main()
{
    // User input for matrix dimensions
    int rows1, cols1, rows2, cols2;
    cout << "Enter number of rows for matrix 1: ";
    cin >> rows1;

    // Input validation
    while (rows1 <= 0 || rows1 > 10)
    {
        clearInput();
        cout << "Please enter a valid number of rows (1-10): ";
        cin >> rows1;
    }

    clearInput();

    cout << "Enter number of columns for matrix 1: ";
    cin >> cols1;
    // Input validation
    while (cols1 <= 0 || cols1 > 10)
    {
        clearInput();
        cout << "Please enter a valid number of columns (1-10): ";
        cin >> cols1;
    } 
    cout << '\n';

    clearInput();
    

    cout << "Enter number of rows for matrix 2: ";
    cin >> rows2;
    // Input validation
    while (rows2 <= 0 || rows2 > 10)
    {
        clearInput();
        cout << "Please enter a valid number of rows (1-10): ";
        cin >> rows2;
    }

    clearInput();

    cout << "Enter number of columns for matrix 2: ";
    cin >> cols2;
    // Input validation
    while (cols2 <= 0 || cols2 > 10)
    {
        clearInput();
        cout << "Please enter a valid number of columns (1-10): ";
        cin >> cols2;
    }

    //Dynamically allocating 2D arrays as matrices
    int** mat1 = new int*[rows1];
    for (int i = 0; i < rows1; i++)
    {
        mat1[i] = new int[cols1];
    }

    int** mat2 = new int*[rows2];
    for (int i = 0; i < rows2; i++)
    {
        mat2[i] = new int[cols2];
    }

    clearInput();
    
    // User input to fill the matrices
    cout << "\nEnter elements of the matrix 1: ";
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
           while (true)
           {
                if (cin >> mat1[i][j])
                    break;
                else
                {
                    clearInput();
                    cout << "Invalid input. Please enter an integer" << endl;
                }
           }
        }
    }
    clearInput();
    
    cout << "\nEnter elements of the matrix 2: ";
    for (int i = 0; i < rows2; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            while (true)
            {
                if (cin >> mat2[i][j])
                    break;
                else
                {
                    clearInput();
                    cout << "Invalid input. Please enter an integer" << endl;
                }
            }
        }
    }
    clearInput();
    

    // Displaying the matrices
    cout << "\nMatrix 1 is:\n" << endl;
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            cout << mat1[i][j] << " ";
        }
        cout << endl;
    }
    cout << '\n';

    cout << "\nMatrix 2 is:\n" << endl;
    for (int i = 0; i < rows2; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            cout << mat2[i][j] << " ";
        }
        cout << endl;
    }
    cout << '\n';


    // Menu Decision logic
    bool isRunning = true;
    
    do
    {
        // Displaying menu
        int choice;
        cout << "\n-=-=- Menu -=-=-" << endl;
        cout << "\n1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Transpose" << endl;
        cout << "5. Determinant" << endl;
        cout << "6. Inverse" << endl;
        cout << "7. Exit" << endl;
        cout << "\nEnter your choice: ";
        while (true)
            {
                if (cin >> choice)
                    break;
                else
                {
                    clearInput();
                    cout << "Invalid input. Please enter an integer" << endl;
                }
            }
        cout << '\n';

        int** answer;
        int num;
        int matrixNum;
        switch (choice)
        {

            case 1:
                //Addition Handler
                cout << "You chose Addition" << endl;
                answer = addMatrices(mat1, mat2, rows1, cols1, rows2, cols2);
                if (answer == nullptr)
                {
                    cout << "Dimension mismatch." << endl;
                }
                else
                {
                    cout << "Resultant Matrix after Addition is:\n" << endl;
                    for (int i = 0; i < rows1; i++)
                    {
                        for (int j = 0; j < cols1; j++)
                        {
                            cout << answer[i][j] << " ";
                        }
                        cout << endl;
                    }
                    // Deallocating the answer matrix
                    for (int i = 0; i < rows1; i++)
                    {
                        delete[] answer[i];
                    }
                    delete[] answer;
                }
                break;
        

            case 2:
                //Subtraction Handler
                cout << "You chose Subtraction" << endl;
                answer = subtractMatrices(mat1, mat2, rows1, cols1, rows2, cols2);
                if (answer == nullptr)
                {
                    cout << "Dimension mismatch." << endl;
                }
                else
                {
                    cout << "Resultant Matrix after Subtraction is:\n" << endl;
                    for (int i = 0; i < rows1; i++)
                    {
                        for (int j = 0; j < cols1; j++)
                        {
                            cout << answer[i][j] << " ";
                        }
                        cout << endl;
                    }
                    // Deallocating the answer matrix
                    for (int i = 0; i < rows1; i++)
                    {
                        delete[] answer[i];
                    }
                    delete[] answer;
                }
                break;
            
            case 3:
                cout << "You chose Multiplication" << endl; 
                answer = multiplyMatrices(mat1, mat2, rows1, cols1, rows2, cols2);
                if (answer == nullptr)
                {
                    cout << "Dimension mismatch." << endl;
                }
                else
                {
                    cout << "Resultant Matrix after Multiplication is:\n" << endl;
                    for (int i = 0; i < rows1; i++)
                    {
                        for (int j = 0; j < cols2; j++)
                        {
                            cout << answer[i][j] << " ";
                        }
                        cout << endl;
                    }
                    // Deallocating the answer matrix
                    for (int i = 0; i < rows1; i++)
                    {
                        delete[] answer[i];
                    }
                    delete[] answer;
                }
                break;

            case 4:
                cout << "You chose Transpose" << endl;
                cout << "Enter 1 to transpose Matrix 1 or 2 to transpose Matrix 2: ";
                cin >> matrixNum;
                clearInput();
                
                if (matrixNum == 1)
                {
                    answer = transposeMatrix(mat1, rows1, cols1);
                        cout << "Resultant Matrix after Transpose is:\n" << endl;
                    
                        for (int i=0; i < cols1; i++)
                        {
                            for (int j = 0; j < rows1; j++)
                            {
                                cout << answer[i][j] << " ";
                            }
                            cout << endl;
                        }

                        // Deallocating the answer matrix
                    for (int i = 0; i < cols1; i++)
                    {
                        delete[] answer[i];
                    }
                    delete[] answer;
                }
                else
                {
                    if (matrixNum == 2)
                    {
                        answer = transposeMatrix(mat2, rows2, cols2);
                        cout << "Resultant Matrix after Transpose is:\n" << endl;

                        for (int i=0; i < cols2; i++)
                        {
                            for (int j = 0; j < rows2; j++)
                            {
                                cout << answer[i][j] << " ";
                            }
                            cout << endl;
                        }

                        // Deallocating the answer matrix
                        for (int i = 0; i < cols2; i++)
                            {
                            delete[] answer[i];
                            }
                        delete[] answer;
                    }
                    else
                    {
                        cout << "Invalid choice!" << endl;
                        answer = nullptr;
                        break;
                    }
                } 
            
                break;

            case 5:
                cout << "You chose Determinant" << endl;
                cout << "Enter 1 to calculate Matrix 1 Determinant or 2 to calculate Matrix 2 Determinant: ";
                cin >> matrixNum;
                clearInput();
                
                //Dimension Checking
                if (matrixNum == 1)
                {
                    if (rows1 != cols1)
                    {
                        cout << "Dimension mismatch." << endl;
                    }
                    else
                    {
                        num = detMatrix(mat1, rows1, rows2);
                        cout << "Determinant of Matrix 1 is: " << detMatrix(mat1, rows1, rows2);
                    }
                }
                else
                {
                    if (matrixNum == 2)
                    {
                        if (rows2 != cols2)
                        {
                            cout << "Dimension mismatch." << endl;
                        }
                        else
                        {
                            num = detMatrix(mat2, rows2, rows2);
                            cout << "Determinant of Matrix 2 is: " << detMatrix(mat2, rows2, rows2);
                        }
                    }
                    else
                    {
                        cout << "Invalid choice!" << endl;
                        answer = nullptr;
                        break;
                    }
                } 

                break;
            
            case 6:
                cout << "You chose Inverse" << endl;
                cout << "Enter 1 to calculate Inverse of Matrix 1 or 2 to calculate Inverse of Matrix 2: ";
                cin >> matrixNum;
                clearInput();
                
                
                if (matrixNum == 1)
                {
                    if (rows1 != cols1)
                    {
                        cout << "Dimension mismatch." << endl;
                    }
                    else
                    {
                        answer = inverseMatrix(mat1, rows1, cols1);
                    }
                }
                else
                {
                    if (matrixNum == 2)
                    {
                        if (rows2 != cols2)
                        {
                            cout << "Dimension mismatch." << endl;
                        }
                        else
                        {
                            answer = inverseMatrix(mat2, rows2, cols2);
                        }
                    }
                    else
                    {
                        cout << "Invalid choice!" << endl;
                        answer = nullptr;
                        break;
                    }
                }
                break;

            case 7:
                cout << "Exiting the program." << endl;
                isRunning = false;
                break;
            
            default:
                cout << "Invalid choice!" << endl;
                break;
        } 
    } while (isRunning);
    

    // Deallocating the matrices
    for (int i = 0; i < rows1; i++)
    {
        delete[] mat1[i];
    }
    delete[] mat1;

    for (int i = 0; i < rows2; i++)
    {
        delete[] mat2[i];
    }
    delete[] mat2;
    return 0;
}


