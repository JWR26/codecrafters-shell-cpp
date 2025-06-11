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

    if(input == "exit 0"){
      return 0;
    }

    std::vector<cppshell::Token> tokens = cppshell::tokenize(input);


    std::cout << input << ": command not found\n";
  }

  return 0;
}
