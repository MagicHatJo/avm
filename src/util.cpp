
#include <regex>
#include <string>

int countMatchInRegex(std::string s, std::string re)
{
    std::regex words_regex(re);
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();

    return std::distance(words_begin, words_end);
}

