#  CompilerKit::Error

Compiler errors in CompilerKit are all represented by the `Error` class. New instances of `error`
cannot be created through the constructor. Instead, [static functions](#staticapi) are provided
to create different types of errors.

Errors can be printed to any standard library output stream (`#include <iostream>`) using the
standard caret syntax:

```c++
Error err = Error:Generic("I/O", "something went wrong", token);
std::cout << err << "\n";
```

### Static API


#### `Error::Syntax(const string& expected, const Token& token) -> Error`

Returns a new instance of `Error` for a syntax error, for a given expected token type and actual
found token.

**Parameters:**

- `expected`: the type of token that was expected by the parser.
- `token`: the token that was found by the parser.

#### `Error::Semantic(const string& message, const Token& token) -> Error`

Returns a new instance of `Error` for a semantic error at a given token in the source code.

**Parameters:**

- `message`: the error message to attach to the error.
- `token`: the token where the error was found.

#### `Error Generic(const string& type, const string& message, const Token& token) -> Error`

Returns a compiler error of a given type, at a given token and with a given message.

**Parameters:**

- `type`: a type of error, shown when printing the error.
- `message`: the error message to attach to the error.
- `token`: the token where the error was found.

### Public API

#### `print(std::ostream& out) -> void`

Prints the error, along with its source code location, to an output stream.

**Parameters:**

- `out`: the output stream to print `this` to.

#### Operators

```
operator<(const Error& other) const -> bool
operator>(const Error& other) const -> bool
```

Comparison operators implemented to allow sorting a collection of errors by line and columns.

