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

namespace AP::CompilerKit {

using std::string;

class Error {
public:
    
    /// Creates a syntax error for a given expected token type at a given token.
    Error Syntax(const string& expected, const Token& token);
    Error IO(const string& message);
    
    // MARK: - comparison operators for nice sorting
    bool operator<(const Error& other);
    bool operator>(const Error& other);
    
    // MARK: - printing to the standard output
    void print(std::ostream& out);
    
private:
    Error(const string& type, const string& message, int line, int column);
    
    int line_;
    int column_;
    const string& type;
    const string& message;
};

/// Allows pretty-printing of errors directly to std::cout/std::cerr.
std::ostream& operator<<(std::ostream& out, const Error& error);

}

#endif /* Error_hpp */
