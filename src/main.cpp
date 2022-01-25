//
//  main.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#include <iostream>
#include <fstream>
#include "PALScanner.hpp"
#include "PALParser.hpp"

[[noreturn]]
void exit_error(const std::string& error) {
    std::cerr << "fatal error: " << error << "\n";
    std::exit(EXIT_FAILURE);
}

[[noreturn]]
void exit_usage(const std::string& error) {
    std::cerr << "fatal error: " << error << "\n";
    std::cerr << "usage: palc IN_FILE\n";
    std::exit(EXIT_FAILURE);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if(argc != 2) {
        exit_usage("wrong parameters");
    }

    std::string path{argv[1]};
    std::ifstream source{path};
    if(!source.is_open()) {
        exit_error("cannot open '" + path + "' for reading");
    }
    
    PALScanner scanner(source);
    PALParser parser(scanner);
    
    bool result = parser.compile();
    
    for(const auto& e: parser.errors()) {
        std::cout << e << "\n";
    }
    return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
