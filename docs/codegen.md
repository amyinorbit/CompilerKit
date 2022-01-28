# CompilerKit::Codegen

`Codegen` provides an API that can be used to create small but working bytecode programs using
the virtual instruction set described in [`Program`](program.html). It follows `Program`'s
stack-based model, and abstracts away labels, jumps, loops, constants and variables.

For example, emitting a program that loops would look like this, when called from a recursive
descent parser:

```c++
Codegen gen;

gen.startLoop();

// This function should emit code that leaves the boolean result on the stack.
recBooleanExpr();

gen.startLoopBody();

// ...
// Here goes the contents of your loop.
// ...
recStatementBlock();

gen.endLoop();
```


### Public API

#### `Codegen()`

Creates a new `Codegen` instance.

#### `getProgram() -> Program`

Returns the bytecode program that has been generated.

***

#### `emit(Instruction instr, ...) -> void`

```
emit(Instruction instr) -> void (1)
emit(Instruction instr, uint8_t operand) -> void (2)
emit(Instruction instr, uint16_t operand) -> void (3)
```

Emits one instruction (1), along its 8-bit (2) or 16-bit (3) operand.

**Parameters:**

- `instr`: a byte code instruction (see [`Program`](program.html) for listing).
- `operand` (optional): a 8-bit or 16-bit integer operand to `instr`.

#### `emitConst(float value) -> void`

Adds a constant numeric value to the program, and emits the bytecode instruction to load it
(`Instruction::Const`).

**Parameters:**

- `value`: the constant's numeric value.

***

#### `startLoop() -> void`

Marks the start of a loop's condition. This must be called right before emitting the bytecode for
the boolean expression driving the loop.

#### `startLoopBody() -> void`

Marks the end of a loop's condition, and the beginning of its body. This should be called right
after emitting the bytecode for the boolean expression driving the loop, and expect a boolean
value to have been pushed on top of the operand stack.

#### `endLoop() -> void`

Marks the end of a loop's body.

***

#### `startConditonal() -> void`

Marks the start of a conditonal statement. This must be called right before emitting the bytecode
for the boolean expression used by the conditional.

#### `startIfBody() -> void`

Marks the end of a conditional statement's condition, and the start of the `true` case's body. This
must be called right after emitting the bytecode for the boolean expression used by the
conditional.

#### `startElseBody() -> void`

Marks the end of a conditional statement's condition, and the start of the `false` case's body. This
section is optional.

If an `else if(...) {...}` statement is desired, a call to `startConditional()` can be made after.

#### `endConditional() -> void`

Marks the end of a conditional statement. Note that conditional statements can be nested: there must
be as many calls to `endConditional` as there were to `startConditional`.

