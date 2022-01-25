//
//  CodeGen.hpp
//  CompilerKit
//
//  Created by Amy Parent on 09/12/2021.
//

#ifndef CodeGen_hpp
#define CodeGen_hpp

#include "Program.hpp"
#include <iostream>
#include <map>
#include <vector>

namespace CompilerKit {

class Codegen {
public:
    using Location = size_t;
    Codegen();
    virtual ~Codegen() {}
    
    void emit(Instruction instr);
    void emit(Instruction instr, uint8_t operand);
    void emit(Instruction instr, uint16_t operand);
    void emitConst(float constant);
    
    void startLoop();
    void startLoopBody();
    void endLoop();

    void startConditional();
    void startIfBody();
    void startElseBody();
    void endConditional();
    
    void emitVariableInstr(Instruction instr, const std::string& name);
    
    Location emitJump(Instruction instr);
    void patchJump(Location loc);
    
    Program getProgram();
    
private:
    uint16_t offsetTo(Location loc);
    uint16_t variableAddress(const std::string& name);
    
    struct IfData{
        Location endJump;
        Location elseJump;
    };
    
    struct LoopData{
        Location start;
        Location endJump;
    };
    
    std::vector<IfData> ifStack_;
    std::vector<LoopData> loopStack_;
    std::map<std::string, uint16_t> variables_;
    std::vector<float> constants_;
    std::vector<uint8_t> code_;
};

}

#endif /* CodeGen_hpp */
