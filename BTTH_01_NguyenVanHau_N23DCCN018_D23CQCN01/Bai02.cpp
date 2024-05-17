// Nguyen Van Hau
// N23DCCN018
// D23CQCN01-N

#include <iostream>

using namespace std;

int tong_le(int a[], int length);

int main()
{
    int arr[10];
    cout << "Nhap vao 10 so nguyen: ";
    for (int i = 0; i < 10; i++)
    {
        cin >> arr[i];
    }
    int result = tong_le(arr, 10);
    cout << "Tong cac so le trong mang: " << result << endl;
    return 0;
}

int tong_le(int a[], int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        if (a[i] % 2 != 0)
        {
            sum += a[i];
        }
    }
    return sum;
}