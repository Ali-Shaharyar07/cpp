// g++ -std=c++17 test.cpp -o tests && ./tests ->test case command

#include <iostream>
#include <string>
using namespace std;

/*
 * Copies one line (string line) into the buffer starting at buff.
 * Replaces the end of the line with '\0'.
 * Returns the address where the next line should start.
 */
char* insertLine(char *buff, string line) {
    int i=0, size = line.length();
    while(size--)
    {
        *(buff+i) = line[i];
        i++;
    }
    *(buff+i) = '\0';
    buff=buff+i+1;

    return (buff);


}

/*
 * Prints a single line starting from ptr until '\0' is found.
 * Then prints a newline.
 */
void printLine(char *ptr) {
    int i=0;
    while (*(ptr+i) != '\0')
    {
        cout << *(ptr+i++);
    }
    cout << '\n';
}

int main() {
    char buffer[1000];
    char *lines[100];

    char* free = &buffer[0];
    string str;
    cout << "Enter text lines (type END to stop):" << endl;
    getline(cin, str);
    int c=0;
    while (str != "END")
    {
        *(lines+c) = free;
        free = insertLine(free, str);
        c++;
        getline(cin, str);
    }

    cout << endl;

    cout << "Lines in reverse order:"<< endl;
    for (int i=c-1; i>=0;i--)
    {
        printLine(*(lines+i));
    }

    return 0;
}
