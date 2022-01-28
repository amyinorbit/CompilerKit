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

namespace CompilerKit {

enum class Instruction {
    Halt,
    Noop,
    Const,
    Load,
    Store,
    Input,
    Output,
    
    Neg,
    Add,
    Sub,
    Mul,
    Div,
    
    Greater,
    Less,
    Equals,
    
    And,
    Or,
    Not,
    
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

std::ostream& operator<<(std::ostream& out, const CompilerKit::Program& program);

#endif /* Program_hpp */
