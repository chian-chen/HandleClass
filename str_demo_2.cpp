#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main()
{

    string str;
    while (true)
    {
        cout << ">>> ";
        getline(cin, str);
        char *c_str = new char[str.length() + 1];
        strcpy(c_str, str.c_str());
        char *token;
        token = strtok(c_str, " ");
        if (strcmp(token, "quit") == 0)
            break;
        while (token != NULL)
        {
            cout << token << ",";
            token = strtok(NULL, " ");
        }
        cout << endl;
        delete[] c_str;
    }

    return 0;
}