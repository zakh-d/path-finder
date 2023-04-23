#pragma once
#include <iostream>

#define INPUT_BUFFER_SIZE 100

class String {
    char* str;
    std::size_t size;
    void expandToSize(std::size_t newSize);

    friend std::ostream& operator<<(std::ostream& os, const String& string);
    friend std::istream& operator>>(std::istream& is, String& string);

public:
    String();
    String(const char* other);
    String(const String& other);
    String(String&& other);
    String& operator=(const char* other);
    String& operator=(const String& other);
    String& operator=(String&& other);
    String& operator+=(char c);
    char operator[](std::size_t i) const;
    std::size_t length() const;
    unsigned int hash() const;
    long long hash1() const;
    ~String();
};