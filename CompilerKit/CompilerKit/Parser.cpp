//
//  Parser.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/12/2021.
//

#include "Parser.hpp"

namespace AP::CompilerKit {

Parser::Parser(Scanner* scanner) : scanner_(scanner) {
    assert(scanner != nullptr);
}

Scanner& Parser::scanner() {
    assert(scanner_);
    return *scanner_;
}

Token Parser::current() const {
    return scanner_->current();
}

bool Parser::have(const std::string& type) const {
    return current().is(type);
}

bool Parser::match(const std::string& type) {
    if(!have(type)) return false;
    scanner().lex();
    return true;
}

bool Parser::expect(const std::string &type) {
    if(have(type)) {
        scanner().lex();
        return true;
    }
    throw syntaxError(type);
    return false;
}

const Error& Parser::syntaxError(const std::string& expected) {
    return errors_.emplace_back(Error::Syntax(expected, current()));
}

RecoveringParser::RecoveringParser(Scanner* scanner) : Parser(scanner), isRecovering_(false) {
    
}

bool RecoveringParser::expect(const std::string &type) {
    if(isRecovering_) {
        while(!have(type) && !current().is(Token::EndOfFile)) {
            scanner().lex();
        }
        isRecovering_ = false;
        if(have(type)) {
            scanner().lex();
            return true;
        }
        return false;
    } else {
        if(have(type)) {
            scanner().lex();
            return true;
        } else {
            syntaxError(type);
            isRecovering_ = true;
            return false;
        }
    }
}

}
