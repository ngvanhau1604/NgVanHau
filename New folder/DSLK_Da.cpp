#include <iostream>
#include <cstring>
#include <conio.h>

using namespace std;

struct Sinhvien
{
    int maso;
    char ho[51];
    char ten[11];
};

struct node
{
    Sinhvien sv;
    node *lk1, *lk2; // lk1 quản lý thứ tự maso tăng dần, lk2 quản lý thứ tự tên tăng dần
};

typedef node *PTR;

void themSV(PTR &head1, PTR &head2);
void loadfromFile(PTR &head1, PTR &head2);
void xoaSinhVien(PTR &head1, PTR &head2, int maso);
PTR timSinhVien(PTR head, int maso);
void lietKeTheoMaso(PTR head);
void lietKeTheoTen(PTR head);
void saveToFile(PTR head);
void giaiPhong(PTR &head);

int main()
{
    PTR head1 = nullptr, head2 = nullptr;
    int choice, maso;
    PTR sv = nullptr;
    loadfromFile(head1, head2);
    do
    {
        system("cls");
        cout << "Chuong trinh quan ly sinh vien\n";
        cout << "1. Nhap danh sach sinh vien\n";
        cout << "2. Xoa sinh vien theo ma so\n";
        cout << "3. Tim sinh vien theo ma so\n";
        cout << "4. Liet ke DSSV tang dan theo ma so\n";
        cout << "5. Liet ke DSSV tang dan theo ten\n";
        // cout << "6. Them sinh vien\n";
        cout << "6. Ket thuc\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            themSV(head1, head2);
            break;
        case 2:
            cout << "Nhap ma so sinh vien can xoa: ";
            cin >> maso;
            xoaSinhVien(head1, head2, maso);
            break;
        case 3:
            cout << "Nhap ma so sinh vien can tim: ";
            cin >> maso;
            sv = timSinhVien(head1, maso);
            if (sv)
            {
                cout << "Sinh vien tim thay: " << sv->sv.ho << " " << sv->sv.ten << endl;
            }
            else
            {
                cout << "Khong tim thay sinh vien\n";
            }
            getch();
            break;
        case 4:
            system("cls");
            cout << "Danh sach sinh vien tang dan theo ma so\n";
            cout << "Ma so\tHo\tTen\n";
            lietKeTheoMaso(head1);
            break;
        case 5:
            system("cls");
            cout << "Danh sach sinh vien tang dan theo ten\n";
            cout << "Ma so\tHo\tTen\n";
            lietKeTheoTen(head2);
            break;
        // case 6:
        //     Sinhvien sv;
        //     themSV(head1, head2, sv);
        //     break;
        case 6:
            saveToFile(head1);
            giaiPhong(head1);
            giaiPhong(head2);
            cout << "Ket thuc chuong trinh\n";
            break;
        default:
            cout << "Lua chon khong hop le\n";
        }
    } while (choice != 6);

    return 0;
}

void themSV(PTR &head1, PTR &head2)
{
    Sinhvien sv;
    while (1)
    {
        system("cls");

        cout << "Nhap ma so sinh vien: ";
        cin >> sv.maso;
        if (!timSinhVien(head1, sv.maso))
        {
            break;
        }
        cout << "Ma so sinh vien da ton tai\nAn phim bat ky de nhap lai\n";
        getch();
    }
    cout << "Nhap ho sinh vien: ";
    cin.ignore();
    cin.getline(sv.ho, 51);
    cout << "Nhap ten sinh vien: ";
    cin.getline(sv.ten, 11);

    PTR newNode = new node{sv, nullptr, nullptr};

    // Insert into lk1 (sorted by maso)
    if (!head1 || head1->sv.maso > sv.maso)
    {
        newNode->lk1 = head1;
        head1 = newNode;
    }
    else
    {
        PTR temp = head1;
        while (temp->lk1 && temp->lk1->sv.maso < sv.maso)
        {
            temp = temp->lk1;
        }
        newNode->lk1 = temp->lk1;
        temp->lk1 = newNode;
    }

    // Insert into lk2 (sorted by ten)
    if (!head2 || strcmp(head2->sv.ten, sv.ten) > 0)
    {
        newNode->lk2 = head2;
        head2 = newNode;
    }
    else
    {
        PTR temp = head2;
        while (temp->lk2 && strcmp(temp->lk2->sv.ten, sv.ten) < 0)
        {
            temp = temp->lk2;
        }
        newNode->lk2 = temp->lk2;
        temp->lk2 = newNode;
    }
}

void loadfromFile(PTR &head1, PTR &head2)
{
    system("cls");
    FILE *f = fopen(".//DSSV.DAT", "rb");
    Sinhvien sv;
    if (f)
    {

        while (fread(&sv, sizeof(Sinhvien), 1, f) != 0)
        {
            PTR newNode = new node{sv, nullptr, nullptr};

            // Insert into lk1 (sorted by maso)
            if (!head1 || head1->sv.maso > sv.maso)
            {
                newNode->lk1 = head1;
                head1 = newNode;
            }
            else
            {
                PTR temp = head1;
                while (temp->lk1 && temp->lk1->sv.maso < sv.maso)
                {
                    temp = temp->lk1;
                }
                newNode->lk1 = temp->lk1;
                temp->lk1 = newNode;
            }

            // Insert into lk2 (sorted by ten)
            if (!head2 || strcmp(head2->sv.ten, sv.ten) > 0)
            {
                newNode->lk2 = head2;
                head2 = newNode;
            }
            else
            {
                PTR temp = head2;
                while (temp->lk2 && strcmp(temp->lk2->sv.ten, sv.ten) < 0)
                {
                    temp = temp->lk2;
                }
                newNode->lk2 = temp->lk2;
                temp->lk2 = newNode;
            }
        }
        fclose(f);
    }
    else
    {
        cout << "Khong tim thay file DSSV.DAT\n";
        return;
    }
    cout << "Da nhap sinh vien tu file DSSV.DAT\n";
    // getch();
    _sleep(1000);
}

void xoaSinhVien(PTR &head1, PTR &head2, int maso)
{
    PTR prev = nullptr, temp = head1;

    // Remove from lk1
    while (temp && temp->sv.maso != maso)
    {
        prev = temp;
        temp = temp->lk1;
    }
    if (temp)
    {
        if (prev)
        {
            prev->lk1 = temp->lk1;
        }
        else
        {
            head1 = temp->lk1;
        }
    }

    prev = nullptr;
    temp = head2;

    // Remove from lk2
    while (temp && temp->sv.maso != maso)
    {
        prev = temp;
        temp = temp->lk2;
    }
    if (temp)
    {
        if (prev)
        {
            prev->lk2 = temp->lk2;
        }
        else
        {
            head2 = temp->lk2;
        }
        delete temp;
    }
}

PTR timSinhVien(PTR head, int maso)
{
    while (head && head->sv.maso != maso)
    {
        head = head->lk1;
    }
    return head;
}

void lietKeTheoMaso(PTR head)
{
    // system("cls");
    while (head)
    {
        cout << head->sv.maso << "\t" << head->sv.ho << "\t" << head->sv.ten << endl;
        head = head->lk1;
    }
    getch();
}

void lietKeTheoTen(PTR head)
{
    // system("cls");
    while (head)
    {
        cout << head->sv.maso << "\t" << head->sv.ho << "\t" << head->sv.ten << endl;
        head = head->lk2;
    }
    getch();
}

void saveToFile(PTR head)
{
    FILE *f = fopen(".//DSSV.DAT", "wb");
    if (f)
    {
        while (head)
        {
            fwrite(&head->sv, sizeof(Sinhvien), 1, f);
            head = head->lk1;
        }
        fclose(f);
    }
}
void giaiPhong(PTR &head)
{
    PTR temp = head;
    while (head)
    {
        temp = head;
        head = head->lk1;
        delete temp;
    }
}