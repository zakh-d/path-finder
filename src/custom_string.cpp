#include <cmath>
#include <utility>
#include <cstring>
#include <cmath>
#include "custom_string.h"

String::String()
:str(new char[1]), size(2){
    str[0] = '\0';
}

String::String(const char* other)
{
    std::size_t length = strlen(other);
    str = new char[length + 1];
    str[length] = '\0';
}

String::String(const String& other)
{
    std::size_t length = other.length();
    str = new char[length + 1];
    strcmp(str, other.str);
    str[length] = '\0';
}

String::String(String&& other)
{
    str =  other.str;
    other.str = nullptr;
}

String& String::operator=(const char* other)
{
    std::size_t length = strlen(other);
    if (length + 1 > size){
        expandToSize(length+1);
    }
    strcpy(str, other);
    str[length] = '\0';
    return *this;
}

String& String::operator=(const String& other)
{
    String tmp(other);
    std::swap(str, tmp.str);
    return *this;
}

String& String::operator=(String&& other)
{
    std::swap(str, other.str);
    return *this;
}

String& String::operator+=(char c)
{
    std::size_t currentLength = length();
    if (currentLength + 2 > size)
    {
        expandToSize(size*2);
    }
    str[currentLength] = c;
    str[currentLength + 1] = '\0';
    return *this;
}

std::size_t String::length() const
{
    return strlen(str);
}

void String::expandToSize(std::size_t newSize)
{
    String tmp(*this);
    std::size_t actualNewSize = (std::size_t) pow(2, ceil(log2(newSize)));
    char* newStr = new char[actualNewSize];
    size = actualNewSize;
    strcpy(newStr, str);
    delete[] str;
    str = newStr;
}

String::~String()
{
    if (str != nullptr)
    {
        delete[] str;
    }
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
    os << string.str;
    return os;
}

std::istream& operator>>(std::istream& is, String& string)
{
    char* buffer = new char[INPUT_BUFFER_SIZE];
    is >> buffer;
    string = buffer;
    delete[] buffer;
    return is;
}

char String::operator[](std::size_t i) const
{
    if (i < size)
    {
        return str[i];
    }
    return '\0';
}

char convert_char(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }

    return c;
}

const int DIGITGROUP = 5;
const int BASE = 'A' - 'Z' + 11; // [A-Z0-9]

unsigned int String::hash() const
{
    unsigned int value = 0;
    int digitPos = 0;
    for (char* curr = str; *curr != '\0'; curr++)
    {
        char c = *curr;
        c = convert_char(c);
        int digit;
        if (c >= 'A' && c <= 'Z')
        {
            digit = c - 'A';
            
        }
        else if (c >= '0' && c <= '9')
        {
            digit = 'Z' - 'A' + c - '0';
        } else continue;
        value += digit * pow(BASE, digitPos);
        digitPos = (digitPos+1) % (DIGITGROUP+1);
    }
    return value;
}

long long String::hash1() const {
    const int p = 31;
    const int m = 1000003;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char* curr = str; *curr != '\0'; curr++) {
        hash_value = (hash_value + (*curr - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}