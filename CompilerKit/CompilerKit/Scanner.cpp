//
//  Scanner.cpp
//  CompilerKit
//
//  Created by Amy Parent on 07/12/2021.
//

#include "Scanner.hpp"

namespace AP::CompilerKit {

Scanner::Scanner(const std::string& source)
    : source_(source)
    , line_(1)
    , column_(1)
    , idx_(0) { }

char Scanner::advance() {
    if(idx_ >= source_.size()) return '\0';
    char c = source_[idx_];
    idx_ += 1;
    
    if(c == '\n') {
        column_ = 0;
        line_ += 1;
    }
    column_ += 1;
    return c;
}

Token Scanner::current() const {
    return current_;
}

Token Scanner::makeToken(const std::string &type) {
    return current_ = Token(type, type, line(), column());
}

Token Scanner::makeToken(const std::string &type, const std::string &text) {
    return current_ = Token(type, text, line(), column());
}

char Scanner::peek() {
    if(idx_ >= source_.size()) return '\0';
    return source_[idx_];
}

int Scanner::line() const {
    return line_;
}

int Scanner::column() const {
    return column_;
}

}

