#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <stdlib.h>
#include <exceptions.h>
using namespace std;

template <typename T>
class Iterator;

template <typename T>
struct Node {
    T data;
    Node *next;
};

template <typename T>
class List {
    friend class Iterator<T>;
private:
    Node<T> *head; //указатель на начало списка
    int size; //размер списка

public: //конструкторы и деструктор
    List(); //конструктор по умолчанию
    List(const List<T>& lst); //конструктор копирования
    List(List<T>&& list); //конструктор перемещения
    explicit List(std::initializer_list<T> lst); //явный конструктор со списком инициализации
    ~List(); //деструктор

public: //перегрузки операторов
    List<T>& operator=(const List<T>& lst); //перегрузка оператора =
    T& operator[](int index); //доступ к элементу аналогично массиву

public: //операции со списками (из условия лабы)
    int get_length() const; //вычисление длины списка
    void add(const T& elem); //добавление элемента в конец списка
    void add_range(const List<T>& lst); //добавление списка lst в конец списка
    void add_range(T* arr, int arr_size);
    void set_elem(int index, const T& elem); //изменить элемент списка по индексу
    T& get_elem(int index); //получить элемент списка по индексу
    void remove_elem(int index); //удалить элемент списка по индексу
    T* to_array(); //преобразование списка в массив
    List<T> combine(const List<T>& lst); //объединение списка с другим списком
    void sort(int (*comp)(const T& r1, const T& r2)); //сортировка списка через переданный компаратор
    int get_index(T& elem) const; //возвращает индекс существующего элемента; если элемента нет, вернёт -1

public: //дополнительно реализованные методы (на доп. балл)
    void push_front(const T& elem); //добавление элемента в начало списка
    template <typename _T>
    friend std::ostream& operator<<(std::ostream& os, const List<_T>& lst); //вывод элементов списка
    bool operator==(const List<T>& lst); //перегрузка оператора ==
    void pop_front(); //удаляет первый элемент
    void reverse(); //переворачивает список
    Iterator<T> insert_after(const Iterator<T>& pos, const int count, const T& elem); //вставляет после позиции pos count элементов elem
};




template <typename T>
List<T>::List() {
    head = nullptr;
    size = 0;
}

template <typename T>
List<T>::List(const List<T>& lst) : head(nullptr), size(0) {
    *this = lst;
}

template <typename T>
List<T>::List(List<T>&& list) {
    head = list.head;
    size = list.size;
    list.head = nullptr;
    list.size = 0;
}

template <typename T>
List<T>::List(std::initializer_list<T> lst) : head(nullptr), size(0) {
    for (const auto& item : lst) {
        add(item);
    }
}

template <typename T>
List<T>::~List() {
    while (head != nullptr) {
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& lst) {
    if (this == &lst) {
        return *this;
    }
    while (head != nullptr) {
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
    }
    if (lst.head != nullptr) {
        head = new Node<T>;
        head->data = lst.head->data;
        head->next = nullptr;
        Node<T> *curr = head;
        Node<T> *other_curr = lst.head->next;
        while (other_curr) {
            curr->next = new Node<T>;
            curr->next->data = other_curr->data;
            curr->next->next = nullptr;
            curr = curr->next;
            other_curr = other_curr->next;
        }
    }
    size = lst.size;
    return *this;
}

template <typename T>
bool List<T>::operator==(const List<T>& lst) {
//    Node<T> *old_list = head;
//    Node<T> *new_list = lst.head;
//    bool result = true;
//    if (size == lst.size) {
//        while (old_list != nullptr) {
//            if (old_list->data != new_list->data) {
//                result = false;
//                break;
//            }
//            else {
//                old_list = old_list->next;
//                new_list = new_list->next;
//            }
//        }
//    }
//    else {
//        result = false;
//    }
    Iterator<T> old_list_it(*this);
    Iterator<T> new_list_it(lst);
    bool result = true;
    if (size == lst.size) {
        while (!(old_list_it.is_end())) {
            if (old_list_it.value() != new_list_it.value()) {
                result = false;
                break;
            }
            else {
                ++old_list_it;
                ++new_list_it;
            }
        }
    }
    else {
        result = false;
    }
    return result;
}

template <typename T>
int List<T>::get_length() const {
    return size;
}

template <typename T>
void List<T>::add(const T& elem) {
    if (head == nullptr) {
        head = new Node<T>;
        head->data = elem;
        head->next = nullptr;
    }
    else {
        Node<T> *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node<T>;
        current = current->next;
        current->data = elem;
        current->next = nullptr;
    }
    size++;
}

template <typename T>
void List<T>::add_range(const List<T>& lst) {
//    Node<T> *new_curr = lst.head;
//    while (new_curr != nullptr) {
//        add(new_curr->data);
//        new_curr = new_curr->next;
//    }
    Iterator<T> iter(lst);
    while (!(iter.is_end())) {
        int val = iter.value();
        add(val);
        ++iter;
    }
}


template <typename T>
void List<T>::add_range(T* arr, int arr_size) {
    if (arr_size <= 0) {
        throw Array_exception();
    }
    if (arr == nullptr) {
        std::string error_message = "array memory was not allocated!";
        throw Array_exception(error_message);
    }
    for (int i = 0; i < arr_size; i++) {
        add(arr[i]);
    }
}


template <typename T>
void List<T>::set_elem(int index, const T& elem) {
    if (index < 0 || index >= size) {
        throw Range_exception();
    }
    Iterator<T> iter(*this);
    for (int i = 0; i < index; i++) {
        ++iter;
    }
    *iter = elem;
}

template <typename T>
T& List<T>::get_elem(int index) {
    if (index < 0 || index >= size) {
        throw Range_exception();
    }
    return (*this)[index];
}

template <typename T>
void List<T>::remove_elem(int index) {
    if (index < 0 || index >= size) {
        throw Range_exception();
    }
    if (index == 0){
        Node<T> *ptr = head;
        head = head->next;
        delete ptr;
        size--;
        return;
    }
    else {
        Node<T> *current = head;
        for (int i = 0; i < index - 1 && current != nullptr; i++) {
            current = current->next;
        }
        if (current == nullptr || current->next == nullptr) {
            return;
        }
        Node<T> *tmp = current->next;
        current->next = tmp->next;
        delete tmp;
    }
    size--;
}

template <typename T>
T* List<T>::to_array() {
    T* array = new T[size];
    Iterator<T> iter(*this);
    for (int i = 0; i < size; i++, ++iter) {
        array[i] = iter.value();
    }
    return array;
}


template <typename T>
List<T> List<T>::combine(const List<T>& lst) {
    add_range(lst);
    return *this;
}

template <typename T>
void List<T>::sort(int (*comp)(const T& r1, const T& r2)) {
    if (head == nullptr || head->next == nullptr) {
        std::string error_message = "list contains <= 1 elements.";
        throw List_size_exception(error_message);
    }
    Node<T> *current = head;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        while (current->next != nullptr) {
            if (comp(current->data, current->next->data)) {
                T tmp = current->data;
                current->data = current->next->data;
                current->next->data = tmp;
                swapped = true;
            }
            current = current->next;
        }
        current = head;
    }
}

template <typename T>
int List<T>::get_index(T& elem) const {
    int ind = -1;
    int counter = -1;
//    Node<T> *p = head;
//    while (p != nullptr) {
//        counter++;
//        if (p->data == elem) {
//            ind = counter;
//            break;
//        }
//        p = p->next;
//    }
    Iterator<T> iter(*this);
    while (!(iter.is_end())) {
        counter++;
        T val = iter.value();
        if (val == elem) {
            ind = counter;
            break;
        }
        ++iter;
    }
    return ind;
}

template <typename T>
T& List<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw Range_exception();
    }
//    Node<T> *current = head;
//    for (int i = 0; i <= index; i++) {
//        if (i != index) {
//            current = current->next;
//        }
//        else {
//            return current->data;
//        }
//    }
    Iterator<T> iter(*this);
    for (int i = 0; i < index; i++) {
        ++iter;
    }
    return *iter;
}

template <typename T>
void List<T>::push_front(const T& elem) {
    Node<T>* new_node = new Node<T>;
    new_node->data = elem;
    new_node->next = head;
    head = new_node;
    size++;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& lst) {
    Iterator<T> iter(lst);
    os << "{ ";
    while (!(iter.is_end())) {
        os << *iter << " ";
        ++iter;
    }
    os << "}" <<  std::endl;
    return os;
}

template <typename T>
void List<T>::pop_front() {
    if (head == nullptr) {
        throw List_size_exception();
    }
    remove_elem(0);
}

template <typename T>
void List<T>::reverse() {
    if (head == nullptr) {
        throw List_size_exception();
    }
    Node<T> *prev = nullptr;
    Node<T> *current = head;
    while (current != nullptr) {
        Node<T> *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

template <typename T>
Iterator<T> List<T>::insert_after(const Iterator<T>& pos, const int count, const T& elem) {
    if (count == 0) {
        return pos;
    }
    Node<T>* prev_node = pos.current;
    Node<T>* next_node = prev_node->next;
    for (int i = 0; i < count; i++) {
        Node<T>* new_node = new Node<T>;
        new_node->data = elem;
        prev_node->next = new_node;
        new_node->next = next_node;
        prev_node = new_node;
        size++;
    }

    Iterator<T> result(*this);
    while (result.current != prev_node) {
        ++result;
    }
    return ++result;
}


#endif // LIST_H
