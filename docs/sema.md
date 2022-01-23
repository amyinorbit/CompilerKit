#  Semantics

## AP::CompilerKit::Type

An enumerator that describes the type of a language object.

- `Type::Integer`: an integral numeric type.
- `Type::Real`: a real numeric type.
- `Type::Boolean`: a boolean type.
- `Type::Invalid`: an invalid type, which can be used to pass errors to `Sema`.

## AP::CompilerKit::Symbol

```c++
struct Symbol {
    Token token;
    Type type;
};
```

A small value type that represents a symbol in a symbol table. The available fields are:

- `token`: the source token that declares the symbol (variable declaration for example).
- `type`: the language type of the symbol.

## AP::CompilerKit::Scope

This class represents declaration scope in the parsed language. Unlike other classes in
CompilerKit, instances of `Scope` are not created by calling the constructor. Instead, the static
functions `open()` and `close()` are provided, and ensure that newly-created scopes are
enclosed by older ones.

Instances of scope are used to declare symbols, and query already-declared symbols.

```c++
static Scope::open() -> Scope*
```

Opens a new scope and returns it. If there is already an open scope, makes the new scope the
current one and ensures that the previous scope encloses it.

***

```c++
static Scope::close() -> void
```

Closes the current scope if there is one, and make the enclosing scope the currentone. Once a
scope is closed, it cannot be recovered.

***

```c++
static Scope::current() -> Scope*
```

Returns the deepest scope currently open, or `nullptr` if none is open.

***

```c++
Scope::define(const Token& token, Type type) -> bool
```

Defines a new symbol with a given token and type in the current scope. If no other symbol is
defined in the current scope, or any of its enclosing ones, with the same name, returns true.
Otherwise, defines nothing and returns false.

**Parameters:**

- `token`: the token that declares the symbol. `token.text()` must not be the name of another,
  previously-declared symbol.
- `type`: the language type of the new symbol.

***

```c++
Scope::isDefined(const std::string& name) const -> bool
```

Returns whether the current scope, or any of its enclosing scopes, contains a symbol declared for
the given name.

**Parameters:**

- `name` the name of the symbol to search for.

***

```c++
Scope::get(const std::string& name) const -> const Symbol*
```

Returns the symbol defined in the current scope or any of its enclosing scopes for a given name,
or `nullptr` if the name doesn't match any symbols.

**Parameters:**

- `name` the name of the symbol to search for.

## AP::CompilerKit::Sema





