#  CompilerKit Introduction

CompilerKit is a small toolkit used to build recursive-descent parsers and compilers. There are
four main parts to CompilerKit, each discussed and documented on their own page:

 * [`Scanner`](scanner/), which is used to build the lexical analysis portion of your compiler;
 * [`Parser`](parser/), and the derived `RecoveringParser`, which are used to build recursive
   descent parsers;
 * [`Sema`](sema/), which provides tools to build the semantic analysis portion of your compiler;
 * and [`Codegen`](codegen/), an artifact generator that lets you emit small programs that run in
   a simplistic virtual machine.
   
There are also some ancillary modules that are used throughout the source:

 * [`Error`](errors/) defines an error type and convenience functions to report them;
 * [`Program`](program-runtime/) defines a simplistic machine language and lets you emit and run
   programs in a basic virtual machine runtime.
