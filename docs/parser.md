# CompilerKit::Parser

`Parser`, and the derived `RecoveringParser`, are base classes that provide you with tools to
build a recursive-descent parser. It implements the three functions such parsers require, `have()`,
`match()` and `expect()`, and relies on an instance of [`Scanner`](scanner.html) to provide a
stream of tokens.

`Parser` is also the driving logic of your compiler, and provides an interface to register errors,
both from itself (`Error::Syntax`) and from other parts of your compiler. If your parser is derived
from `Parser`, the first call to `syntaxError()` will also `throw()`. If it is derived from
`RecoveringParser`, then errors will be stored, and the parser will go into recovery.

To implement your own parser, you must subclass `Parser` or `RecoveringParser`, and implement
at least the `recStarter()` method, which will be called by `Parser.parse()`.

```c++
include "CompilerKit/Parser::hpp"
using namespace CompilerKit;

class MyParser : public Parser {
public:
    MyParser(Scanner& scanner) : Parser(scanner) {}
    virtual ~MyParser() {}
    
    void recStarter() override {
        ...
    }
};
```


## Public Interface

#### `Parser(Scanner& scanner)`

Creates a new instance of `Parser`.

**Parameters:**

- `scanner`: the `Scanner` instance used to generate tokens from the source string.

#### `parse()`

Starts the parsing process and calls the implementation-defined `recStarter()` method. Errors
thrown during compilation are caught and interrupt the parsing process.

#### `errors() const -> const std::vector<Error>&`

Returns a list of errors that have occurred during parsing.

#### `isRecovering() const -> bool`

Returns whether the parser is currently in recovery or not. Will always be `false` for straight
instances of `Parser`.

#### `addError(const Error& error)`

Emits a compilation error. Errors can be emitted from anywhere, and are not necessarily syntax
errors.

**Parameters:**

- `error`: a new error to log.


## Protected Interface

These methods are available when writing a class that derives from `Parser`.

#### `scanner() -> Scanner&`

Returns the `Scanner` instance attached to `this`.


#### `current() -> Token`


Returns the last token lexed by the `Scanner` instance attached to `this`. Equivalent to
calling `parser.scanner().current()`.


#### `have(const std::string& type) const -> bool`


Returns whether the last token lexed by the scanner attached to `this` is of a given type.

**Parameters:**

- `type`: the type of token to check for.


#### `match(const std::string& type) -> bool`

Checks whether the last token lexed by the scanner attached to `this` is of a given type. If
it is, lexes one more token and returns true, otherwise returns false.

**Parameters:**

- `type`: the type of token to check for.


#### `expect(const std::string& type) -> bool`

Checks that the last token lexed by the scanner attached to `this` is of a given type. If it is,
lexes one more token and returns true. If it isn't, emits a syntax error and returns false.

**Parameters:**

- `type`: the type of token to check for.


#### `syntaxError(const std::string& expected) -> void`

Emits a syntax error, informing the user that a token of a unexpected type was found. For instances
of `Parser`, the error will be thrown after it has been logged. For instances of `RecoveringParser`,
the parser goes into recovery.

**Parameters:**

- `expected`: the type of token that was expected.


# CompilerKit::RecoveringParser

## Public Interface

#### `parse()`

Starts the parsing process and calls the implementation-defined `recStarter()` method.

#### `syntaxError(const std::string& expected) -> void`

Emits a syntax error, informing the user that a token of a unexpected type was found. For
instances of `RecoveringParser`, the parser goes into recovery.

**Parameters:**

- `expected`: the type of token that was expected.
