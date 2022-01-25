//
//  Sema.cpp
//  CompilerKit
//
//  Created by Amy Parent on 18/01/2022.
//

#include "Sema.hpp"
#include <sstream>

namespace CompilerKit {

Scope* Scope::current_ = nullptr;

// MARK: - Static scope interface

Scope* Scope::open() {
    Scope* scope = new Scope(current_);
    current_ = scope;
    return scope;
}

Scope* Scope::current() {
    return current_;
}

void Scope::close() {
    if(!current_) return;
    
    Scope* closed = current_;
    current_ = nullptr;
    delete closed;
}

// MARK: - Scope stuff

Scope::Scope(Scope* parent) : parent_(parent) { }

bool Scope::define(const Token& token, Type type) {
    if(isDefined(token.text())) return false;
    symbols_.emplace(token.text(), Symbol{token, type});
    return true;
}

bool Scope::isDefined(const std::string& name) const {
    if(symbols_.find(name) != symbols_.end()) return true;
    return parent_ && parent_->isDefined(name);
}

const Symbol* Scope::get(const std::string& name) const {
    auto it = symbols_.find(name);
    if(it != symbols_.end()) return &it->second;
    if(parent_) return parent_->get(name);
    return nullptr;
}

// MARK: - Abstract Sema class implementation

static inline const char *typeToString(Type type) {
    switch(type) {
        case Type::Integer: return "Integer";
        case Type::Real: return "Real";
        case Type::Boolean: return "Boolean";
        case Type::Invalid: return "Invalid";
    }
}


const void Sema::semaError(const Token& token, const std::string& message) {
    parser_.addError(Error::Semantic(message, token));
}

const void Sema::binaryExprError(const Token& op, Type lhs, Type rhs) {
    std::stringstream buf;
    buf << "invalid operands to binary expression";
    buf << " ('" << typeToString(lhs) << "' " << op.text() << " '" << typeToString(rhs) << "')";
    parser_.addError(Error::Semantic(buf.str(), op));
}

const void Sema::booleanExprError(const Token& op, Type lhs, Type rhs) {
    std::stringstream buf;
    buf << "invalid operands to binary expression";
    buf << " ('" << typeToString(lhs) << "' " << op.text() << " '" << typeToString(rhs) << "')";
    parser_.addError(Error::Semantic(buf.str(), op));
}

const void Sema::assignmentError(const Token& var, Type lhs, Type rhs) {
    std::stringstream buf;
    buf << "assigning variable '" << var.text() << "' of type '" << typeToString(lhs);
    buf <<  "' from incompatible type '" << typeToString(rhs) << "'";
    parser_.addError(Error::Semantic(buf.str(), var));
}


const void Sema::undeclaredError(const Token& var) {
    std::stringstream buf;
    buf << "use of undeclared variable '" << var.text() << "'";
    parser_.addError(Error::Semantic(buf.str(), var));
}

const void Sema::redeclaredError(const Token& var) {
    std::stringstream buf;
    buf << "redefinition of variable '" << var.text() << "'";
    parser_.addError(Error::Semantic(buf.str(), var));
}

}

std::ostream& operator<<(std::ostream& out, CompilerKit::Type type) {
    using CompilerKit::Type;
    out << CompilerKit::typeToString(type);
    return out;
}

