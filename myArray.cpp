#include "myArray.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>

MyArray::MyArray(int size) : m_size(size), m_length(0) {

    m_elements = new int[size];
}

MyArray::MyArray(const MyArray &other) : m_size(other.m_size), m_length(other.m_length)
{
    m_elements = new int[m_size];
    std::copy(other.m_elements, other.m_elements + other.m_length, m_elements);
}

MyArray::~MyArray()
{
    delete[] m_elements;
}

bool MyArray::add(int element)
{
    if (m_size > m_length) {
        m_elements[m_length] = element;
        m_length++;
        return true;
    }
    resize(m_size * 2);
    m_elements[m_length] = element;
    m_length++;
    return true;

}

bool MyArray::remove(int index)
{
    if (index < 0 || index >= m_length)
    {
        return false;
    }
    for (int i = index; i < m_length - 1; i++)
    {
        m_elements[i] = m_elements[i + 1];
    }
    m_length--;
    return true;
}

int MyArray::get(int index) const
{
    if (index < 0 || index >= m_length) {
        throw std::out_of_range("Index out of bounds");
    }
    return m_elements[index];
}

int MyArray::size() const
{
    return m_length;
}

bool MyArray::isEmpty() const
{
    return m_length == 0;
}

bool MyArray::clear()
{
    m_length = 0;
    return true;
}

int MyArray::indexOf(int element) const
{
    for (int i = 0; i < m_length; i++)
    {
        if (m_elements[i] == element)
        {
            return i;
        }
    }
    return -1;
}

void MyArray::resize(int newCapatity)
{
    if (newCapatity < 0) return;
    int* newElements = new int[newCapatity];
    std::copy(m_elements, m_elements + m_length, newElements);
    delete[] m_elements;
    m_elements = newElements;
    m_size = newCapatity;
}

MyArray& MyArray::operator=(const MyArray& other)
{
    if (*this == other) return *this;
    if (m_length >= other.m_length) {
        memcpy(m_elements, other.m_elements, other.m_length * sizeof(int));
        m_length = other.m_length;
        return *this;
    }
    int* newElements = new int[other.m_length];
    m_elements = newElements;
    m_size = other.m_length;
    memcpy(m_elements, other.m_elements, other.m_length * sizeof(int));
    m_length = other.m_length;
    return *this;
}

MyArray& MyArray::operator+=(const MyArray& other)
{
    if (m_size < m_length + other.m_length)
    {
        resize(m_length + other.m_length);
    }
    std::copy(other.m_elements, other.m_elements + other.m_length, m_elements + m_length);
    m_length += other.m_length;
    return *this;
}

MyArray MyArray::operator+(const MyArray& other) const
{
    MyArray returnArray(m_length + other.m_length);
    std::copy(m_elements, m_elements + m_length, returnArray.m_elements);
    std::copy(other.m_elements, other.m_elements + other.m_length, returnArray.m_elements + m_length);
    returnArray.m_length = m_length + other.m_length;
    return returnArray;
}

MyArray& MyArray::operator-=(const MyArray& other)
{
    for (int i = 0; i < other.m_length; i++) {
        int otherElement = other.m_elements[i];
        int index;
        while ((index = indexOf(otherElement)) != -1)
        {
            remove(index);
        }
    }
    return *this;
}

MyArray MyArray::operator-(const MyArray &other) const
{
    MyArray returnArray = *this;
    for (int i = 0; i < other.m_length; i++) {
        int otherElement = other.m_elements[i];
        int index;
        while ((index = returnArray.indexOf(otherElement)) != -1)
        {
            returnArray.remove(index);
        }
    }
    return returnArray;
}

bool MyArray::operator==(const MyArray& other) const
{
    if (m_length != other.m_length) return false;
    for (int i = 0; i < m_length; i++) 
    {
        if (m_elements[i] != other.m_elements[i]) return false;
    }
    return true;
}

bool MyArray::operator!=(const MyArray& other) const
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const MyArray &myArray)
{
    os << "MyArray {\n";
    for (int i = 0; i < myArray.m_length; i++)
    {
        os << "[" << i << "] -> " << myArray.m_elements[i] << ";\n";
    }
    os << "}";
    return os;
}
