#pragma once
#include <iostream>

#define INPUT_BUFFER_SIZE 100

class String {
    char* str;
    std::size_t size;

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
    bool operator==(const String& other) const;
    char operator[](std::size_t i) const;
    std::size_t length() const;
    long long hash() const;
    long long hash1() const;
    ~String();
};