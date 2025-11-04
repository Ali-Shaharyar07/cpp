


#include <iostream>

using namespace std;

int validateInput(int &num, int lower_bound, int upper_bound, string error_message)
{
    
    while (num < lower_bound || num > upper_bound)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid number of rows (1-10): ";
        cin >> num;
    }
}

int main()
{
    // User input for matrix dimensions
    int rows, cols;
    rows = validateInput(rows, )
    
    return 0;
}
    