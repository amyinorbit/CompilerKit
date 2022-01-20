#  CompilerKit/Scanner

```c++
include "CompilerKit/Scanner.hpp"
using namespace AP::CompilerKit;

class MyScanner: public Scanner {
    ...
    Token lex() override { }
    ...
};
```

`Scanner` is the base class you will use to create your lexical analyser. It provides convenience
methods to advance and consume the source string, and to generate source tokens that can then be
processed by further stages of your compiler. **When implementing a scanner based on `Scanner`, you
must implement at least the `Token lex()` function**.

## Public Interface

These methods can be called on `Token` from anywhere in the source code.

### `Scanner::Scanner(const std::string& source)`

Creates a new scanner that operates on `source`.

### `Scanner::current() const -> Token`

Returns the last token that was lexed by `this`.

### `Scanner::advance() -> char`

Advances the scanner by one more character in the source string, if it is available,
and returns it. If the scanner is at the end of the source string, it will always return the
null character, `\0`.

## Protected Interface

These methods are available when writing a class that derives from `Scanner`.

