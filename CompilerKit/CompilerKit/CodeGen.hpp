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

namespace AP::CompilerKit {

class CodeGen {
public:
    using Location = size_t;
    CodeGen();
    virtual ~CodeGen() {}
    
    Location startLoop();
    void jumpLoop(Location mark);
    void finishLoop(Location mark);
    
    
    Program finish();
    
private:
    Program program_;
};

}

#endif /* CodeGen_hpp */
