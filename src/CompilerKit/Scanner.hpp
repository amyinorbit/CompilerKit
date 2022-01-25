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
    
    /// Advances the lexer by one character in the source, and returns that character.
    char advance();
    
protected:
    
    /// Marks the current position in the source text as the start of a token.
    /// Use in combination with `makeToken()`.
    void startToken();
    
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
    
    /// Sets the point where a token starts. Call this when lexing!
    void updateTokenStart();
    
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
