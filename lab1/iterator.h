#ifndef ITERATOR_H
#define ITERATOR_H
#include "list.h"


template <typename T>
class Iterator {
    friend class List<T>;
private:
    Node<T> *current;
public:
    Iterator<T>(const List<T>& container_obj); //конструктор
    Iterator<T> next(); //получение следующего элемента контейнера
    T value(); //получить элемент контейнера
    bool is_end(); //установлен ли итератор на конец контейнера
    Iterator<T>& operator++(); //перегрузка оператора ++ (аналог next())
    T& operator*(); //перегрузка оператора * (аналог value())
    bool operator==(Iterator<T> &b); //перегрузка оператора ==
    bool operator!=(Iterator<T> &b); //перегрузка оператора !=
    Iterator<T>& operator=(const Iterator<T>& other); // перегрузка оператора =

};

template <typename T>
Iterator<T>::Iterator(const List<T>& container_obj) {
    if (container_obj.head == nullptr) {
        throw List_size_exception();
    }
    current = container_obj.head;
}

template <typename T>
Iterator<T> Iterator<T>::next() {
    return ++(*this);
}


template <typename T>
T Iterator<T>::value() {
    return **this;
}

template <typename T>
bool Iterator<T>::is_end() {
    return (current == nullptr) ? true : false;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    if (current == nullptr) {
        throw List_size_exception();
    }
    current = current->next;
    return *this;
}

template <typename T>
T& Iterator<T>::operator*() {
    if (current == nullptr) {
        throw List_size_exception();
    }
    return current->data;
}

template <typename T>
bool Iterator<T>::operator==(Iterator<T> &b) {
    return current == b.current;
}

template <typename T>
bool Iterator<T>::operator!=(Iterator<T> &b) {
    return current != b.current;
}

template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& other) {
        if (this != &other) {
           current = other.current;
        }
        return *this;
}
#endif // ITERATOR_H
