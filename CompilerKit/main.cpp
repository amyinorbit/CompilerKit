//
//  main.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#include <iostream>
#include "PALScanner.hpp"
#include "PALParser.hpp"

const std::string prog = R"SOURCE(
PROGRAM Factorial
WITH i, n, factorial AS INTEGER
IN
    INPUT i
    n = 1
    UNTIL n = i REPEAT
    ENDLOOP
    OUTPUT factorial
END
)SOURCE";

int main(int argc, const char * argv[]) {
    // insert code here...
    PALScanner scanner(prog);
    PALParser parser(scanner);
    
    std::cout << "result: " << (parser.compile() ? "true" : "false" ) << "\n";
    
    for(const auto& e: parser.errors()) {
        std::cout << e << "\n";
    }
    return 0;
}
