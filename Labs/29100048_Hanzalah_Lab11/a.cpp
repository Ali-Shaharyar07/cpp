// g++ -std=c++17 test.cpp -o tests && ./tests ->test case command
//#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int fac(int n)
{
    if (n==0)
    {
        return 1;
    }
    else
    {
        return n*fac(n-1);
    }
}

int fib(int n)
{
    if (n<=1)
    {
        return n;
    }
    else
    {
        return fib(n-1)+fib(n-2);
    }
}

void t(int l)
{
    if (l==1)
    {
        cout << "[]" << endl;
        return;
    }
    else
    {
        t(l-1);
        for (int i=0; i<l; i++)
        cout << "[] ";
        cout << endl;
        return;
    }

}

void pl(int l)
{
    for (int r=0;r<=l;r++)
    {
        if (r==0 || r==l)
        {
            cout << "1";
        }
        else
        {
            int n=1;
            int k=1;
            int t=1;
            for (int i=2; i<=l;i++) n *= i;
            for (int i=2; i<=r; i++) k *= i;
            for (int i=2; i<=l-r; i++) t *= i;
            cout << (n)/((t)*k);
        }
        cout << " ";
    }
    cout << endl;
}

void ssorta(int a[], int n)
{
    for (int i=0; i<n-1; i++)
    {
        int mp = i;
        for (int j=i+1; j<n;j++) 
        {
         if (a[j] < a[mp]) mp = j;
        }    
        if (i != mp)
        {
            int temp = a[i];
            a[i] = a[mp];
            a[mp] = temp;
        }
    }
}

void ssortd(int a[], int n)
{
    for (int i=0; i<n-1; i++)
    {
        int max_pos = i;
        for (int j=i+1; j<n; j++)
        {
            if (a[j]>a[max_pos])
            {
                max_pos = j;
            }
        }

        if (max_pos!=i)
        {
            int temp = a[i];
            a[i] = a[max_pos];
            a[max_pos] = temp;
        }
    }
}

int main() {
    
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int b[10] = {10, 4, 7, 5, 7, 2, 11, 100, 9, -1};
    int r=7, c=2;
    //cout << *(*(a+r)+c) << endl;
    //t(5);
    //cout << fib(5) << endl;

    ssortd(b,10);
    
    for (int i=0; i<10; i++)
    {
        cout << b[i] << " ";
    }    
    cout << endl;

    ssorta(b,10);
    for (int i=0; i<10; i++)
    {
        cout << b[i] << " ";
    }    
    cout << endl;
    return 0;
}
