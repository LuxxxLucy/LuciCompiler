# **luci**: a simple compiler implement with C-like grammar

> LU Jialin this was intended on demand of a course < Complier Principle > in Zhejiang University

> According to the design of C99 standard design and implement the compiler to generate the IR tree.

按照C语言写了编译器。 完成的有声明，定义，while if等loop。而且函数可嵌套定义。

也做了生成机器码的部分。而且我想到了一种方法直接可以生成在自己的任何机器上直接调用的方法。但是这个IR树到中间代码的部分还没有写完。为了惊喜，会在展示的时候直接演示。

真的我觉得我这个IR树到机器码的方法超级牛逼。等写完了一起再传一份。

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

there are only 1 shift and reduce error. designed according to the c99 standard.

```
parser.y: conflicts: 1 shift/reduce
```

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
