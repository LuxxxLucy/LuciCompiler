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
3. `gcc`

### compile the compiler

type the shell command to build

```
cmake .
make lucc;
```

or

```
make lucc
```

### grammar and Syntactic sugars

### compile & run your own program.

type the shell code

```
./lucc sourceCode.lucy
```

sample

```
int i=3;
int a=4;
a=i+1;
```

the IR tree and fragments are like

```
SEQ(
      MOVE(
          TEMP t100
          CONST 3
      )
      MOVE(
          TEMP t102
          CONST 4
      )
      MOVE(
          TEMP t102
          BINOP(PLUS
              TEMP t100
              CONST 1
          )
      )
  )
```

and I even accomplish the print function using a special trick(which would be presented later in the class). It allows me to even

then you can run your own C-like code as executable!(congrats!)
