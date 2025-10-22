#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "DSString.h" // Include the DSString class
#include <vector>

class Tokenizer
{
public:
    Tokenizer();  // Constructor
    ~Tokenizer(); // Destructor

    // Tokenizes a tweet into individual words and returns them as DSString objects in a vector.
    std::vector<DSString> tokenizeTweet(const DSString &tweet);

    // Converts a DSString to lowercase and returns the result.
    DSString toLowercase(const DSString &str) const;

private:
    // Helper function to check if a character is part of a word.
    bool isWordCharacter(char c) const;
};

#endif
