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
#include "Error.hpp"
#include <memory>
#include <vector>

namespace CompilerKit {

/// A simple recursive descent parser that aborts parsing on the first error.
class Parser {
public:
    Parser(Scanner& scanner);
    virtual ~Parser() {}
    
    /// Start lexing and call the `recStarter()` method.
    virtual void parse();
    
    /// Returns a list of the errors that have occured during compilation.
    const std::vector<Error>& errors() const { return errors_; }
    
    /// Returns whether the parser is currently in recovery mode.
    virtual bool isRecovering() const { return false; }
    
    virtual void addError(const Error& error);
protected:
    
    /// The first recogniser, called by `parse()`. This must be implemented by subclasses.
    virtual void recStarter() = 0;
    
    /// Returns the scanner's current token. Same as `calling scanner().current()`.
    Token current() const;
    
    /// Returns the scanner object attached to this parser.
    Scanner& scanner();
    
    /// Returns whether the scanner's current token is of the given type.
    bool have(const std::string& type) const;
    
    /// Returns whether the scanner's current token is of the given type, and lexes the next token if it is.
    bool match(const std::string& type);
    
    /// If the scanner's current token is of the given type, lexes the next token.
    /// Otherwise, aborts
    virtual bool expect(const std::string& type);
    
    /// Emits a syntax error, and aborts parse.
    virtual void syntaxError(const std::string& expected);
    
private:
    std::vector<Error> errors_;
    Scanner& scanner_;
};


/// A more advanced recursive descent parser that can recover from syntax errors.
class RecoveringParser : public Parser {
public:
    RecoveringParser(Scanner& scanner);
    virtual ~RecoveringParser() {}
    
    /// Start lexing and call the `recStarter()` method.
    virtual void parse();
    
    /// Returns whether the parser is currently in recovery mode.
    virtual bool isRecovering() const { return isRecovering_; }
    
protected:
    virtual bool expect(const std::string& type) final;
    virtual void syntaxError(const std::string& expected) final;
private:
    bool isRecovering_ = false;
};

}

#endif /* Parser_hpp */
