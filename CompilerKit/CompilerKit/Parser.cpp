//
//  Parser.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/12/2021.
//

#include "Parser.hpp"

namespace AP::CompilerKit {

Parser::Parser(Scanner* scanner) : scanner_(scanner), recovering_(false) {
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
    if(recovering_) {
        while(!have(type) && !current().is(Token::EndOfFile)) {
            scanner().lex();
        }
        recovering_ = false;
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
            recovering_ = true;
            return false;
        }
    }
}


}
