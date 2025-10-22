#include "Tokenizer.h"
#include "DSString.h"
#include <cctype> // For tolower()

Tokenizer::Tokenizer()
{
    // Constructor
}

Tokenizer::~Tokenizer()
{
    // Destructor
}

std::vector<DSString> Tokenizer::tokenizeTweet(const DSString &tweet)
{
    std::vector<DSString> tokens;
    DSString token;
    char c;

    for (size_t i = 0; i < tweet.length(); i++)
    {
        c = tweet[i];
        if (isWordCharacter(c))
        {
            token += c;
        }
        else
        {
            if (token.length() > 0)
            {
                tokens.push_back(token);
                token = "";
            }
        }
    }
    if (token.length() > 0)
    {
        tokens.push_back(token);
    }
    return tokens;
}

DSString Tokenizer::toLowercase(const DSString &str) const
{
    DSString result;
    for (size_t i = 0; i < str.length(); ++i)
    {
        result += tolower(str[i]);
    }
    return result;
}

bool Tokenizer::isWordCharacter(char c) const
{
    // Helper function to check if a character is part of a word (alphanumeric, apostrophe, or hyphen).
    return isalnum(c) || c == '\'' || c == '-';
}
