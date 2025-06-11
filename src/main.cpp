#include <iostream>
#include <string>
#include <vector>

#include "tokenizer.h"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true){
    std::cout << "$ ";
  
    std::string input;
    std::getline(std::cin, input);

    std::vector<cppshell::Token> tokens = cppshell::tokenize(input);

    if (tokens.empty()){
      continue;
    }

    switch (tokens.front().token_type)
    {
    case cppshell::TOKEN_TYPE::EXIT:
      return 0;
    case cppshell::TOKEN_TYPE::ECHO:
      {
        std::string output;
        for(auto it = tokens.begin() + 1; it != tokens.end(); ++it){
          output += it->str;
          output += ' ';
        }
        std::cout << output << '\n';
      }
      break;
    default:
      std::cout << tokens.front().str << ": command not found\n";
      break;
    }

    
  }

  return 0;
}
