#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


// TASK 1
// int main()
// {
//     const char STAR = '*';

//     string line = "*";
//     int x, length;
//     cin >> x;
    
//     length = 2*x-1;

//     for (int i=0; i < x; i++)
//     {
        
//         cout << setw((length+line.length())/2) << right << line << endl;
//         line += STAR;
//         line += STAR;
//     }

//     return 0;
// }


//TASK 2
// int main()
// {
//    const int COLS = 5;
//    int rows;
//    cin >> rows;

//    for (int i=0; i < rows; i++)
//    {
//     for (int j=0; j < COLS; j++)
//     {
//         if ((i%2 == 0 && j%2 == 0) || (i%2==1 && j%2 == 1))
//         {
//             cout << '.';
//         }
//         else
//         {
//             cout << '#';
//         }
//     }
//     cout << endl;
//    }

//     return 0;
// }

//TASK 3
// int main()
// {
//     int rows, cols, aisle;
//     cin >> rows >> cols >> aisle;
    
//     for (int i=0; i < rows; i++)
//     {   
//         for (int j=0; j < cols; j++)
//         {
//             if (j == aisle) continue;
//             cout << "R" << i+1 << "C" << j+1 << " ";
//         }
//         cout << endl;
//     }
//     return 0;
// }

//TASK 4
// int main()
// {
//    const char STAR = '*';
//    string line;
//    int n, length;
//    cout << " Enter the number of triangles\n ";
//    cin >> n;

//    for (int i=0; i < n; i++)
//    {
//         line = "*";
//         length = 2+i;
//         for (int c=0;c<length-1;c++)
//         {
//             line = " " + line;
//         }
//         for (int j = 0; j < length; j++)
//         {
//             cout << line << endl;
//             line = line.substr(1);
//             line += " ";
//             line += STAR;
//         }
//    }
// }

//PASCAL TRIANGLE

//TASK 4
int main()
{
   int rows, ans, n_factorial, n_r_factorial, r_factorial;
   cin >> rows;
   cout << "\n\n";


   for (int i=0; i<rows; i++)
   {

        for (int s=i; s<rows; s++)
        {
            cout << " ";
        }

        for (int j=0; j<=i; j++)
        {
            n_factorial = 1;
            n_r_factorial = 1;
            r_factorial = 1;
            if (i==0)
            {
                ans = 1;
            }
            else
            {
                for (int k=i; k>0;k--)
                {
                    n_factorial *= k;
                }
                for (int k=i-j; k>0;k--)
                {
                    n_r_factorial *= k;
                }
                if (j==0)
                {
                    r_factorial = 1;
                }
                else
                {
                    for (int k=j; k>0; k--)
                    {
                        r_factorial *= k;
                    }
                }
                
                //cout << "i: " << i << " j: " << j << " n: " << n_factorial << " n-r: " << n_r_factorial << " r: " << r_factorial << endl;
                ans = n_factorial/((n_r_factorial)*(r_factorial));
                
            }
            cout << ans << " ";
            
        }
        cout << endl;
   }
}