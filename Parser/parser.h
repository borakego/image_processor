#pragma once

#include <string>
#include <vector>

namespace parser {
struct Token {
    std::string name;
    std::vector<std::string> args;
    void Clear();
    bool Empty() const;
};

std::vector<Token> Parse(int agrc, char** argv);
}  // namespace parser