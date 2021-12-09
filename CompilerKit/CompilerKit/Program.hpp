//
//  Program.hpp
//  CompilerKit
//
//  Created by Amy Parent on 09/11/2021.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>

namespace AP::CompilerKit {

enum class Instruction {
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
    If,
    Loop,
};

class Program {
public:
    
    bool run();
    
private:
    
};

}


#endif /* Program_hpp */
