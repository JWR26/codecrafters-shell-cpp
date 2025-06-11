#ifndef TOKENIZER
#define TOKENIZER

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace cppshell{
    enum TOKEN_TYPE{
        EXIT,
        ECHO,
        TYPE,
        WORD,
    };

    const std::unordered_map<std::string, TOKEN_TYPE> RESERVED_WORDS{
        {"exit", TOKEN_TYPE::EXIT},
        {"echo", TOKEN_TYPE::ECHO},
        {"type", TOKEN_TYPE::TYPE},
    };

    struct Token{
        TOKEN_TYPE token_type{TOKEN_TYPE::WORD};
        std::string str;

        Token() {}

        Token(const std::string& s) {
            str = s;
            std::unordered_map<std::string, TOKEN_TYPE>::const_iterator res = RESERVED_WORDS.find(str);

            if (res != RESERVED_WORDS.end()){
                token_type = res->second;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Token& t) {
            os << t.str;
        }
    };

    bool is_command(const Token& t) {
        return (t.token_type != TOKEN_TYPE::WORD);
    }

    std::vector<Token> tokenize(const std::string& input){
        std::vector<Token> tokens{};
        tokens.reserve(input.size());

        std::string::const_iterator it = input.begin();

        size_t pos{0};
        size_t last{0};

        std::string token;

        while((pos = input.find(' ', last)) != std::string::npos){
            token = input.substr(last, pos - last);
            last = pos + 1;
            tokens.emplace_back(token);
        }
        
        token = input.substr(last);
        tokens.emplace_back(token);

        return tokens;
    }
}


#endif