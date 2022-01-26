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
#include "Block1PureParser.hpp"
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
    std::cerr << "usage: " << program << " command <in_file>\n";
    std::exit(EXIT_FAILURE);
}


int count_lets(std::istream& source) {
    std::cout << "counting let statements...\n";
    
    Block1Scanner scanner(source);
    
    int lets = 0;
    
    while(!scanner.end()) {
        Token token = scanner.lex();
        if(token.type() == "let") lets += 1;
    }
    
    std::cout << lets << " assignment (let) statements found.\n";
    std::cout << "done.\n";
    return EXIT_SUCCESS;
}

int pure_parser(std::istream& source) {
    std::cout << "running pure parser...\n";
    
    Block1Scanner scanner(source);
    Block1PureParser parser(scanner);
    
    try {
        parser.compile();
        std::cout << "done.\n";
    } catch(Error& err) {
        std::cout << err << "\n";
        std::cout << "done.\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int parser(std::istream& source) {
    std::cout << "running full parser & semantic analysis...\n";
    
    Block1Scanner scanner(source);
    Block1Parser parser(scanner);
    
    bool success = parser.compile();
    
    for(const auto& error: parser.errors()) {
        std::cout << error << "\n";
    }
    std::cout << "done.\n";
    
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}


int main(int argc, const char * argv[]) {
    program = argv[0];
    
    if(argc != 3) {
        exit_usage("wrong parameters");
    }

    std::string path{argv[2]};
    std::ifstream source{path};
    if(!source.is_open()) {
        exit_error("cannot open '" + path + "' for reading");
    }
    
    std::string cmd{argv[1]};
    if(cmd == "count-let") {
        return count_lets(source);
    } else if(cmd == "parse-pure") {
        return pure_parser(source);
    } else if(cmd == "parse-sema") {
        return parser(source);
    }
    
    std::cerr << "invalid command '" << cmd << "'\n";
    return EXIT_FAILURE;
}
