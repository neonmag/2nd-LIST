#include <iostream>
using namespace std;


template <class T>
struct Elem
{
    T data; // ������
    Elem* next, * prev;
};

template <class T>
class List
{
    // ������, �����
    Elem<T>* Head, * Tail;
    // ���������� ���������
    int Count;
public:
    // �����������
    List();
    // ����������� �����������
    List(const List&);
    // ����������
    ~List();

    // �������� ����������
    T GetCount();
    // �������� ������� ������
    Elem<T>* GetElem(int);

    // ������� ���� ������
    void DelAll();
    // �������� ��������, ���� �������� �� �����������,
    // �� ������� ��� �����������
    void Del(int pos = 0);
    // ������� ��������, ���� �������� �� �����������,
    // �� ������� ��� �����������
    void Insert(int pos = 0);

    // ���������� � ����� ������
    void AddTail(T n);

    // ���������� � ������ ������
    void AddHead(T n);

    // ������ ������
    void Print();
    // ������ ������������� ��������
    void Print(int pos);

    List& operator = (const List&);
    // �������� ���� ������� (�����������)
    List operator + (const List&);

    // ��������� �� ���������
    bool operator == (const List&);
    bool operator != (const List&);
    bool operator <= (const List&);
    bool operator >= (const List&);
    bool operator < (const List&);
    bool operator > (const List&);

    // ��������������� ������
    List operator - ();
};

template <class T>
List<T>::List()
{
    // ���������� ������ ����
    Head = Tail = NULL;
    Count = 0;
}

template <class T>
List<T>::List(const List<T>& L)
{
    Head = Tail = NULL;
    Count = 0;

    // ������ ������, �� �������� ��������
    Elem<T>* temp = L.Head;
    // ���� �� ����� ������
    while (temp != 0)
    {
        // ���������� ������
        AddTail(temp->data);
        temp = temp->next;
    }
}

template <class T>
List<T>::~List()
{
    // ������� ��� ��������
    DelAll();
}

template <class T>
void List<T>::AddHead(T n)
{
    // ����� �������
    Elem<T>* temp = new Elem<T>;
    // ����������� ���
    temp->prev = 0;
    // ��������� ������
    temp->data = n;
    // ��������� - ������ ������
    temp->next = Head;

    // ���� �������� ����?
    if (Head != 0)
        Head->prev = temp;
    // ���� ������� ������, �� �� ������������ � ������ � �����
    if (Count == 0)
        Head = Tail = temp;
    else
        // ����� ����� ������� - ��������
        Head = temp;
    Count++;
}

template <class T>
void List<T>::AddTail(T n)
{
    // ������� ����� �������
    Elem<T>* temp = new Elem<T>;
    // ���������� ���
    temp->next = 0;
    // ��������� ������
    temp->data = n;
    // ���������� - ������ �����
    temp->prev = Tail;

    // ���� �������� ����?
    if (Tail != 0)
        Tail->next = temp;
    // ���� ������� ������, �� �� ������������ � ������ � �����
    if (Count == 0)
        Head = Tail = temp;
    else
        // ����� ����� ������� - ���������
        Tail = temp;
    Count++;
}

template <class T>
void List<T>::Insert(int pos)
{
    // ���� �������� ����������� ��� ����� 0, �� ����������� ���
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count + 1)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    // ���� ������� � ����� ������
    if (pos == Count + 1)
    {
        // ����������� ������
        int data;
        cout << "Input new number: ";
        cin >> data;
        // ���������� � ����� ������
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {
        // ����������� ������
        int data;
        cout << "Input new number: ";
        cin >> data;
        // ���������� � ������ ������
        AddHead(data);
        return;
    }

    // �������
    int i = 1;

    // ����������� �� ������ n - 1 ���������
    Elem<T>* Ins = Head;

    while (i < pos)
    {
        // ������� �� ��������, 
        // ����� ������� �����������
        Ins = Ins->next;
        i++;
    }
    // ������� �� ��������, 
    // ������� ������������
    Elem<T>* PrevIns = Ins->prev;

    // ������� ����� �������
    Elem<T>* temp = new Elem<T>;

    // ������ ������
    cout << "Input new number: ";
    cin >> temp->data;

    // ��������� ������
    if (PrevIns != 0 && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}

template <class T>
void List<T>::Del(int pos)
{
    // ���� �������� ����������� ��� ����� 0, �� ����������� ���
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    // �������
    int i = 1;

    Elem<T>* Del = Head;

    while (i < pos)
    {
        // ������� �� ��������, 
        // ������� ���������
        Del = Del->next;
        i++;
    }

    // ������� �� ��������, 
    // ������� ������������ ����������
    Elem<T>* PrevDel = Del->prev;
    // ������� �� ��������, ������� ������� �� ���������
    Elem<T>* AfterDel = Del->next;
    // ���� ������� �� ������
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // ���� ������� �� �����
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;
    // ��������� �������?
    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;
    // �������� ��������
    delete Del;

    Count--;
}

template <class T>
void List<T>::Print(int pos)
{
    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem<T>* temp;

    // ���������� � ����� ������� 
    // ������� ���������
    if (pos <= Count / 2)
    {
        // ������ � ������
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            // ��������� �� ������� ��������
            temp = temp->next;
            i++;
        }
    }
    else
    {
        // ������ � ������
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            // ��������� �� ������� ��������
            temp = temp->prev;
            i++;
        }
    }
    // ����� ��������
    cout << pos << " element: ";
    cout << temp->data << endl;
}

template <class T>
void List<T>::Print()
{
    // ���� � ������ ������������ ��������, �� ��������� �� ����
    // � �������� ��������, ������� � ���������
    if (Count != 0)
    {
        Elem<T>* temp = Head;
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}

template <class T>
void List<T>::DelAll()
{
    // ���� �������� ��������, ������� �� ������ � ������
    while (Count != 0)
        Del(1);
}

template <class T>
T List<T>::GetCount()
{
    return Count;
}

template <class T>
Elem<T>* List<T>::GetElem(int pos)
{
    Elem<T>* temp = Head;

    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return 0;
    }

    int i = 1;
    // ���� ������ ��� �������
    while (i < pos && temp != 0)
    {
        temp = temp->next;
        i++;
    }

    if (temp == 0)
        return 0;
    else
        return temp;
}

template <class T>
List<T>& List<T>::operator = (const List<T>& L)
{
    // �������� ������������ �������� "������ ����"
    if (this == &L)
        return *this;

    // �������� ������� ������
    this->~List(); // DelAll();

    Elem<T>* temp = L.Head;

    // �������� ��������
    while (temp != 0)
    {
        AddTail(temp->data);
        temp = temp->next;
    }

    return *this;
}
// �������� ���� �������
template <class T>
List<T> List<T>::operator + (const List<T>& L)
{
    // ������� �� ��������� ������ �������� ������� ������
    List Result(*this);
    // List Result = *this;

    Elem<T>* temp = L.Head;

    // ��������� �� ��������� ������ �������� ������� ������
    while (temp != 0)
    {
        Result.AddTail(temp->data);
        temp = temp->next;
    }

    return Result;
}

template <class T>
bool List<T>::operator == (const List<T>& L)
{
    // ��������� �� ����������
    if (Count != L.Count)
        return false;

    Elem* t1, * t2;

    t1 = Head;
    t2 = L.Head;

    // ��������� �� ����������
    while (t1 != 0)
    {
        // ������� ������, �������
        // ��������� �� ���������� ��������
        if (t1->data != t2->data)
            return false;

        t1 = t1->next;
        t2 = t2->next;
    }
    return true;
}

template <class T>
bool List<T>::operator != (const List<T>& L)
{
    // ���������� ���������� ������� ���������
    return !(*this == L);
}

template <class T>
bool List<T>::operator >= (const List<T>& L)
{
    // ��������� �� ����������
    if (Count > L.Count)
        return true;
    // ��������� �� ����������
    if (*this == L)
        return true;

    return false;
}

template <class T>
bool List<T>::operator <= (const List<T>& L)
{
    // ��������� �� ����������
    if (Count < L.Count)
        return true;
    // ��������� �� ����������
    if (*this == L)
        return true;

    return false;
}

template <class T>
bool List<T>::operator > (const List<T>& L)
{
    if (Count > L.Count)
        return true;

    return false;
}

template <class T>
bool List<T>::operator < (const List<T>& L)
{
    if (Count < L.Count)
        return true;

    return false;
}

// ���������
template <class T>
List<T> List<T>::operator - ()
{
    List Result;

    Elem<T>* temp = Head;
    // �������� �������� ������, ������� � ���������,
    // � ���� ����� ���������� ��������� � ������,
    // ����� ������� ��������� ������ Result ����� ���������
    // �������� � �������� �������
    while (temp != 0)
    {
        Result.AddHead(temp->data);
        temp = temp->next;
    }

    return Result;
}

/////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Queue
{
    // �������
    List<T> Wait;
    // ������������ ������ �������
    T MaxQueueLength;
    // ������� ������ �������
    T QueueLength;

public:
    // �����������
    Queue(T m);

    //����������
    ~Queue();

    // ���������� ��������
    void Add(T c);

    // ���������� ��������
    Elem<T>* Extract();

    // ������� �������
    void Clear();

    // �������� ������������� ��������� � �������
    bool IsEmpty();

    // �������� �� ������������ �������
    bool IsFull();

    // ���������� ��������� � �������
    int GetCount();

    //������������ �������
    void Show();

    void ShowFirst();
};

template <class T>
void Queue<T>::Show() {
    cout << "\n-------------------------------------\n";
    //������������ �������
    Wait.Print();
    cout << "\n-------------------------------------\n";
}
template<class T>
void Queue<T>::ShowFirst()
{
    Wait.Print(1);
}
template <class T>
Queue<T>::~Queue()
{
    //�������� �������
}

template <class T>
Queue<T>::Queue(T m)
{
    //�������� ������
    MaxQueueLength = m;
    //������� �������
    // ���������� ������� �����
    QueueLength = 0;
}

template <class T>
void Queue<T>::Clear()
{
    // ����������� "�������" ������� 
    QueueLength = 0;
}

template <class T>
bool Queue<T>::IsEmpty()
{
    // ����?
    return QueueLength == 0;
}

template <class T>
bool Queue<T>::IsFull()
{
    // �����?
    return QueueLength == MaxQueueLength;
}

template <class T>
int Queue<T>::GetCount()
{
    // ���������� �������������� � ����� ���������
    return QueueLength;
}

template <class T>
void Queue<T>::Add(T c)
{
    // ���� � ������� ���� ��������� �����, �� ����������� ����������
    // �������� � ��������� ����� �������
    if (!IsFull())
    {
        Wait.AddTail(c);
        QueueLength++;
    }
}

template <class T>
Elem<T>* Queue<T>::Extract()
{
    // ���� � ������� ���� ��������, �� ���������� ���, 
    // ������� ����� ������ � �������� �������	
    if (!IsEmpty())
    {
        //��������� ������
        //�������� ��� ��������
        Wait.Del(1);
        QueueLength--;
        return Wait.GetElem(1);
    }

    else // ���� � ����� ��������� ���
        return Wait.GetElem(0);
}

// �������� ������
void main()
{
    Queue<int> QU(10);
    for (int i = 0; i < 10; i++)
    {
        QU.Add(i);
    }
    QU.Show();
    cout << endl;
    QU.ShowFirst();
    cout << endl;
    for (int i = 0; i < 10; i++)
    {
        QU.Extract();
        cout << endl;
        QU.ShowFirst();
        cout << endl;
        QU.Show();
    }
}

