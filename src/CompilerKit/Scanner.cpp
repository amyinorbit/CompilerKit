//
//  Scanner.cpp
//  CompilerKit
//
//  Created by Amy Parent on 07/12/2021.
//

#include "Scanner.hpp"

namespace CompilerKit {

Scanner::Scanner(std::istream& source)
    : in_(source)
    , line_(1)
    , column_(1) { }

char Scanner::advance() {
    if(in_.peek() == EOF) return '\0';
    char c = in_.get();
    
    if(c == '\n') {
        column_ = 0;
        line_ += 1;
    }
    column_ += 1;
    return c;
}

bool Scanner::end() const {
    return (in_.peek() == EOF);
}

Token Scanner::current() const {
    return current_;
}

Token Scanner::makeToken(const std::string &type) {
    return current_ = Token(type, type, startLine_, startColumn_);
}

Token Scanner::makeToken(const std::string &type, const std::string &text) {
    return current_ = Token(type, text, startLine_, startColumn_);
}

void Scanner::updateTokenStart() {
    startLine_ = line();
    startColumn_ = column();
}

char Scanner::peek() {
    if(in_.peek() == EOF) return '\0';
    return in_.peek();
}

int Scanner::line() const {
    return line_;
}

int Scanner::column() const {
    return column_;
}

}

