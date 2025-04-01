#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

class TwoFrontStack
{
private:
    int *arr;
    int capacity;
    int front;
    int rear;
    int size;

public:
    TwoFrontStack(int capacity);
    ~TwoFrontStack();
    void pushFront(int value);
    void pushRear(int value);
    int popFront();
    int popRear();
    bool isEmpty();
    bool isFull();
    void display();
};

TwoFrontStack::TwoFrontStack(int capacity)
{
    this->capacity = capacity;
    arr = new int[capacity];
    front = -1;
    rear = 0;
    size = 0;
}

TwoFrontStack::~TwoFrontStack()
{
    delete[] arr;
}

bool TwoFrontStack::isEmpty()
{
    return size == 0;
}

bool TwoFrontStack::isFull()
{
    return size == capacity;
}

void TwoFrontStack::pushFront(int value)
{
    if (isFull())
    {
        cout << "Stack is full. Cannot push " << value << " to the front." << endl;
        return;
    }
    if (front == -1)
    { 
        front = 0;
        rear = 0;
    }
    else if (front == 0)
    {
        front = capacity - 1;
    }
    else
    {
        front = front - 1;
    }
    arr[front] = value;
    size++;
}

void TwoFrontStack::pushRear(int value)
{
    if (isFull())
    {
        cout << "Stack is full. Cannot push " << value << " to the rear." << endl;
        return;
    }
    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else if (rear == capacity - 1)
    {
        rear = 0;
    }
    else
    {
        rear = rear + 1;
    }
    arr[rear] = value;
    size++;
}

int TwoFrontStack::popFront()
{
    if (isEmpty())
    {
        cout << "Stack is empty. Cannot pop from the front." << endl;
        return -1;
    }
    int value = arr[front];
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else if (front == capacity - 1)
    {
        front = 0;
    }
    else
    {
        front = front + 1;
    }
    size--;
    return value;
}

int TwoFrontStack::popRear()
{
    if (isEmpty())
    {
        cout << "Stack is empty. Cannot pop from the rear." << endl;
        return -1;
    }
    int value = arr[rear];
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else if (rear == 0)
    {
        rear = capacity - 1;
    }
    else
    {
        rear = rear - 1;
    }
    size--;
    return value;
}

void gotoxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void clrscr()
{
    system("cls");
}

void drawBox(int x, int y, int value)
{
    gotoxy(x, y);
    cout << "+---+";
    gotoxy(x, y + 1);
    cout << "| " << value << " |";
    gotoxy(x, y + 2);
    cout << "+---+";
}

void drawBoundary(int x, int y, int height)
{
    for (int i = 0; i < height; ++i)
    {
        gotoxy(x, y + i);
        cout << "|";
    }
}

void TwoFrontStack::display()
{
    clrscr();
    if (isEmpty())
    {
        cout << "Stack is empty." << endl;
        return;
    }
    int i = front;
    int pos = 0;
    while (true)
    {
        drawBox(pos * 6, 0, arr[i]);
        if (i == rear)
        {
            break;
        }
        i = (i + 1) % capacity;
        pos++;
    }
    // drawBoundary((capacity / 2) * 6, 0, 3); // Draw boundary in the middle
    cout << endl;
}

int main()
{
    TwoFrontStack stack(10); // Increased capacity to 10 for better visualization
    char choice;
    int value;

    while (true)
    {
        clrscr();
        stack.display();
        cout << "\nOptions:\n";
        cout << "1. Push Front\n";
        cout << "2. Push Rear\n";
        cout << "3. Pop Front\n";
        cout << "4. Pop Rear\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        choice = _getch();

        switch (choice)
        {
        case '1':
            cout << "\nEnter value to push to front: ";
            cin >> value;
            stack.pushFront(value);
            break;
        case '2':
            cout << "\nEnter value to push to rear: ";
            cin >> value;
            stack.pushRear(value);
            break;
        case '3':
            value = stack.popFront();
            if (value != -1)
            {
                cout << "\nPopped from front: " << value << endl;
            }
            Sleep(1000);
            break;
        case '4':
            value = stack.popRear();
            if (value != -1)
            {
                cout << "\nPopped from rear: " << value << endl;
            }
            Sleep(1000);
            break;
        case '5':
            return 0;
        default:
            cout << "\nInvalid choice. Please try again." << endl;
            Sleep(1000);
        }
    }

    return 0;
}