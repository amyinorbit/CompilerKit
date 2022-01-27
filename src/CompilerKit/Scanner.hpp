//
//  Scanner.hpp
//  CompilerKit
//
//  Created by Amy Parent on 07/12/2021.
//

#ifndef Scanner_hpp
#define Scanner_hpp

#include "Token.hpp"
#include <iostream>

namespace CompilerKit {

class Scanner {
public:
    /// Creates a new scanner for a given source text.
    Scanner(std::istream& source);
    virtual ~Scanner() {}
    
    /// Lexes one more token from the source. You must override this in your implementation.
    virtual Token lex() = 0;
    
    /// Returns the last token lexed by the scanner.
    Token current() const;
    
    /// Returns whether `this` is at the end of its source stream.
    bool end() const;
    
protected:
    
    /// Advances the lexer by one character in the source, and returns that character.
    char advance();
    
    /// Marks the current position in the source text as the start of a token.
    /// Use in combination with `makeToken()`.
    void updateTokenStart();
    
    /// Returns the next character;
    char peek();
    
    /// Returns the line at which the scanner currently is in the source text.
    int line() const;
    
    /// Returns the column at which the scanner currently is in the source text.
    int column() const;
    
    /// Creates a new token of a given type, assigns it as the current token, and returns it.
    Token makeToken(const std::string& type);
    
    /// Creates a new token of a given type and text, assigns it as the current token, and returns it.
    Token makeToken(const std::string& type, const std::string& text);
    
private:
    
    std::istream& in_;
    Token current_;
    int line_ = 1;
    int column_ = 1;
    
    int startLine_ = 1;
    int startColumn_ = 0;
};


}

#endif /* Scanner_hpp */
