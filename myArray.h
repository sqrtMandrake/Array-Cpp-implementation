#pragma once
#include <iostream>

class MyArray {
    private:
        int m_size;
        int m_length;
        int* m_elements;
    public:
        MyArray(int size = 3);
        MyArray(const MyArray& other);
        ~MyArray();
        bool add(int element);
        bool remove(int index);
        int get(int index) const;
        int size() const;
        bool isEmpty() const;
        bool clear();
        int indexOf(int element) const;
        void resize(int newCapatity);

        MyArray& operator=(const MyArray& other);
        MyArray& operator+=(const MyArray& other);
        MyArray operator+(const MyArray& other) const;
        MyArray& operator-=(const MyArray& other);
        MyArray operator-(const MyArray& other) const;
        bool operator==(const MyArray& other) const;
        bool operator!=(const MyArray& other) const;
    friend std::ostream& operator<<(std::ostream& os, const MyArray& myArray);
    };