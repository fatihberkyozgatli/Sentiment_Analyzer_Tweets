#include <iostream>
#include <vector>
#include <algorithm>

#include "DSString.h"

int main()
{
    DSString myString = "Hello, World!";
    std::cout << myString << "\n";

    // this uses the one argument constructor in DSString and then the inherited operator=
    myString = "Good bye!";
    std::cout << myString << "\n";

    std::cout << "substr: " << myString.substring(5, 3) << "\n";

    DSString a = "test";
    DSString b = a;

    std::cout << std::boolalpha;
    std::cout << (a == b) << "\n";

    // use initialization list
    std::vector<DSString> strings = {
        DSString("bbb"),
        DSString("aaa"),
        DSString("ddd"),
        DSString("eee"),
        DSString("ccc")};

    // find strings
    for (const auto &s : strings)
        std::cout
            << s << "\n";

    std::cout << "found ddd: " << (std::find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << "\n";
    std::cout << "found zzz: " << (std::find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << "\n";

    // sorting using the STL
    std::sort(strings.begin(), strings.end());

    for (const auto &s : strings)
        std::cout
            << s << "\n";

    // now we can do more efficient search using STL binary search
    std::cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << "\n";
    std::cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << "\n";

    return 0;
}
