#  CompilerKit Introduction

CompilerKit is a small toolkit used to build recursive-descent parsers and compilers. There are
four main parts to CompilerKit, each discussed and documented on their own page:

 * [`Scanner`](docs/scanner.html), which is used to build the lexical analysis portion of your compiler;
 * [`Parser`](docs/parser.html), and the derived `RecoveringParser`, which are used to build recursive
   descent parsers;
 * [`Sema`](docs/sema.html), which provides tools to build the semantic analysis portion of your compiler;
 * and [`Codegen`](docs/codegen.html), an artifact generator that lets you emit small programs that run in
   a simplistic virtual machine.
   
There are also some ancillary modules that are used throughout the source:

 * [`Token`](docs/token.html) defines a source token type, which encodes text, a type and a location;
 * [`Error`](docs/errors.html) defines an error type and convenience functions to report them;
 * [`Program`](docs/program-runtime.html) defines a simplistic machine language and lets you emit and run
   programs in a basic virtual machine runtime.
