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
        std::vector<cppshell::Token>::const_iterator it = ++tokens.begin();
        while(it != tokens.end()){
          std::cout << *it;
          ++it;
          if (it != tokens.end()){
            std::cout << ' ';
          };
        }
      }
      break;
    default:
      std::cout << *it << ": command not found\n";
      break;
    }

    
  }

  return 0;
}
