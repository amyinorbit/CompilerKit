//
//  Program.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#include "Program.hpp"
#include <iomanip>
#include <utility>

// This is where the magic happens!
//
// If you're here, well done! Remember, you do *not* need to understand (or even use) this to
// get full marks on your assessment. However, there's a tonne of interesting things happening here.
//
int disassembleInstr(std::ostream& out, const uint8_t *ip);
namespace AP::CompilerKit {

using std::vector;
using std::string;

// We use this Runtime class to keep track of the state of our program's execution. It is
// really a small virtual machine, with (rudimentary) memory, an instruction pointer and a stack.
class Runtime {
public:
    Runtime(const Program& program) {
        variables = new float[program.variableCount];
        for(int i = 0; i < program.variableCount; ++i) {
            variables[i] = 0;
        }
        stack = new Value[STACK_SIZE];
        sp = stack;
        code = program.code.data();
        ip = code;
    }
    
    ~Runtime() {
        delete [] variables;
        delete [] stack;
        ip = nullptr;
        sp = nullptr;
    }
    
    void debugStack() {
        std::cout << "\t\t> stack (" << int(sp - stack) << "): ";
        for(const Value* v = stack; v < sp; ++v) {
            std::cout << v->f32 << "/" << (v->b ? "true" : "false") << " ";
        }
        std::cout << "\n";
    }
    
    void debugInstr() {
        std::cout << std::setfill('0') << std::setw(4) << std::hex;
        std::cout << (ip - code) << "\t";
        std::cout << std::setw(0) << std::setfill(' ') << std::dec;
        disassembleInstr(std::cout, ip);
        std::cout << "\n";
    }
    
    // Returns the next instruction in the program.
    Instruction readi() {
        
        return static_cast<Instruction>(read8());
    }
    
    // Returns a reference to a given variable.
    float& variable(uint16_t idx) {
        return variables[idx];
    }
    
    // Moves the instruction pointer forward by a given amount.
    void jump(uint16_t offset) {
        ip += offset;
    }
    
    // Moves the instruction pointer backward by a given amount.
    void loop(uint16_t offset) {
        ip -= offset;
    }
    
    // Reads a 8-bit integer from the program.
    uint8_t read8() {
        return *(ip++);
    }
    
    // Reads a 16-bit integer from the program.
    uint16_t read16() {
        ip += 2;
        return ip[-2] << 8 | ip[-1];
    }
    
    // Push a value onto the operand stack.
    void push(float val) {
        if(sp >= stack + STACK_SIZE) {
            throw InterpreterError("VM stack overflow");
        }
        (sp++)->f32 = val;
    }
    
    void push(bool val) {
        if(sp >= stack + STACK_SIZE) {
            throw InterpreterError("VM stack overflow");
        }
        (sp++)->b = val;
    }
    
    template <typename T>
    T pop();
    
    // Pops a floating-point number from the operand stack.
    template <>
    float pop<float>() {
        if(sp <= stack) {
            throw InterpreterError("VM stack underflow");
        }
        return (--sp)->f32;
    }
    
    // Pops a boolean value from the operand stack.
    template <>
    bool pop<bool>() {
        if(sp <= stack) {
            throw InterpreterError("VM stack underflow");
        }
        return (--sp)->b;
    }
    
private:
    
    union Value {
        float   f32;
        bool    b;
    };
    float *variables;
    Value *stack;
    Value *sp;
    const uint8_t *code;
    const uint8_t *ip;
};

void run(const Program& program) {
    
    // Runtime here is really just a wrapper on our stack pointer and instruction pointer.
    // This is what we saw in first year architecture!
    Runtime rt(program);
    
    
    // And this is how our (basic) virtual machine works. As you see, there's really not much
    // to it: every time we loop (once "cpu" cycle), we fetch the next instruction in the program
    // memory, then execute it (using that big switch statement).
    while(true) {
        //rt.debugStack();
        //rt.debugInstr();
        Instruction i = rt.readi();
        float input;
        switch(i) {
            case Instruction::Halt:
                return;
                
            case Instruction::Noop:
                break;
                
            case Instruction::Const:
                rt.push(program.constants[rt.read16()]);
                break;
            case Instruction::Load:
                rt.push(rt.variable(rt.read16()));
                break;
            case Instruction::Store:
                rt.variable(rt.read16()) = rt.pop<float>();
                break;
            case Instruction::Input:
                std::cout << "input: ";
                std::cin >> input;
                rt.push(input);
                break;
            case Instruction::Output:
                std::cout << "output: " << rt.pop<float>() << "\n";
                break;
                
            case Instruction::Neg:
                {
                    float a = rt.pop<float>();
                    rt.push(-a);
                }
                break;
            case Instruction::Add:
                {
                    float b = rt.pop<float>();
                    float a = rt.pop<float>();
                    rt.push(a + b);
                }
                break;
            case Instruction::Sub:
            {
                float b = rt.pop<float>();
                float a = rt.pop<float>();
                rt.push(a - b);
            }
                break;
            case Instruction::Mul:
            {
                float b = rt.pop<float>();
                float a = rt.pop<float>();
                rt.push(a * b);
            }
                break;
            case Instruction::Div:
            {
                float b = rt.pop<float>();
                float a = rt.pop<float>();
                rt.push(a / b);
            }
                break;
            case Instruction::And:
            {
                // Hint: this is valid for PAL, but doesn't respect the C standard for example.
                // Do you know why?
                bool b = rt.pop<bool>();
                bool a = rt.pop<bool>();
                rt.push(a && b);
            }
                break;
            case Instruction::Or:
            {
                // Hint: this is valid for PAL, but doesn't respect the C standard for example.
                // Do you know why?
                bool b = rt.pop<bool>();
                bool a = rt.pop<bool>();
                rt.push(a || b);
            }
                break;
            case Instruction::Not:
                rt.push(!rt.pop<bool>());
                break;
            case Instruction::Greater:
            {
                float b = rt.pop<float>();
                float a = rt.pop<float>();
                rt.push(a > b);
            }
                break;
            case Instruction::Less:
            {
                float b = rt.pop<float>();
                float a = rt.pop<float>();
                rt.push(a < b);
            }
                break;
            case Instruction::Equals:
            {
                float b = rt.pop<float>();
                float a = rt.pop<float>();
                rt.push(a == b);
            }
                break;
            case Instruction::Jump:
                rt.jump(rt.read16());
                break;
            case Instruction::Loop:
                rt.loop(rt.read16());
                break;
            case Instruction::IfNot:
                if(!rt.pop<bool>()) {
                    rt.jump(rt.read16());
                } else {
                    // We need to make sure that we still consume our index here!
                    (void)rt.read16();
                }
                break;
        }
    }
}

}


static inline void print16(std::ostream& out, const uint8_t *ip) {
//    return ip[1] << 16 | ip[2];
    uint16_t op = (ip[1] << 16) | ip[2];
    out << std::setfill('0') << std::setw(4) << std::hex;
    out << op;
    out << std::setw(0) << std::setfill(' ') << std::dec;
}

int disassembleInstr(std::ostream& out, const uint8_t *ip) {
    using AP::CompilerKit::Instruction;
    Instruction i = static_cast<Instruction>(ip[0]);
    out << std::setfill('0');
    switch(i) {
        case Instruction::Halt:
            out << "halt";
            return 1;
        case Instruction::Noop:
            out << "noop";
            return 1;
        case Instruction::Const:
            out << "const\t";
            print16(out, ip);
            return 3;
        case Instruction::Load:
            out << "load\t";
            print16(out, ip);
            return 3;
        case Instruction::Store:
            out << "store\t";
            print16(out, ip);
            return 3;
        case Instruction::Input:
            out << "in";
            return 1;
        case Instruction::Output:
            out << "out";
            return 1;
        case Instruction::Neg:
            out << "neg";
            return 1;
        case Instruction::Add:
            out << "add";
            return 1;
        case Instruction::Sub:
            out << "add";
            return 1;
        case Instruction::Mul:
            out << "mul";
            return 1;
        case Instruction::Div:
            out << "div";
            return 1;
        case Instruction::And:
            out << "and";
            return 1;
        case Instruction::Or:
            out << "or";
            return 1;
        case Instruction::Not:
            out << "not";
            return 1;
        case Instruction::Greater:
            out << "greater";
            return 1;
        case Instruction::Less:
            out << "less";
            return 1;
        case Instruction::Equals:
            out << "equals";
            return 1;
        case Instruction::Jump:
            out << "jump\t";
            print16(out, ip);
            return 3;
        case Instruction::Loop:
            out << "loop\t";
            print16(out, ip);
            return 3;
        case Instruction::IfNot:
            out << "ifnot\t";
            print16(out, ip);
            return 3;
    }
}


std::ostream& operator<<(std::ostream& out, const AP::CompilerKit::Program& program) {
    out << "== disassembly ==\n";
    
    const uint8_t *code = program.code.data();
    
    for(size_t i = 0; i < program.code.size();) {
        out << std::setfill('0') << std::setw(4) << std::hex;
        out << i;
        out << std::setw(0) << std::setfill(' ') << std::dec;
        out << "\t";
        i += disassembleInstr(out, code + i);
        out << "\n";
    }
    
    return out;
}


