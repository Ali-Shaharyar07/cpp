#include <iostream>
using namespace std;

const int CAPACITY = 5;
int values[CAPACITY];

void print_array(int size)
{
for(int i=0;i<size;i++)
cout<< values[i]<<endl;
}
int main() {
int size=0;
int i=0;
int input;
while (cin >> input)
{
if (size < CAPACITY)
{
values[size] = input;
size++;
}
}
print_array(size);
}