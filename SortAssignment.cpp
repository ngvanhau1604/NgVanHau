int Delete_info(PTR &First, int x)
{

    PTR p = First;
    Int del_Count = 0;

    if (First == NULL)
        return 0; // empty list
    if (First->info == x)
    {
        Delete_First(First);
        del_Cout++;
    }

    for (p = First; p->next != NULL; p = p->next)
    {
        if (p->next->info == x)
        {
            Delete_After(p);
            del_Count++;
        }
    }
    return del_Count;
}

int Delete_current(PTR &First, PTR p)
{
    PTR q;
    if (p == NULL)
        return 0;
    if (p == First)
    {
        First = First->next;
        delete p;
        return 1;
    }
    for (q = First; q->next != p && q->next != NULL; q = q->next)
        ;
    if (q->next != NULL)
    {
        q->next = p->next;
        delete p;
        return 1;
    }
    return 0;
}

int main()
{
    PTR First = NULL;
    int x;
    cout << "Enter the element to be deleted: ";
    cin >> x;
    int del_Count = Delete_info(First, x);
    cout << "Number of elements deleted: " << del_Count << endl;
    return 0;
}