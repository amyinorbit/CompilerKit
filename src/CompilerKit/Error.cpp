//
//  Error.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/12/2021.
//

#include "Error.hpp"
#include <sstream>

namespace AP::CompilerKit {

Error Error::Syntax(const string &expected, const Token &token) {
    
    std::stringstream stream;
    
    stream << "expected " << expected;
    stream << ", found " << token.type() << " instead";
    auto [line, col] = token.sourceLoc();
    
    return Error("syntax", stream.str(), line, col);
}


Error Error::Semantic(const string& message, const Token& token) {
    auto [line, col] = token.sourceLoc();
    return Error("semantic", message, line, col);
}

Error::Error(const string& type, const string& message, int line, int column)
: line_(line)
, column_(column)
, type_(type)
, message_(message) {
    
}

bool Error::operator<(const Error &other) const {
    if(line_ < other.line_) return true;
    if(line_ > other.line_) return false;
    return column_ < other.column_;
}

bool Error::operator>(const Error &other) const {
    if(line_ > other.line_) return true;
    if(line_ < other.line_) return false;
    return column_ > other.column_;
}

void Error::print(std::ostream &out) const {
    out << type_ << " error at " << line_ << ":" << column_ << ": ";
    out << message_;
}

std::ostream& operator<<(std::ostream& out, const Error& error) {
    error.print(out);
    return out;
}

}
