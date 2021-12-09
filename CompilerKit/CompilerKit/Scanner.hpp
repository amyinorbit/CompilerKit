//
//  Scanner.hpp
//  CompilerKit
//
//  Created by Amy Parent on 07/12/2021.
//

#ifndef Scanner_hpp
#define Scanner_hpp

#include "Token.hpp"
#include <optional>

namespace AP::CompilerKit {

class Scanner {
public:
    /// Creates a new scanner for a given source text.
    Scanner(const std::string& source);
    virtual ~Scanner() {}
    
    /// Lexes one more token from the source. You must override this in your implementation.
    virtual Token lex() = 0;
    
    /// Returns the last token lexed by the scanner.
    Token current() const;
protected:
    
    /// Marks the current position in the source text as the start of a token. Use in combination with `makeToken()`.
    void startToken();
    
    /// Advances the lexer by one character in the source, and returns that character.
    char advance();
    
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
    
    Token current_;
    std::string source_;
    int line_ = 1;
    int column_ = 1;
    int idx_ = 0;
};


}

#endif /* Scanner_hpp */
