#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> tokens;
    std::string::size_type last_pos = 0, pos = 0;

    while ((pos = str.find(delimiter, last_pos)) != std::string::npos)
    {
        tokens.push_back(str.substr(last_pos, pos - last_pos));
        last_pos = pos + delimiter.length();
    }

    tokens.push_back(str.substr(last_pos));

    return tokens;
}

int main()
{
    std::string str = "Hello, world! This is a string.";
    std::vector<std::string> tokens = splitString(str, " ");

    for (const auto &token : tokens)
    {
        std::cout << token << std::endl;
    }

    return 0;
}
