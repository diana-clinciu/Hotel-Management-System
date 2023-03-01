//
// Created by Diana on 2/25/2023.
//

#ifndef PROIECT_VECTOR_H
#define PROIECT_VECTOR_H

#include "iostream"

using namespace std;

// #clasa template
template<class T>
class Vector {
private:
    T *v;
    int length, capacity;
public:

    void push(T element);

    T pop();

    int getSize() const;

    void clear();

    Vector();

    Vector(T *v, int length, int capacity);

    Vector(const Vector<T> &vect);

    ~Vector();

    Vector<T> &operator=(const Vector<T> &vect);

    T operator[](int index) const;

    template<class U>
    friend istream &operator >>(istream &in, Vector<U> &vect);

    template<class U>
    friend ostream &operator <<(ostream &out,const Vector<U> &vect);

};

template<class T>
void Vector<T>::push(T element) {
    T *temp;
    if (this->length == this->capacity) {
        temp = new T[this->length];
        for (int i = 0; i < this->length; i++)
            temp[i] = this->v[i];

        if (this->v != NULL)
            delete[] this->v;

        this->capacity *= 2;
        this->v = new T[this->capacity];

        for (int i = 0; i < this->length; i++)
            this->v[i] = temp[i];

        delete[] temp;
    }
    this->length++;
    this->v[this->length - 1] = element;
}

template<class T>
T Vector<T>::pop() {
    if (this->length != 0) {
        this->length--;
        return this->v[this->length];
    }
    cout << "Vector gol\n";
    return -1;
}

template<class T>
int Vector<T>::getSize() const {
    return this->length;
}

template<class T>
void Vector<T>::clear() {
    this->length = 0;
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vect) {
    if (this != &vect) {
        this->capacity = vect.capacity;
        this->length = vect.length;

        if (this->v != NULL)
            delete[] this->v;

        this->v = new T[vect.capacity];
        for (int i = 0; i < vect.length; i++)
            this->v[i] = vect.v[i];
    }

    return *this;
}

template<class T>
T Vector<T>::operator[](int index) const {
    if (index < this->length && index >= 0) {
        return this->v[index];
    }

}

template<class T>
istream &operator>>(istream &in, Vector<T> &vect) {
    int n;
    T x;
    cout << "Nr elemente: ";
    in >> n;
    cout << "Elementele:\n";
    for (int i = 0; i < n; i++) {
        in >> x;
        vect.push(x);
    }

    return in;
}

template<class T>
ostream &operator<<(ostream &out, const Vector<T> &vect) {
    for (int i = 0; i < vect.length; i++)
        out << vect.v[i] << endl;

    return out;
}

template<class T>
Vector<T>::Vector() {
    this->capacity = 1;
    this->length = 0;
    this->v = new T[1];
}

template<class T>
Vector<T>::Vector(T *v, int length, int capacity) {
    this->capacity = capacity;
    this->length = length;
    this->v = new T[capacity];
    for (int i = 0; i < length; i++)
        this->v[i] = v[i];
}

template<class T>
Vector<T>::Vector(const Vector<T> &vect) {
    this->capacity = vect.capacity;
    this->length = vect.length;
    this->v = new T[vect.capacity];
    for (int i = 0; i < vect.length; i++)
        this->v[i] = vect.v[i];
}

template<class T>
Vector<T>::~Vector() {
    if (this->v != NULL) {
        delete[] this->v;
    }
}

#endif //PROIECT_VECTOR_H
