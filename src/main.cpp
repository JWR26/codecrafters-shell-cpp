#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "tokenizer.h"

int main() {
  // get PATH (environment variable and convert to a list of directories)



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
          std::cout << it->str << ' ';
        }
        std::cout << '\n';
      }
      break;
    case cppshell::TOKEN_TYPE::TYPE:
      {
        if (tokens[1].token_type == cppshell::TOKEN_TYPE::WORD){
          std::cout << tokens[1].str << ": not found\n";
        }
        else{
          std::cout << tokens[1].str << " is a shell builtin\n";
        }
      }
      break;
    default:
      std::cout << tokens.front().str << ": command not found\n";
      break;
    }

    
  }

  return 0;
}
