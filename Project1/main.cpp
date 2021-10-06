#include <iostream>
using namespace std;


template <class T>
struct Elem
{
    T data; // данные
    Elem* next, * prev;
};

template <class T>
class List
{
    // Голова, хвост
    Elem<T>* Head, * Tail;
    // Количество элементов
    int Count;
public:
    // Конструктор
    List();
    // Конструктор копирования
    List(const List&);
    // Деструктор
    ~List();

    // Получить количество
    T GetCount();
    // Получить элемент списка
    Elem<T>* GetElem(int);

    // Удалить весь список
    void DelAll();
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    void Del(int pos = 0);
    // Вставка элемента, если параметр не указывается,
    // то функция его запрашивает
    void Insert(int pos = 0);

    // Добавление в конец списка
    void AddTail(T n);

    // Добавление в начало списка
    void AddHead(T n);

    // Печать списка
    void Print();
    // Печать определенного элемента
    void Print(int pos);

    List& operator = (const List&);
    // сложение двух списков (дописывание)
    List operator + (const List&);

    // сравнение по элементам
    bool operator == (const List&);
    bool operator != (const List&);
    bool operator <= (const List&);
    bool operator >= (const List&);
    bool operator < (const List&);
    bool operator > (const List&);

    // переворачивание списка
    List operator - ();
};

template <class T>
List<T>::List()
{
    // Изначально список пуст
    Head = Tail = NULL;
    Count = 0;
}

template <class T>
List<T>::List(const List<T>& L)
{
    Head = Tail = NULL;
    Count = 0;

    // Голова списка, из которого копируем
    Elem<T>* temp = L.Head;
    // Пока не конец списка
    while (temp != 0)
    {
        // Передираем данные
        AddTail(temp->data);
        temp = temp->next;
    }
}

template <class T>
List<T>::~List()
{
    // Удаляем все элементы
    DelAll();
}

template <class T>
void List<T>::AddHead(T n)
{
    // новый элемент
    Elem<T>* temp = new Elem<T>;
    // Предыдущего нет
    temp->prev = 0;
    // Заполняем данные
    temp->data = n;
    // Следующий - бывшая голова
    temp->next = Head;

    // Если элементы есть?
    if (Head != 0)
        Head->prev = temp;
    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - головной
        Head = temp;
    Count++;
}

template <class T>
void List<T>::AddTail(T n)
{
    // Создаем новый элемент
    Elem<T>* temp = new Elem<T>;
    // Следующего нет
    temp->next = 0;
    // Заполняем данные
    temp->data = n;
    // Предыдущий - бывший хвост
    temp->prev = Tail;

    // Если элементы есть?
    if (Tail != 0)
        Tail->next = temp;
    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - хвостовой
        Tail = temp;
    Count++;
}

template <class T>
void List<T>::Insert(int pos)
{
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count + 1)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Если вставка в конец списка
    if (pos == Count + 1)
    {
        // Вставляемые данные
        int data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в конец списка
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {
        // Вставляемые данные
        int data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в начало списка
        AddHead(data);
        return;
    }

    // Счетчик
    int i = 1;

    // Отсчитываем от головы n - 1 элементов
    Elem<T>* Ins = Head;

    while (i < pos)
    {
        // Доходим до элемента, 
        // перед которым вставляемся
        Ins = Ins->next;
        i++;
    }
    // Доходим до элемента, 
    // который предшествует
    Elem<T>* PrevIns = Ins->prev;

    // Создаем новый элемент
    Elem<T>* temp = new Elem<T>;

    // Вводим данные
    cout << "Input new number: ";
    cin >> temp->data;

    // настройка связей
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
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Счетчик
    int i = 1;

    Elem<T>* Del = Head;

    while (i < pos)
    {
        // Доходим до элемента, 
        // который удаляется
        Del = Del->next;
        i++;
    }

    // Доходим до элемента, 
    // который предшествует удаляемому
    Elem<T>* PrevDel = Del->prev;
    // Доходим до элемента, который следует за удаляемым
    Elem<T>* AfterDel = Del->next;
    // Если удаляем не голову
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // Если удаляем не хвост
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;
    // Удаляются крайние?
    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;
    // Удаление элемента
    delete Del;

    Count--;
}

template <class T>
void List<T>::Print(int pos)
{
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem<T>* temp;

    // Определяем с какой стороны 
    // быстрее двигаться
    if (pos <= Count / 2)
    {
        // Отсчет с головы
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->next;
            i++;
        }
    }
    else
    {
        // Отсчет с хвоста
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->prev;
            i++;
        }
    }
    // Вывод элемента
    cout << pos << " element: ";
    cout << temp->data << endl;
}

template <class T>
void List<T>::Print()
{
    // Если в списке присутствуют элементы, то пробегаем по нему
    // и печатаем элементы, начиная с головного
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
    // Пока остаются элементы, удаляем по одному с головы
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

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return 0;
    }

    int i = 1;
    // Ищем нужный нам элемент
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
    // Проверка присваивания элемента "самому себе"
    if (this == &L)
        return *this;

    // удаление старого списка
    this->~List(); // DelAll();

    Elem<T>* temp = L.Head;

    // Копируем элементы
    while (temp != 0)
    {
        AddTail(temp->data);
        temp = temp->next;
    }

    return *this;
}
// сложение двух списков
template <class T>
List<T> List<T>::operator + (const List<T>& L)
{
    // Заносим во временный список элементы первого списка
    List Result(*this);
    // List Result = *this;

    Elem<T>* temp = L.Head;

    // Добавляем во временный список элементы второго списка
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
    // Сравнение по количеству
    if (Count != L.Count)
        return false;

    Elem* t1, * t2;

    t1 = Head;
    t2 = L.Head;

    // Сравнение по содержанию
    while (t1 != 0)
    {
        // Сверяем данные, которые
        // находятся на одинаковых позициях
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
    // Используем предыдущую функцию сравнения
    return !(*this == L);
}

template <class T>
bool List<T>::operator >= (const List<T>& L)
{
    // Сравнение по количеству
    if (Count > L.Count)
        return true;
    // Сравнение по содержанию
    if (*this == L)
        return true;

    return false;
}

template <class T>
bool List<T>::operator <= (const List<T>& L)
{
    // Сравнение по количеству
    if (Count < L.Count)
        return true;
    // Сравнение по содержанию
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

// переворот
template <class T>
List<T> List<T>::operator - ()
{
    List Result;

    Elem<T>* temp = Head;
    // Копируем элементы списка, начиная с головного,
    // в свой путем добавления элементов в голову,
    // таким образом временный список Result будет содержать
    // элементы в обратном порядке
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
    // Очередь
    List<T> Wait;
    // Максимальный размер очереди
    T MaxQueueLength;
    // Текущий размер очереди
    T QueueLength;

public:
    // Конструктор
    Queue(T m);

    //Деструктор
    ~Queue();

    // Добавление элемента
    void Add(T c);

    // Извлечение элемента
    Elem<T>* Extract();

    // Очистка очереди
    void Clear();

    // Проверка существования элементов в очереди
    bool IsEmpty();

    // Проверка на переполнение очереди
    bool IsFull();

    // Количество элементов в очереди
    int GetCount();

    //демонстрация очереди
    void Show();

    void ShowFirst();
};

template <class T>
void Queue<T>::Show() {
    cout << "\n-------------------------------------\n";
    //демонстрация очереди
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
    //удаление очереди
}

template <class T>
Queue<T>::Queue(T m)
{
    //получаем размер
    MaxQueueLength = m;
    //создаем очередь
    // Изначально очередь пуста
    QueueLength = 0;
}

template <class T>
void Queue<T>::Clear()
{
    // Эффективная "очистка" очереди 
    QueueLength = 0;
}

template <class T>
bool Queue<T>::IsEmpty()
{
    // Пуст?
    return QueueLength == 0;
}

template <class T>
bool Queue<T>::IsFull()
{
    // Полон?
    return QueueLength == MaxQueueLength;
}

template <class T>
int Queue<T>::GetCount()
{
    // Количество присутствующих в стеке элементов
    return QueueLength;
}

template <class T>
void Queue<T>::Add(T c)
{
    // Если в очереди есть свободное место, то увеличиваем количество
    // значений и вставляем новый элемент
    if (!IsFull())
    {
        Wait.AddTail(c);
        QueueLength++;
    }
}

template <class T>
Elem<T>* Queue<T>::Extract()
{
    // Если в очереди есть элементы, то возвращаем тот, 
    // который вошел первым и сдвигаем очередь	
    if (!IsEmpty())
    {
        //запомнить первый
        //сдвинуть все элементы
        Wait.Del(1);
        QueueLength--;
        return Wait.GetElem(1);
    }

    else // Если в стеке элементов нет
        return Wait.GetElem(0);
}

// Тестовый пример
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

