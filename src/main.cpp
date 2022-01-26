//
//  main.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#include <iostream>
#include <fstream>
#include "Block1Scanner.hpp"
#include "Block1Parser.hpp"
// #include "PALParser.hpp"

const char *program = NULL;

[[noreturn]]
void exit_error(const std::string& error) {
    std::cerr << "fatal error: " << error << "\n";
    std::exit(EXIT_FAILURE);
}

[[noreturn]]
void exit_usage(const std::string& error) {
    std::cerr << "fatal error: " << error << "\n";
    std::cerr << "usage: " << program << " IN_FILE\n";
    std::exit(EXIT_FAILURE);
}

int main(int argc, const char * argv[]) {
    program = argv[0];
    
    if(argc != 2) {
        exit_usage("wrong parameters");
    }

    std::string path{argv[1]};
    std::ifstream source{path};
    if(!source.is_open()) {
        exit_error("cannot open '" + path + "' for reading");
    }
    
    Block1Scanner scanner(source);
    Block1Parser parser(scanner);
    
    // try {
    //     parser.compile();
    // } catch(Error& err) {
    //     std::cout << err << "\n";
    //     return EXIT_FAILURE;
    // }
    
    bool success = parser.compile();
    
    for(const auto& error: parser.errors()) {
        std::cout << error << "\n";
    }
    
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
    
    // while(true) {
    //     auto token = scanner.lex();
    //     if(token.is(Token::EndOfFile)) break;
    //
    //     std::cout << "{" << token.type() << "} " << token.text() << "\n";
    // }
}
