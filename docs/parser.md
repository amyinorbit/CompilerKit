# AP::CompilerKit::Parser

`Parser`, and the derived `RecoveringParser`, are base classes that provide you with tools to
build a recursive-descent parser. It implements the three functions such parsers require, `have()`,
`match()` and `expect()`, and relies on an instance of [`Scanner`](scanner.html) to provide a
stream of tokens.

`Parser` is also the driving logic of your compiler, and provides an interface to register errors,
both from itself (`Error::Syntax`) and from other parts of your compiler. If your parser is derived
from `Parser`, the first call to `addError()` will also `throw()`. If it is derived from
`RecoveringParser`, then errors will be stored, and the parser will go into recovery.



```c++
include "CompilerKit/Parser::hpp"
using namespace AP::CompilerKit;

class MyParser : public Parser {
public:
    MyParser(Scanner& scanner) : Parser(scanner) {}
    virtual ~MyParser {}
    
    void compile() {
        ...
    }
};
```


## Public Interface

```c++
Parser::Parser(Scanner& scanner)
```

Creates a new instance of `Parser`.

#### Parameters:

- `scanner`: the `Scanner` instance used to generate tokens from the source string.

***

```c++
Parser::errors() const -> const std::vector<Error>&
```

Returns a list of errors that have occurred during parsing.

***

```c++
Parser::isRecovering() const -> bool
```

Returns whether the parser is currently in recovery or not. Will always be `false` for straight
instances of `Parser`.

***

```c++
Parser::addError(const Error& error)
```

Emits a compilation error. Errors can be emitted from anywhere, and are not necessarily syntax
errors. For instances of `Parser`, the error will be thrown after it has been logged.

#### Parameters

- `error`: a new error to log.


## Protected Interface

These methods are available when writing a class that derives from `Parser`.

```c++
Parser::scanner() -> Scanner&
```

Returns the `Scanner` instance attached to `this`.

***

```c++
Parser::current() -> Token
```

Returns the last token lexed by the `Scanner` instance attached to `this`. Equivalent to
calling `parser.scanner().current()`.

***

```c++
Parser::have(const std::string& type) const -> bool
```

Returns whether the last token lexed by the scanner attached to `this` is of a given type.

#### Parameters:

- `type`: the type of token to check for.

***

```c++
Parser::match(const std::string& type) -> bool
```

Checks whether the last token lexed by the scanner attached to `this` is of a given type. If
it is, lexes one more token and returns true, otherwise returns false.

#### Parameters:

- `type`: the type of token to check for.

***

```c++
Parser::expect(const std::string& type) -> bool
```

Checks that the last token lexed by the scanner attached to `this` is of a given type. If it is,
lexes one more token and returns true. If it isn't, emits a syntax error and returns false.

#### Parameters:

- `type`: the type of token to check for.

***

```c++
Parser::syntaxError(const std::string& expected) -> void
```

Emits a syntax error, informing the user that a token of a unexpected type was found.

#### Parameters:

- `expected`: the type of token that was expected.


# AP::CompilerKit::RecoveringParser

