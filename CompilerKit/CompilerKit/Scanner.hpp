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
    
    /// Lexes one more token from the source. You must override this in your implementation.
    virtual std::optional<Token> nextToken() = 0;
protected:
    
    /// Advances the lexer by one character in the source, and returns that character.
    char nextChar();
private:
    std::string source_;
};


}

#endif /* Scanner_hpp */
