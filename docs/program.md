#  `Program` and the CompilerKit Runtime

`Program` is a simple struct type that is used by [`Codegen`](codegen.html) to store and return
a program's compiled bytecode that can be run using the CompilerKit runtime. You should not build
a `Program` instance by hand, but instead use `Codegen`.

## `CompilerKit::Program`

```c++
struct Program {
    std::vector<uint8_t> code;
    std::vector<float> constants;
    uint16_t variableCount;
};
```

Programs do not have methods. Instead, they can be run using the free-standing function
`CompilerKit::run(const Program& program)`. For debugging purposes, a program can be
disassembled and printed to an output stream with the standard caret syntax:

```c++
Program prog = codegen.getProgram();
std::cout << prog << "\n"; // print out machine code for debugging.
run(program);
```

## The CompilerKit Runtime

The CompilerKit runtime is a very simple stack-based virtual machine. Operations pop their operand
values from the stack, and push their results onto it. There is a separate memory dedicated to
local variables, and a constant pool included with the program.

Instructions for the runtime are 8-bit long, with an optional 16-bit operand, used for instructions
that require a jump offset, a constant index, or a local variable index. The table presented below
lists valid runtime instructions.

| Mnemonic  | Operand       | Stack Effect  | Description                                       |
|:----------|:--------------|:--------------|:--------------------------------------------------|
| `Halt`    | no            | []            | Stop the execution of the program                 |
| `Noop`    | no            | []            | Do nothing                                        |
| `Const`   | 16-bit index  | push 1        | Push the constant at index onto stack             |
| `Load`    | 16-bit index  | push 1        | Push the local variable at index onto stack       |
| `Store`   | 16-bit index  | pop 1         | Pop a value into the local variable at index      |
| `Input`   | no            | push 1        | Read value from stdin and push it onto stack      |
| `Output`  | no            | pop 1         | Pop a value and display it on stdout              |
| `Neg`     | no            | pop 1, push 1 | Pop a float from the stack, and push its opposite |
| `Add`     | no            | pop 2, push 1 | Pop floats `b` then `a`, push `a + b`             |
| `Sub`     | no            | pop 2, push 1 | Pop floats `b` then `a`, push `a - b`             |
| `Mul`     | no            | pop 2, push 1 | Pop floats `b` then `a`, push `a * b`             |
| `Greater` | no            | pop 2, push 1 | Pop floats `b` then `a`, push `a > b`             |
| `Less`    | no            | pop 2, push 1 | Pop floats `b` then `a`, push `a < b`             |
| `Equals`  | no            | pop 2, push 1 | Pop floats `b` then `a`, push `a == b`            |
| `And`     | no            | pop 2, push 1 | Pop booleans `b` then `a`, push `a && b`          |
| `Or`      | no            | pop 2, push 1 | Pop booleans `b` then `a`, push `a || b`          |
| `Not`     | no            | pop 1, push 1 | Pop boolean `a` from stack, and push `!a`         |
| `Jump`    | 16-bit offset | []            | Advance instruction pointer by offset             |
| `Loop`    | 16-bit offset | []            | Rewind instruction pointer by offset              |
| `IfNot`   | 16-bit offset | pop 1         | Pop boolean from stack, if false, same as `Jump`  |


