// Nguyen Van Hau
// N23DCCN018
// D23CQCN01-N

#include <iostream>
#include <string>

using namespace std;

int countSubstring(const string &str, const string &sub);

int main()
{
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    int count = countSubstring(input, "it");
    cout << "Number of 'it' substrings: " << count << endl;

    return 0;
}

int countSubstring(const string &str, const string &sub)
{
    int count = 0;
    size_t pos = 0;

    while ((pos = str.find(sub, pos)) != string::npos)
    {
        count++;
        pos += sub.length();
    }

    return count;
}