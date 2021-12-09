//
//  main.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#include <iostream>
#include "CompilerKit/Scanner.hpp"

using namespace AP::CompilerKit;

class PALScanner : public Scanner {
public:
    using Scanner::Scanner;
    
    std::optional<Token> lexNumber() {
        return std::nullopt;
    }
    
    Token lex() override {
        
        return Token();
    }
    
private:
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
