// Nguyen Van Hau
// N23DCCN018
// D23CQCN01-N

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    const int size = 10;
    int arr[size];

    cout << "Enter " << size << " integers: ";
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    sort(arr, arr + size);

    cout << "Sorted array in ascending order: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}