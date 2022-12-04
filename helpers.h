#pragma once

#include <string>

bool split_string(std::string s, char c, std::string* out1, std::string* out2) {
    if (!s.find(c)) return false;


    std::string h = s.substr(0, s.find(c));
    std::string t = s.substr(s.find(c) + 1, s.length() - 1);

    *out1 = h;
    *out2 = t;

    return true;
}