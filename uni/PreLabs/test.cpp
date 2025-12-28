#include <iostream>
#include <vector>
using namespace std;






int main() {

    int t[] = {1, 2, 3, 4, 5};
    vector<int> v;
    
    //cout << "size: " << v.size() << " first: " << v[0] << " 5th: " << v[4] <<  endl;
    cout << "VECTOR size: " << v.size() << " Capacity: " << v.capacity() << endl;
    v.reserve(10);
    for (int i=0; i<10; i++)
    {
        v.push_back(i);
        cout << v.at(i) << " size: " << v.size() << " Capacity: " << v.capacity() << endl;
    }
        
    cout << endl;
}