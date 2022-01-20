//
//  Sema.hpp
//  CompilerKit
//
//  Created by Amy Parent on 18/01/2022.
//

#ifndef Sema_hpp
#define Sema_hpp

#include "Token.hpp"
#include "Parser.hpp"
#include <memory>
#include <string>
#include <map>

namespace AP::CompilerKit {

enum class Type {
    Integer,
    Real,
    Boolean,
    Invalid,
};

struct Symbol {
    Token token;
    Type type;
};

using SymbolTable = std::map<std::string, Symbol>;

class Scope final {
public:
    
    static Scope* open();
    static Scope* current();
    static void close();
    
    bool define(const Token& token, Type type);
    bool isDefined(const std::string& name) const;
    const Symbol* get(const std::string& name) const;
    
    
private:
    Scope(Scope *parent);
    virtual ~Scope() {}
    
    static Scope* current_;
    Scope* parent_;
    SymbolTable symbols_;
};


class Sema {
public:
    Sema(Parser& parser) : parser_(parser) {}
    virtual ~Sema() {}
    
    const void semaError(const Token& token, const std::string& message);
    
    /// Reports a type mismatch: left-hand side type doesn't match right-hand side type in a binary expression.
    const void binaryExprError(const Token& op, Type lhs, Type rhs);
    
    const void booleanExprError(const Token& op, Type lhs, Type rhs);
    
    const void assignmentError(const Token& var, Type lhs, Type rhs);
    
    const void undeclaredError(const Token& var);
    const void redeclaredError(const Token& var);
private:
    Parser& parser_;
};

}

std::ostream& operator<<(std::ostream& out, AP::CompilerKit::Type type);

#endif /* Sema_hpp */
