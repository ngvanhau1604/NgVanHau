// Nguyen Van Hau
// N23DCCN018
// D23CQCN01-N

#include <iostream>
#include <iomanip>

using namespace std;

float trung_binh(int a, int b, int c);

int main()
{
    int num1, num2, num3;

    cout << "Nhap vao 3 so nguyen: ";
    cin >> num1 >> num2 >> num3;

    int max = num1;
    if (num2 > max)
    {
        max = num2;
    }
    if (num3 > max)
    {
        max = num3;
    }
    cout << "Gia tri lon nhat la: " << max << endl;

    float average = trung_binh(num1, num2, num3);
    cout << "Gia tri trung binh la: " << fixed << setprecision(3) << average << endl;

    return 0;
}

float trung_binh(int a, int b, int c)
{
    return (a + b + c) / 3.0f;
}