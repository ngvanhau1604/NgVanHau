#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <conio.h>

using namespace std;

struct Employee
{
    char manv[8];
    char ho[40];
    char ten[10];
    char mapb[10];
    float luong;
};

const int MAX_EMPLOYEES = 300;

struct ListEmployee
{
    Employee nv[MAX_EMPLOYEES];
    int soluong;
};

void sortByMapb(ListEmployee &ds)
{
    for (int i = 0; i < ds.soluong - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < ds.soluong; ++j)
        {
            if (strcmp(ds.nv[j].mapb, ds.nv[minIndex].mapb) < 0)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(ds.nv[i], ds.nv[minIndex]);
        }
    }
}

void calculateSalaryByDepartment(const ListEmployee &ds)
{
    vector<string> processedDepartments;
    cout << left << setw(15) << "Ma phong ban" << setw(15) << "Tong luong" << endl;

    for (int i = 0; i < ds.soluong; ++i)
    {
        string currentMapb = ds.nv[i].mapb;
        if (find(processedDepartments.begin(), processedDepartments.end(), currentMapb) == processedDepartments.end())
        {
            float totalSalary = 0;
            for (int j = 0; j < ds.soluong; ++j)
            {
                if (strcmp(ds.nv[j].mapb, currentMapb.c_str()) == 0)
                {
                    totalSalary += ds.nv[j].luong;
                }
            }
            cout << left << setw(15) << currentMapb << setw(15) << totalSalary << endl;
            processedDepartments.push_back(currentMapb);
        }
    }
}

bool cmp(bool flag, const Employee &a, const Employee &b)
{
    if (flag)
        return stricmp(a.manv, b.manv) > 0;
    else
        return stricmp(a.ten, b.ten) > 0;
}

int *orderEmployees(const ListEmployee ds, bool flag = true)
{

    bool f[ds.soluong];
    for (int i = 0; i < ds.soluong; ++i)
    {
        f[i] = true;
    }

    int j;
    int *order = new int[ds.soluong];
    for (int i = 0; i < ds.soluong; ++i)
    {
        j = 0;
        while (j < ds.soluong)
        {
            if (f[j])
                break;
            j++;
        }
        order[i] = j;
        for (j = 0; j < ds.soluong; ++j)
        {
            if (f[j])
                if (cmp(flag, ds.nv[order[i]], ds.nv[j]) > 0)
                {
                    order[i] = j;
                }
        }
        f[order[i]] = false;
    }

    return order;
}

void displayEmployees(const ListEmployee &ds)
{
    cout << left << setw(20) << "Ma nhan vien" << setw(20) << "Ho" << setw(15) << "Ten" << setw(25) << "Ma phong ban" << setw(15) << "Luong" << endl;
    for (int i = 0; i < ds.soluong; ++i)
    {
        cout << left << setw(20) << ds.nv[i].manv
             << setw(20) << ds.nv[i].ho
             << setw(15) << ds.nv[i].ten
             << setw(25) << ds.nv[i].mapb
             << setw(15) << ds.nv[i].luong
             << endl;
    }
}

void displayOrder(int *order, const ListEmployee &ds)
{
    cout << left << setw(20) << "Ma nhan vien" << setw(20) << "Ho" << setw(15) << "Ten" << setw(25) << "Ma phong ban" << setw(15) << "Luong" << endl;
    for (int i = 0; i < ds.soluong; ++i)
    {
        cout << left << setw(20) << ds.nv[order[i]].manv
             << setw(20) << ds.nv[order[i]].ho
             << setw(15) << ds.nv[order[i]].ten
             << setw(25) << ds.nv[order[i]].mapb
             << setw(15) << ds.nv[order[i]].luong
             << endl;
    }
}

void displayMenu()
{
    cout << "0. Hien thi danh sach nhan vien" << endl;
    cout << "1. Nhap danh sach nhan vien" << endl;
    cout << "2. Hien thi theo ma nhan vien va ten" << endl;
    cout << "3. Sap xep theo ma phong ban" << endl;
    cout << "4. Tinh tong luong theo phong ban" << endl;
    cout << "5. Thoat" << endl;
    cout << "6. Luu danh sach nhan vien vao file" << endl;
    cout << "7. Tai danh sach nhan vien tu file" << endl;
}

void saveFile(ListEmployee &ds)
{
    ofstream outFile("employees.bin", ios::binary); // Open file in binary mode
    if (!outFile)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Write the number of employees
    outFile.write(reinterpret_cast<const char *>(&ds.soluong), sizeof(ds.soluong));

    // Write the employee data
    for (int i = 0; i < ds.soluong; ++i)
    {
        outFile.write(reinterpret_cast<const char *>(&ds.nv[i]), sizeof(Employee));
    }

    outFile.close();
    cout << "Danh sach nhan vien da duoc luu vao file employees.bin" << endl;
}

void loadFile(ListEmployee &ds)
{
    ifstream inFile("employees.bin", ios::binary); // Open file in binary mode
    if (!inFile)
    {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    // Read the number of employees
    inFile.read(reinterpret_cast<char *>(&ds.soluong), sizeof(ds.soluong));

    // Read the employee data
    for (int i = 0; i < ds.soluong; ++i)
    {
        inFile.read(reinterpret_cast<char *>(&ds.nv[i]), sizeof(Employee));
    }

    inFile.close();
    cout << "Danh sach nhan vien da duoc tai tu file employees.bin" << endl;
}

void enteringEmpoyees(ListEmployee &ds)
{
    if (ds.soluong >= MAX_EMPLOYEES)
    {
        cout << "Danh sach nhan vien da day!" << endl;
        return;
    }
    system("cls");
    cout << "Nhap thong tin nhan vien thu " << ds.soluong + 1 << ":" << endl;
    while (true)
    {
        cout << "Nhap ma nhan vien (nhap 0 de ket thuc): ";
        cin >> ds.nv[ds.soluong].manv;
        if (strcmp(ds.nv[ds.soluong].manv, "0") == 0)
        {
            return;
        }
        cout << "Nhap ho nhan vien: ";
        cin.ignore();
        cin.getline(ds.nv[ds.soluong].ho, 40);
        cout << "Nhap ten nhan vien: ";
        cin.getline(ds.nv[ds.soluong].ten, 10);
        cout << "Nhap ma phong ban: ";
        cin >> ds.nv[ds.soluong].mapb;
        cout << "Nhap luong: ";
        cin >> ds.nv[ds.soluong].luong;
        ds.soluong++;
    }
}

int main()
{

    ListEmployee ds;
    loadFile(ds);

    int choice;
    while (true)
    {
        system("cls");
        cout << "==================== MENU ====================" << endl;
        displayMenu();
        cout << "Chon chuc nang: ";
        cin >> choice;
        switch (choice)
        {
        case 0:
        {
            cout << "Danh sach nhan vien:" << endl;
            displayEmployees(ds);
            getch();
            break;
        }
        case 1:
        {
            cout << "Nhap danh sach nhan vien:" << endl;
            enteringEmpoyees(ds);
            // displayEmployees(ds);
            break;
        }
        case 2:
        {
            cout << "Sap xep danh sach nhan vien theo ten va ma nhan vien:" << endl;

            cout << "Danh sach nhan vien da sap xep theo ma nhan vien:" << endl;
            displayOrder(orderEmployees(ds), ds);
            cout << endl;

            cout << "Danh sach nhan vien da sap xep theo ten:" << endl;
            displayOrder(orderEmployees(ds, false), ds);
            cout << endl;
            getch();
            break;
        }
        case 3:
            sortByMapb(ds);
            displayEmployees(ds);
            getch();
            break;
        case 4:
            calculateSalaryByDepartment(ds);
            getch();
            break;
        case 5:
            return 0;
        case 6:
            saveFile(ds);
            break;
        case 7:
            loadFile(ds);
            break;
        default:
            cout << "Chuc nang khong hop le. Vui long chon lai." << endl;
        }
    }
    return 0;
}