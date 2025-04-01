#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "mylib.h"
using namespace std;

struct Sinhvien
{
	int maso;
	char ho[51];
	char ten[11];
	float dtb;
	int hang;
};

struct node
{
	Sinhvien sv;
	node *next;
};

struct listName
{
	char ten[11];
	int soluong;
	node *dsSV[100];
};

typedef struct listName *PTRname;

typedef struct node *PTR;

const int so_item = 15;
const int dong = 5;
const int cot = 40;
char thucdon[so_item][50] = {"1. Nhap danh sach sinh vien         ",
							 "2. Liet ke danh sach                ",
							 "3. Them ve dau danh sach            ",
							 "4. Them sv o vi tri i               ",
							 "5. Xoa sinh vien theo ma so         ",
							 "6. Them 1 sv vao danh sach co thu tu",
							 "7. Loc SV trung theo ten            ",
							 "8. Sap xep dssv theo ma so tang dan ",
							 "9. Save DSSV                        ",
							 "10.Load DSSV                        ",
							 "11.Xep hang theo DTB                ",
							 "12.Xoa sinh vien theo ten           ",
							 "13.Dao nguoc danh sach              ",
							 "14.Copy danh sach                   ",
							 "15.Ket thuc chuong trinh            "};

int Delete_First(PTR &First)
{
	PTR p;
	if (First == NULL)
		return 0;
	p = First; // nut can xoa la nut dau
	First = p->next;
	delete p;
	return 1;
}

int Menu(char td[so_item][50])
{
	system("cls");
	int chon = 0;
	int i;
	for (i = 0; i < so_item; i++)
	{
		gotoxy(cot, dong + i);
		cout << td[i];
	}
Nhaplai:
	gotoxy(cot, dong + so_item);
	cout << "Ban chon 1 so (1.." << so_item << "):       ";
	gotoxy(wherex() - 4, wherey());
	cin >> chon;
	if (chon < 1 || chon > so_item)
		goto Nhaplai;
	return chon;
}

void BaoLoi(char *s)
{
	int x = wherex(), y = wherey();
	gotoxy(10, 24);
	cout << s;
	Sleep(4000);
	gotoxy(10, 24);
	clreol();
	gotoxy(x, y);
}

PTR Search(PTR First, int x)
{
	for (PTR p = First; p != NULL; p = p->next)
		if (p->sv.maso == x)
			return p;
	return NULL;
}

int NhapSV(PTR First, Sinhvien &sv)
{
NhaplaiMaSV:
	system("cls");
	cout << "Nhap thong tin sinh vien:\n";
	cout << "\nMa so sinh vien (<=0 dung nhap):";
	cin >> sv.maso;
	if (sv.maso <= 0)
		return 0;
	if (Search(First, sv.maso) != NULL)
	{
		BaoLoi("Ma so sinh vien bi trung. Ban nhap lai. ");
		goto NhaplaiMaSV;
	}
	fflush(stdin);
	cout << "Ho sinh vien  :";
	gets(sv.ho);
	fflush(stdin);
	cout << "Ten sinh vien :";
	gets(sv.ten);
	cout << "Diem TB :";
	cin >> sv.dtb;
	sv.hang = 0;
	return 1;
}

void Insert_First(PTR &First, Sinhvien &sv)
{
	PTR p = new node;
	p->sv = sv;
	p->next = First;
	First = p;
}

void NhapSV_VeDau(PTR &First)
{
	// system("cls");
	PTR p;
	Sinhvien sv;
	int err;
	while (1)
	{
		err = NhapSV(First, sv);
		if (err == 1)
			return;
		Insert_First(First, sv);
	}
}

void Nhap_DSSV(PTR &First)
{ // them ve cuoi
	system("cls");
	PTR p, Last;
	Sinhvien sv;
	int err;
	if (First != NULL)
		for (Last = First; Last->next != NULL; Last = Last->next)
			;

	while (true)
	{
		err = NhapSV(First, sv);
		if (err == 0)
			return;

		p = new node;
		p->sv = sv;
		p->next = NULL;
		if (First == NULL)
			First = p;
		else
			Last->next = p;
		Last = p;
	}
}

void LietKe(PTR First)
{
	int dem = 0;
	system("cls");
	printf("MaSV\tHo\tTen\t\tDTB\tHang\n");
	for (PTR p = First; p != NULL; p = p->next)
	{
		cout << p->sv.maso << "\t" << p->sv.ho << "\t" << p->sv.ten << "\t\t" << p->sv.dtb << "\t" << p->sv.hang << endl;
		dem++;
	}
	cout << "\nSo luong Sv = " << dem;
	getch();
}

int Reccount(PTR First)
{
	int dem = 0;
	for (PTR p = First; p != NULL; p = p->next)
		dem++;
	return dem;
}

int SaveFile(PTR First, char *tenfile)
{
	FILE *f = fopen(tenfile, "wb");
	if (f == NULL)
		return 0;
	for (PTR p = First; p != NULL; p = p->next)
		fwrite(&p->sv, sizeof(Sinhvien), 1, f);
	fclose(f);
	return 1;
}

void InsertLast(PTR &First, Sinhvien sv)
{
	PTR p = new node;
	p->sv = sv;
	p->next = NULL;
	if (First == NULL)
		First = p;
	else
	{
		PTR Last;
		for (Last = First; Last->next != NULL; Last = Last->next)
			;
		Last->next = p;
	}
}

int OpenFile(PTR &First, char *tenfile)
{
	PTR p;
	Sinhvien sv;
	FILE *f = fopen(tenfile, "rb");
	if (f == NULL)
		return 0; // mo file khong duoc

	while (First != NULL)
	{
		p = First;
		First = p->next;
		delete p;
	}
	while (fread(&sv, sizeof(Sinhvien), 1, f) == 1)
		InsertLast(First, sv);
	fclose(f);
	return 1;
}

bool XacNhan(char *S)
{
	cout << S;
	char kt;
	do
	{
		kt = toupper(getch());
	} while (kt != 'Y' && kt != 'N');
	cout << kt;
	return kt == 'Y';
}

void Insert_Order(PTR &First, Sinhvien x)
{
	PTR p, t, s; // t la nut truoc, s la nut sau
	p = new node;
	p->sv = x;
	for (s = First; s != NULL && s->sv.maso < x.maso; t = s, s = s->next)
		;
	if (s == First) // them nut vao dau danh sach lien ket
	{
		p->next = First;
		First = p;
	}
	else // them nut p vao truoc nut s
	{
		p->next = s;
		t->next = p;
	}
}

int Delete_after(PTR p)
{
	PTR q;

	if ((p == NULL) || (p->next == NULL))
		return 0;
	q = p->next; // q chi nut can xoa
	p->next = q->next;
	delete q;
	return 1;
}

void SapXepTheoMaso(PTR &First)
{
	if (First == NULL || First->next == NULL)
		return;

	for (PTR p = First; p->next != NULL; p = p->next)
	{
		for (PTR q = p->next; q != NULL; q = q->next)
		{
			if (p->sv.maso > q->sv.maso)
			{
				Sinhvien temp = p->sv;
				p->sv = q->sv;
				q->sv = temp;
			}
		}
	}
}

void XepHangTheoDTB(PTR &First)
{
	if (First == NULL)
		return;
	PTR tmp;
	for (PTR p = First; p != NULL; p = p->next)
	{
		int rank = 1;
		for (PTR q = First; q != NULL; q = q->next)
		{
			if (p->sv.dtb < q->sv.dtb)
				rank++;
		}
		p->sv.hang = rank;
	}
}

int XoaSV(PTR &First, int maso)
{
	if (First == NULL)
		return 0;

	if (First->sv.maso == maso)
	{
		Delete_First(First);
		return 1;
	}

	for (PTR p = First; p->next != NULL; p = p->next)
	{
		if (p->next->sv.maso == maso)
		{
			Delete_after(p);
			return 1;
		}
	}
	return 0;
}

void reverseLinkedList(PTR &First)
{
	PTR prev = NULL, current = First, next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	First = prev;
}

void Copy_linked_list2(PTR First, PTR &First2)
{
	if (First == NULL)
		return;

	First2 = new node;
	First2->sv = First->sv;
	First2->next = NULL;

	PTR p = First2;
	for (PTR q = First->next; q != NULL; q = q->next)
	{
		p->next = new node;
		p = p->next;
		p->sv = q->sv;
		p->next = NULL;
	}
}

int XoaSinhVienTheoTen(PTR &First, char *ten)
{
	int count = 0;
	PTR p = First, prev = NULL;

	while (p != NULL)
	{
		if (stricmp(p->sv.ten, ten) == 0)
		{
			if (prev == NULL)
			{
				First = p->next;
				delete p;
				p = First;
			}
			else
			{
				prev->next = p->next;
				delete p;
				p = prev->next;
			}
			count++;
		}
		else
		{
			prev = p;
			p = p->next;
		}
	}
	return count;
}

PTRname SearchName(PTR First, char *ten)

{
	PTRname pName = new listName;
	pName->soluong = 0;
	for (auto *p = First; p != NULL; p = p->next)
		if (stricmp(p->sv.ten, ten) == 0)
		{
			pName->dsSV[pName->soluong++] = p;
		}
	return pName;
}

void ThemSVTheoViTri(PTR &First, int i)
{
	if (i < 1)
	{
		NhapSV_VeDau(First);
		return;
	}

	PTR p = First;
	for (int j = 1; j < i - 1 && p != NULL; j++)
	{
		p = p->next;
	}

	if (p == NULL)
		Nhap_DSSV(First);
}

void Fillter(PTR const First)
{
	system("cls");
	cout << "Ten SV muon loc :";
	fflush(stdin);
	char tensv[16];
	gets(tensv);
	cout << "Danh sach sinh vien co ten " << tensv << " la :\n";
	PTRname pName = SearchName(First, tensv);
	if (pName->soluong == 0)
		cout << "Khong co sinh vien nao co ten " << tensv << endl;
	else
	{
		cout << "MaSV\tHo\tTen\t\tDTB\tHang\n";
		for (int j = 0; j < pName->soluong; j++)
		{
			cout << pName->dsSV[j]->sv.maso << "\t" << pName->dsSV[j]->sv.ho << "\t" << pName->dsSV[j]->sv.ten << "\t\t" << pName->dsSV[j]->sv.dtb << "\t" << pName->dsSV[j]->sv.hang << endl;
		}
	}
}

void themSV_cothuTu(PTR &First, Sinhvien sv)
{
	SapXepTheoMaso(First); // sap xep danh sach sinh vien theo ma so tang dan
	// them sinh vien theo thu tu ma so tang dan
	PTR p = new node;
	p->sv = sv;
	p->next = NULL;
	if (First == NULL)
		First = p;
	else
	{
		PTR q = First;
		while (q->next != NULL && q->next->sv.maso < sv.maso)
			q = q->next;
		p->next = q->next;
		q->next = p;
	}
}

int main()
{
	char filename[80] = ".//DSSV_DTB.TXT";
	int x;
	char tensv[16];
	int chon;
	PTR First = NULL;
	int so;
	PTR First1 = NULL, First2 = NULL;

	int i;
	Sinhvien sv;
	int maso;

	cout << "Chuong trinh quan ly danh sach sinh vien\n";
	cout << "----------------------------------------\n";
	OpenFile(First, filename);
	cout << "Da mo file DSSV_DTB.TXT de doc du lieu\n";
	Sleep(2000);
	system("cls");

	do
	{
		chon = Menu(thucdon);
		switch (chon)
		{
		case 1:
			Nhap_DSSV(First);
			break;
		case 2:
			LietKe(First);
			break;
		case 3:
			printf("So luong sinh vien =%d", Reccount(First));
			getch();
			break;
		case 4:
			system("cls");
			cout << "Vi tri can them :";
			cin >> i;

			ThemSVTheoViTri(First, i);
			cout << "Da them sinh vien" << endl;
			Sleep(3000);
			break;

		case 5:
			cout << "Ma so SV muon xoa :";
			cin >> maso;

			if (XoaSV(First, maso) == 1)
				BaoLoi("Da xoa sinh vien co ma so trong DSSV.");
			else
				BaoLoi("Ma so SV khong co.");
			break;
		case 6:
			system("cls");
			NhapSV(First, sv);
			cout << "Da nhap sinh vien co ma so " << sv.maso << endl;
			themSV_cothuTu(First, sv);
			Sleep(3000);
			break;

		case 7:
			Fillter(First);
			getch();
			break;
		case 8:
			system("cls");
			cout << "Sap xep danh sach sinh vien theo ma so tang dan.\n";
			SapXepTheoMaso(First);
			cout << "Danh sach da duoc sap xep.\n";
			getch();
			break;

		case 9:
			system("cls");
			if (SaveFile(First, filename) == 0)
				cout << "Loi mo file de ghi ";
			else
				cout << "Da ghi xong danh sach sinh vien vao file.";
			Sleep(2000);
			break;

		case 10:
			system("cls");
			if (OpenFile(First, filename) == 0)
				cout << "Loi mo file de doc ";
			else
				cout << "Da doc xong danh sach sinh vien tu file.";
			Sleep(2000);
			break;
		case 11:
			XepHangTheoDTB(First);
			break;
		case 12:
			system("cls");
			cout << "Ten SV muon xoa :";
			fflush(stdin);
			gets(tensv);
			cout << "So SV da xoa =" << XoaSinhVienTheoTen(First, tensv);
			getch();
			break;
		case 13:
			reverseLinkedList(First);
			cout << "Da dao nguoc danh sach xong";
			getch();
			break;

		case 14:
			Copy_linked_list2(First, First2);
			cout << "DSSV ban dau ";
			LietKe(First);
			cout << endl
				 << "DSSV ban copy ";
			LietKe(First2);
			getch();
			break;
		case 15:
			system("cls");

			if (XacNhan("Ban co muon thoat chuong trinh khong ? (Y/N) :"))
			{
				cout << "\nCam on ban da su dung chuong trinh.\n";
				cout << "Hen gap lai ban sau.\n";
				SaveFile(First, filename);
				Sleep(2000);
				return 0;
			}
			else
			{
				cout << "Ban chua thoat chuong trinh.\n";
				Sleep(2000);
				system("cls");
			}
			break;
			return 0;
		}
	} while (1);

	return 0;
}
