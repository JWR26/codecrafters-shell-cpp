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
        {"type", TOKEN_TYPE::WORD},
    };

    struct Token{
        TOKEN_TYPE token_type;
        std::string str;

        Token() {}

        Token(const TOKEN_TYPE& t, const std::string& s) : token_type(t), str(s) {}

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

        while(it != input.end()){
            std::string::const_iterator start = it;
            if (*it == ' '){
                ++it;
                continue;
            }
            while (*(it + 1) != ' ' && *(it + 1) != '\0'){
                ++it;
            }
            
            std::string word{start, it+1};

            std::unordered_map<std::string, TOKEN_TYPE>::const_iterator res = RESERVED_WORDS.find(word);

            if (res != RESERVED_WORDS.end()){
                tokens.emplace_back(Token(res->second, word));
            }
            else{
                tokens.emplace_back(Token(TOKEN_TYPE::WORD, word));
            }
            ++it;
        }

        return tokens;
    }
}


#endif