#  Semantics

The types documented on this page provide the tools needed to build the semantic analysis portion
of your compiler: [types](#apcompilerkittype), [symbols](#apcompilerkitsymbol) and
[scopes](#apcompilerkitscope), as well as a skeletton from which to derive your semantic analyser,
[Sema](#apcompilerkitsema).

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


#### `static Scope::open() -> Scope*`

Opens a new scope and returns it. If there is already an open scope, makes the new scope the
current one and ensures that the previous scope encloses it.


#### `static Scope::close() -> void`

Closes the current scope if there is one, and make the enclosing scope the currentone. Once a
scope is closed, it cannot be recovered.

#### `static Scope::current() -> Scope*`

Returns the deepest scope currently open, or `nullptr` if none is open.


#### `define(const Token& token, Type type) -> bool`

Defines a new symbol with a given token and type in the current scope. If no other symbol is
defined in the current scope, or any of its enclosing ones, with the same name, returns true.
Otherwise, defines nothing and returns false.

**Parameters:**

- `token`: the token that declares the symbol. `token.text()` must not be the name of another,
  previously-declared symbol.
- `type`: the language type of the new symbol.

#### `isDefined(const std::string& name) const -> bool`

Returns whether the current scope, or any of its enclosing scopes, contains a symbol declared for
the given name.

**Parameters:**

- `name` the name of the symbol to search for.

#### `get(const std::string& name) const -> const Symbol*`

Returns the symbol defined in the current scope or any of its enclosing scopes for a given name,
or `nullptr` if the name doesn't match any symbols.

**Parameters:**

- `name` the name of the symbol to search for.

## AP::CompilerKit::Sema

`Sema` is the class from which your semantic analyser will derive. It provides an API that can be
used to emit various types of semantic errors.

### Public API

#### `Sema(Parser& parser)`

Creates a new instance of `Sema` that uses the given parser to emit and record errors.

**Parameters:**

- `parser`: the `Parser` instance that `this` will use to emit errors.

### Protected API

#### `semanticError(const Token& token, const std::string& message) -> void`

Emits a generic semantic error at a token's location.

**Parameters:**

- `token`: the token at which the error is.
- `message`: the error message to present to the user.


#### `binaryExprError(const Token& op, Type lhs, Type rhs) -> void`

Emits a type mismatch error in a binary expression:

> semantic error at 10:23: invalid operands to binary expression: 'Integer' + 'Boolean'

**Parameters:**

- `op`: the token that represents the operator.
- `lhs`: the type of the left-hand side member of the operation.
- `rhs`: the type of the right-hand side member of the operation.


#### `booleanExprError(const Token& op, Type lhs, Type rhs) -> void`

Emits a type mismatch error in a boolean expression.

> semantic error at 10:23: invalid operands to boolean expression: 'Integer' < 'Boolean'

**Parameters:**

- `op`: the token that represents the operator.
- `lhs`: the type of the left-hand side member of the operation.
- `rhs`: the type of the right-hand side member of the operation.


#### `assignmentError(const Token& var, Type lhs, Type rhs) -> void`

Emits a type mismatch error in a variable assignment

> semantic error at 10:23: assigning variable 'abc' of type 'Integer' from incompatible type
> 'Boolean'

**Parameters:**

- `var`: the token that represents the variable.
- `lhs`: the type of the left-hand side member of the operation (the variable).
- `rhs`: the type of the right-hand side member of the operation (the expression).


#### `undeclaredError(const Token& var) -> void`

Emits an undeclared-variable error.

> use of undeclared variable 'abc'

**Parameters:**

- `var`: the token that references the variable that isn't declared.


#### `redeclaredError(const Token& var) -> void`

Emits a variable re-declaration error.

> redefinition of variable 'abc'

**Parameters:**

- `var`: the token that re-declares the variable.

