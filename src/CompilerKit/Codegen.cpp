//
//  CodeGen.cpp
//  CompilerKit
//
//  Created by Amy Parent on 09/12/2021.
//

#include "Codegen.hpp"
#include <cstdio>
#include <cstdarg>

namespace CompilerKit {

// If we have errors in codegen, it's a programming error, not a user error. Crash hard & early
// so we can debug!
static inline void check(bool condition, const char *fmt, ...) {
    if(condition) return;
    fprintf(stderr, "code generation error: ");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    abort();
}

Codegen::Codegen() {}

void Codegen::emit(Instruction instr) {
    code_.push_back(static_cast<uint8_t>(instr));
}

void Codegen::emit(Instruction instr, uint8_t operand) {
    code_.push_back(static_cast<uint8_t>(instr));
    code_.push_back(operand);
}

void Codegen::emit(Instruction instr, uint16_t operand) {
    code_.push_back(static_cast<uint8_t>(instr));
    code_.push_back(operand >> 8);
    code_.push_back(operand & 0xff);
}


// If you've made it this far: well done, good on your for being curious!
//
// This is by far not the most efficient way of doing constants: every time we use a 0 or 1,
// we're going to create a new constant for it. PAL is, by definition, pretty awful, but can
// you think of an easy optimisation that could be done here?
void Codegen::emitConst(float constant) {
    check(constants_.size() <= UINT16_MAX, "too many constants");
    
    size_t id = constants_.size();
    constants_.push_back(constant);
    assert(id <= UINT16_MAX);
    
    emit(Instruction::Const, static_cast<uint16_t>(id));
}

uint16_t Codegen::offsetTo(Location loc) {
    Location here = code_.size();
    size_t offset = here > loc ? here - loc : loc - here;
    
    check(offset <= UINT16_MAX, "attempted to write a jump larger than %d (%d)", UINT16_MAX, offset);
    return offset;
}


// You could have many nested for loops. Therefore, we use a stack to keep track of code locations
// where we start and stop our loops. The only thing this does is mark where we need to jump back
// when the loop repeats.
void Codegen::startLoop() {
    loopStack_.push_back(LoopData{code_.size(), SIZE_MAX});
}

// This is a bit more interesting. The way loops work in bytecode is:
//
// [start marker] <do some conditional here>
// jump if true -> [body marker]
// jump -> [end marker]
// [body marker] ... loop stuff here ...
// jump -> [start marker]
// [end marker]
//
// Essentially, it's just about jump over ourselves a lot.
void Codegen::startLoopBody() {
    // If we're not in a loop, we've made a whoopsie. crash!
    check(loopStack_.size(), "attempted to start a loop body outside a loop");
    
    LoopData& data = loopStack_.back();
    
    // If we're not true, jump to the body
    Location bodyJump = emitJump(Instruction::IfNot);
    
    // If we didn't jump, we're true (spaghetti logic!) so now we can jump to the end.
    data.endJump = emitJump(Instruction::Jump);
    
    // Finally, patch the body jump. Here goes the actual body.
    patchJump(bodyJump);
}

void Codegen::endLoop() {
    // If we're not in a loop, we've made a whoopsie. crash!
    check(loopStack_.size(), "attempted to start a loop body outside a loop");

    
    LoopData& data = loopStack_.back();
    // Check that we actually have started the body. If not, crash.
    check(data.endJump != SIZE_MAX, "attempted to close a loop without declaring a body");
    
    // Two things here:
    // - first we jump back to the start of the loop (where the condition is tested).
    // - second, we patch the end jump to point here.
    emit(Instruction::Loop, static_cast<uint16_t>(offsetTo(data.start) + 3));
    patchJump(data.endJump);
}

void Codegen::startConditional() {
    ifStack_.push_back(IfData{UINT16_MAX, UINT16_MAX});
}

void Codegen::startIfBody() {
    check(ifStack_.size(), "attempted to start a conditional's if body outside of a conditional");
    
    IfData& data = ifStack_.back();
    data.endJump = emitJump(Instruction::IfNot);
}

void Codegen::startElseBody() {
    check(ifStack_.size(), "attempted to start a conditional's else body outside of a conditional");
    
    IfData& data = ifStack_.back();
    check(data.endJump != SIZE_MAX, "attempted to add a else body before a if body");
    data.elseJump = data.endJump;
    
    data.endJump = emitJump(Instruction::Jump);
    patchJump(data.elseJump);
    
}

void Codegen::endConditional() {
    check(ifStack_.size(), "attempted to start a conditional's else body outside of a conditional");
    
    IfData& data = ifStack_.back();
    check(data.endJump != SIZE_MAX, "attempted to add a else body before a if body");
    patchJump(data.endJump);
}

Codegen::Location Codegen::emitJump(Instruction instr) {
    emit(instr);
    Location loc = code_.size();
    code_.push_back(0xff);
    code_.push_back(0xff);
    return loc;
}

void Codegen::patchJump(Location loc) {
    check(loc < code_.size() - 1, "%d is not a valid jump location", (int)loc);
    
    uint16_t offset = offsetTo(loc+2);
    code_[loc] = offset >> 16;
    code_[loc+1] = offset & 0xff;
}

uint16_t Codegen::variableAddress(const std::string& name) {
    if(variables_.find(name) != variables_.end()) {
        return variables_.at(name);
    }
    
    check(variables_.size() <= UINT16_MAX, "too many variables");
    uint16_t id = static_cast<uint16_t>(variables_.size());
    variables_[name] = id;
    return id;
}

void Codegen::emitVariableInstr(Instruction instr, const std::string& name) {
    emit(instr, variableAddress(name));
}


Program Codegen::getProgram() {
    emit(Instruction::Halt);
    return Program{code_, constants_, static_cast<uint16_t>(variables_.size())};
}


}
