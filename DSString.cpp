#include "DSString.h"

DSString::DSString()
{
    // Default constructor: creates an empty string
    data = new char[1];
    data[0] = '\0';
    len = 0;
}

DSString::DSString(const char *val)
{
    // Constructor with a C-string parameter
    if (val == nullptr)
    {
        // Handle the case of a null pointer by creating an empty string
        data = new char[1];
        data[0] = '\0';
        len = 0;
    }
    else
    {
        // Calculate the length of the input C-string
        len = 0;
        while (val[len] != '\0')
            ++len;

        // Allocate memory for the string and copy the characters
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i)
            data[i] = val[i];
        data[len] = '\0';
    }
}

DSString::DSString(const DSString &other)
{
    // Copy constructor: creates a new string as a copy of another
    len = other.len;
    data = new char[len + 1];
    for (size_t i = 0; i < len; ++i)
        data[i] = other.data[i];
    data[len] = '\0';
}

DSString::~DSString()
{
    // Destructor: releases the memory allocated for the string
    delete[] data;
}

DSString &DSString::operator+=(char c)
{
    // Append a character to the string
    char *newString = new char[len + 2]; // Allocate new memory for the updated string

    // Copy old data
    for (size_t i = 0; i < len; i++)
    {
        newString[i] = data[i];
    }
    newString[len] = c;
    newString[len + 1] = '\0';

    // Replace the old data with the new string
    delete[] data;
    data = newString;
    len++;
    return *this;
}

DSString &DSString::operator=(const DSString &other)
{
    // Assignment operator: copy the contents of another string
    if (this != &other)
    {
        delete[] data; // Release old memory
        len = other.len;
        data = new char[len + 1]; // Allocate new memory
        for (size_t i = 0; i < len; ++i)
            data[i] = other.data[i];
        data[len] = '\0';
    }
    return *this;
}

size_t DSString::length() const
{
    // Returns the length of the string
    return len;
}

int DSString::find(char c) const
{
    // Searches for the first occurrence of a character in the string
    for (size_t i = 0; i < len; ++i)
    {
        if (data[i] == c)
        {
            return static_cast<int>(i);
        }
    }
    return -1; // Character not found
}

char &DSString::operator[](size_t index) const
{
    // Subscript operator to access characters
    if (index >= len)
        throw out_of_range("Index out of range");
    return data[index];
}

DSString DSString::operator+(const DSString &other) const
{
    // Concatenation operator: combines two strings
    DSString result;
    result.len = len + other.len;
    result.data = new char[result.len + 1];

    size_t i = 0;
    for (; i < len; ++i)
        result.data[i] = data[i];
    for (size_t j = 0; j < other.len; ++j, ++i)
        result.data[i] = other.data[j];

    result.data[result.len] = '\0';
    return result;
}

bool DSString::operator==(const DSString &other) const
{
    // Equality operator
    if (len != other.len)
        return false;
    for (size_t i = 0; i < len; ++i)
        if (data[i] != other.data[i])
            return false;
    return true;
}

bool DSString::operator<(const DSString &other) const
{
    // Less than operator
    size_t minLen = len < other.len ? len : other.len;
    for (size_t i = 0; i < minLen; ++i)
    {
        if (data[i] < other.data[i])
            return true;
        if (data[i] > other.data[i])
            return false;
    }
    return len < other.len;
}

DSString DSString::substring(size_t start, size_t numChars) const
{
    // Extracts a substring from the string
    if (start >= len)
        throw out_of_range("Start index out of range");
    if (start + numChars > len)
        numChars = len - start;

    DSString result;
    result.len = numChars;
    result.data = new char[numChars + 1];
    for (size_t i = 0; i < numChars; ++i)
        result.data[i] = data[start + i];
    result.data[numChars] = '\0';

    return result;
}

DSString DSString::toLower() const
{
    // Converts the string to lowercase
    DSString result;
    result.len = len;
    result.data = new char[len + 1];
    for (size_t i = 0; i < len; ++i)
        result.data[i] = tolower(static_cast<unsigned char>(data[i]));
    result.data[len] = '\0';
    return result;
}

char *DSString::c_str() const
{
    // Returns a pointer to the C-string representation
    return data;
}

ostream &operator<<(ostream &os, const DSString &str)
{
    // Output operator: allows printing a DSString using cout
    os << str.data;
    return os;
}
