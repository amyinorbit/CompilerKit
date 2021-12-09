//
//  Token.h
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#ifndef Token_h
#define Token_h

#include <string>

namespace AP::CompilerKit {
    class Token final {
    public:
        /// A token that represents an identifier.
        static constexpr const char *Identifier = "Identifier";
        /// A token that represents a real number literal.
        static constexpr const char *Real = "Real";
        /// A token that represents an integer literal.
        static constexpr const char *Integer = "Integer";
        /// A token that represents the end of the source file.
        static constexpr const char *EndOfFile = "EndOfFile";
        static constexpr const char *InvalidToken = "InvalidToken";
        static constexpr const char *InvalidChar = "InvalidChar";
        
        Token() : type_(InvalidToken), text_(InvalidToken), line_(0), column_(0) {}
        
        /// Creates a new token.
        Token(const std::string& type, const std::string& text, int line, int col)
        {}
        
        /// Returns the translated value that the token represents.
        template <typename T>
        T value() const;
        
        /// Returns the floating-point value the token represents.
        template <>
        double value<double>() const {
            if(type_ != Integer && type_ != Real) return 0;
            return std::stod(text_);
        }
        
        /// Returns the integer value the token represents.
        template <>
        int value<int>() const {
            if(type_ != Integer && type_ != Real) return 0;
            return std::stoi(text_);
        }
        
        
        // MARK: - Accessors
        
        bool is(const std::string& type) const { return type == type_; }
        
        const std::string& type() const { return type_; }
        const std::string& text() const { return text_; }
        std::pair<int, int> sourceLoc() const { return {line_, column_}; }
        
    private:
        std::string type_;
        std::string text_;
        int line_ = -1;
        int column_ = -1;
    };
}

#endif /* Token_h */
