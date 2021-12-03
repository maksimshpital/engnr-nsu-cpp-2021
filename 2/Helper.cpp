#include "Helper.h"

std::vector<std::string> Helper::split(std::string line, const std::string& delimiter) {
    std::vector<std::string> result;
    int pos = 0;
    while ((pos = (int)line.find(delimiter)) != (int)std::string::npos) {
        std::string token = line.substr(0, pos);
        result.push_back(Helper::strip(token));
        line.erase(0, pos + delimiter.length());
    }
    result.push_back(Helper::strip(line));
    return result;
}

bool Helper::isDigit(const std::string & value) {
    std::string::const_iterator it = value.begin();
    while (it != value.end() && (std::isdigit(*it) || (*it == '-'))) ++it;
    return !value.empty() && it == value.end();
}

std::string Helper::strip(std::string s) {
    const char* ws = " \t\n\r\f\v";
    s.erase(s.find_last_not_of(ws) + 1);
    s.erase(0, s.find_first_not_of(ws));
    return s;
}
