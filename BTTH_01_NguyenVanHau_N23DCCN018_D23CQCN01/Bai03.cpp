// Nguyen Van Hau
// N23DCCN018
// D23CQCN01-N

#include <iostream>

using namespace std;

int BSCNN(int a, int b);

int main()
{
    int n;
    do
    {
        cout << "Enter a value for n (n >= 2): ";
        cin >> n;
    } while (n < 2);

    int sum = 0;
    for (int i = 2; i <= n; i++)
    {
        sum += BSCNN(2 * i - 2, 2 * i);
    }

    cout << "T = " << sum << endl;

    return 0;
}

int BSCNN(int a, int b)
{
    int max = (a > b) ? a : b;
    int lcm = max;

    while (true)
    {
        if ((lcm % a == 0) && (lcm % b == 0))
        {
            break;
        }
        lcm += max;
    }

    return lcm;
}