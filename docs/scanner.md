#  CompilerKit::Scanner

`Scanner` is the base class you will use to create your lexical analyser. It provides convenience
methods to advance and consume the source string, and to generate source tokens that can then be
processed by further stages of your compiler. **When implementing a scanner based on `Scanner`, you
must implement at least the `Token lex()` function**.


```c++
include "CompilerKit/Scanner::hpp"
using namespace CompilerKit;

class MyScanner : public Scanner {
public:

    MyScanner(std::istream& source) : Scanner(source) {}
    virtual ~MyScanner() {}
    
    Token lex() override {
        return makeToken(Token::Invalid);
    }
};
```

## Public Interface

These methods can be called on `Parser` from anywhere in the source code.

#### `Scanner::Scanner(const std::istream& source)`

Creates a new scanner that operates on `source`.

**Parameters:**

- `source`: the input stream to read characters from.

#### `current() const -> Token`

Returns the last token that was lexed by `this`.

### `end() const -> bool`

Returns whether the scanner is at the end of its input stream.

***


## Protected Interface

These methods are available when writing a class that derives from `Scanner`.


#### `advance() -> char`

Advances the scanner by one more character in the source string, if it is available,
and returns it. If the scanner is at the end of the source string, it will always return the
null character, `\0`.

#### `updateTokenStart() -> void`

Sets the point in the source at which a new token starts. This is called once you've consumed
any whitespace before a token.

#### `peek() -> char`

Returns the character in the source string that `this` is currently at.

#### `line() const -> int`

Returns the line number in the source string that `this` is currently at.

#### `column() const -> int`

Returns the line number in the source string that `this` is currently at.

#### `makeToken(const std::string& type) -> Token`

Creates a new token of a given type, assigns it as the current token, and returns it.

**Parameters:**

 - `type`: the type of token to create. See [`Token`](token.html) for existing types.

#### `makeToken(const std::string& type, const std::string& text) -> Token`

Creates a new token of a given type, assigns it as the current token, and returns it. This
methods also lets your provide text for the token, and should be used for tokens where the type
and text are different (number literals, non-keyword identifiers, etc).

**Parameters:**

 - `type`: the type of token to create. See [`Token`](token.html) for existing types.
 - `text`: the text of the new token.

