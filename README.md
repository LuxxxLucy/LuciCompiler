# **luci**: a simple compiler implement with C-like grammar

> LU Jialin this was intended on demand of a course < Complier Principle > in Zhejiang University

## Syntactic sugars

- all C grammar you need as a normal compiler in C
- nested-function declaration and usage

## reference and prerequisite

Much of the design was learned from the Tiger book < Modern Complier in C >

all code are initialized from the code prototypes from tiger code reposity

To run the program you need to install the following software

1. `flex`
2. `bison`
3. `g++`

### compile the compiler

type the shell command to build

```
make all;
```

or

```
make lucc
```

### grammar and Syntactic sugars

### compile & run your own program.

type the shell code

```
./lucc sourceCode.lucy output.exe
```

then you can run your own C-like code as executable!(congrats!)
