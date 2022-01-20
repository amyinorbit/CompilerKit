#  CompilerKit/Scanner

```c++
include "CompilerKit/Scanner::hpp"
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

***

```c++
Scanner::Scanner(const std::string& source)
```

Creates a new scanner that operates on `source`.

***

```c++
Scanner::current() const -> Token
```

Returns the last token that was lexed by `this`.

***


```c++
Scanner::advance() -> char
```

Advances the scanner by one more character in the source string, if it is available,
and returns it. If the scanner is at the end of the source string, it will always return the
null character, `\0`.

***


## Protected Interface

These methods are available when writing a class that derives from `Scanner`.

```c++
Scanner::startToken() -> void
```

Marks the current position in the source text as the start of a token. Use in combination with
`makeToken()`.

***


```c++
Scanner::peek() -> char
```

Returns the character in the source string that `this` is currently at.

***


```c++
Scanner::line() const -> int
```

Returns the line number in the source string that `this` is currently at.

***


```c++
Scanner::column() const -> int
```

Returns the line number in the source string that `this` is currently at.

***


```c++
Scanner::makeToken(const std::string& type) -> Token
```

Creates a new token of a given type, assigns it as the current token, and returns it.

***


#### Parameters:
 - `type`: the type of token to create. See [`Token`](token.html) for existing types.

***


```c++
Scanner::makeToken(const std::string& type, const std::string& text) -> Token
```

Creates a new token of a given type, assigns it as the current token, and returns it. This
methods also lets your provide text for the token, and should be used for tokens where the type
and text are different (number literals, non-keyword identifiers, etc).

#### Parameters:
 - `type`: the type of token to create. See [`Token`](token.html) for existing types.
 - `text`: the text of the new token.

***


```c++
Scanner::updateTokenStart() -> void
```

Sets the point in the source at which a new token starts. This is called once you've consumed
any whitespace before a token.
