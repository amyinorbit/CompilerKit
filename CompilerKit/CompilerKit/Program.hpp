//
//  Program.hpp
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>

#define STACK_SIZE (1024)

namespace AP::CompilerKit {

enum class Instruction {
    Halt,
    Const,
    Load,
    Store,
    Input,
    Output,
    Add,
    Sub,
    Mul,
    Div,
    And,
    Or,
    Not,
    Greater,
    Less,
    Equals,
    
    Jump,
    Loop,
    IfNot,
};

struct InterpreterError : public std::runtime_error {
    using std::runtime_error::runtime_error;
    virtual ~InterpreterError() {}
};

struct Program {
    std::vector<uint8_t> code;
    std::vector<float> constants;
    uint16_t variableCount;
};

/// Runs a program.
void run(const Program& program);

}

std::ostream& operator<<(std::ostream& out, const AP::CompilerKit::Program& program);

#endif /* Program_hpp */
