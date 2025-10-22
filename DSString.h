#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cctype>    // For tolower
#include <stdexcept> // For out_of_range

using namespace std;

class DSString
{
private:
    char *data; // Pointer to character data
    size_t len; // Length of the string

public:
    DSString();                            // Default constructor
    DSString(const char *);                // Constructor with C-string parameter
    DSString(const DSString &);            // Copy constructor
    ~DSString();                           // Destructor
    DSString &operator=(const DSString &); // Assignment operator

    size_t length() const;  // Returns the length of the string
    int find(char c) const; // Searches for the first occurrence of a character

    char &operator[](size_t) const;             // Subscript operator to access characters
    DSString operator+(const DSString &) const; // Concatenation operator
    DSString &operator+=(char c);               // Append a character to the string

    bool operator==(const DSString &) const; // Equality operator
    bool operator<(const DSString &) const;  // Less than operator

    DSString substring(size_t start, size_t numChars) const; // Extracts a substring
    DSString toLower() const;                                // Converts the string to lowercase

    char *c_str() const; // Returns a pointer to the C-string representation

    friend ostream &operator<<(ostream &, const DSString &); // Output operator
};

#endif
