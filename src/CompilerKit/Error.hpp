//
//  Error.hpp
//  CompilerKit
//
//  Created by Amy Parent on 09/12/2021.
//

#ifndef Error_hpp
#define Error_hpp

#include "Token.hpp"
#include <iostream>
#include <string>

namespace CompilerKit {

using std::string;

class Error {
public:
    
    /// Creates a syntax error for a given expected token type at a given token.
    static Error Syntax(const string& expected, const Token& token);
    static Error Semantic(const string& message, const Token& token);
    
    // MARK: - comparison operators for nice sorting
    bool operator<(const Error& other) const;
    bool operator>(const Error& other) const;
    
    // MARK: - printing to the standard output
    void print(std::ostream& out) const;
    
private:
    
    Error(const string& type, const string& message, int line, int column);
    
    int line_;
    int column_;
    string type_;
    string message_;
};

/// Allows pretty-printing of errors directly to std::cout/std::cerr.
std::ostream& operator<<(std::ostream& out, const Error& error);

}

#endif /* Error_hpp */
