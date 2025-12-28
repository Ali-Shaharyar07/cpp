//g++ -std=c++17 test.cpp -o tests && ./tests  ->test case command


#include <iostream>
using namespace std;

/*
 * Swaps the values stored at the two integer addresses.
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

}

/*
 * Reverses the segment of the array from index start to end (inclusive).
 * Uses swap() and pointer arithmetic only.
 */
void reverseSegment(int *arr, int size, int start, int end) {
    for (int i=0; i<size;i++)
    {
        if (i>=start && i<=end)
        {
            swap(arr+i, arr+end--);
        }
        
    }
}

/*
 * Displays all elements of the array in one line separated by spaces.
 * Access array elements using pointer arithmetic only.
 */
void displayArray(int *arr, int size) {
    
    for (int i=0; i<size; i++)
    {
        cout << *(arr+i) << " ";
    }
    cout << endl;

}

int main() {
    const int CAPACITY = 20;
    int arr[CAPACITY];

    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    while (size < 0 || size > 20)
    {
        cout << "Invalid input. Size is out of bounds." << endl;
        cout << "Please try again." << endl;
        cout << "Enter the size of the array: ";
        cin >> size; 
    }

    cout << "Enter " << size << " integers: ";
    for (int i=0; i<size; i++)
    {
        cin >> *(arr+i);
    }

    int start, end;
    cout << "Enter start and end indices to reverse: ";
    cin >> start >> end;
    while ((start < 0 || start > 20) || (end < 0 || end > 20) || (start > end))
    {
        if (start<0 || start > 20 || start > end)
            cout << "Invalid input. Start index is out of bounds." << endl;
        else
            cout << "Invalid input. End index is out of bounds." << endl;
       
        cout << "Please try again." << endl;
        cout << "Enter start and end indices to reverse: ";
        cin >> start >> end; 
    }
    
    cout << "Original array: ";
    displayArray(arr, size);
    cout << "Array after reversing segment " << start << " to " << end << ": ";
    reverseSegment(arr, size, start, end);
    displayArray(arr, size);
    
    return 0;
}
