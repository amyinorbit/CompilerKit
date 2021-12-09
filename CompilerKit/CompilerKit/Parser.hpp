//
//  Parser.hpp
//  CompilerKit
//
//  Created by Amy Parent on 09/12/2021.
//

#ifndef Parser_hpp
#define Parser_hpp

#include "Token.hpp"
#include "Scanner.hpp"
#include <memory>

namespace AP::CompilerKit {

class Parser {
public:
    Parser(Scanner* scanner);
    virtual ~Parser() {}
protected:
    
    /// Returns the scanner's current token. Same as `calling scanner().current()`.
    Token current() const;
    
    /// Returns the scanner object attached to this parser.
    Scanner& scanner();
    
    /// Returns whether the scanner's current token is of the given type.
    bool have(const std::string& type) const;
    
    /// Returns whether the scanner's current token is of the given type, and lexes the next token if it is.
    bool match(const std::string& type);
    
    /// If the scanner's current token is of the given type, lexes the next token. Otherwise, enter error recovery mode.
    bool expect(const std::string& type);
private:
    
    std::unique_ptr<Scanner> scanner_;
    bool recovering_ = false;
};

}

#endif /* Parser_hpp */
