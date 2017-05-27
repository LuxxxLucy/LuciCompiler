CC	= g++
# CFLAGS	= -g -Wall -ansi -pedantic
CFLAGS	= -g -w -ansi -pedantic

all:  parser.c parser.o lex.o parse_test lexical_test main lucc

lucc: parse_test.o parser.o lex.o error_message.o utility.o abstract_syntax.o prabsyn.o types.o tree.o temp.o main.o
	# $(CC) $(CFLAGS) translateBack.c -o lucc
	@echo "building lucc (lucy's c complier) make not ready please wait..."

main: parse_test.o parser.o lex.o error_message.o utility.o abstract_syntax.o prabsyn.o types.o tree.o temp.o main.o translateBack.o semant.o env.o printtree.o
	$(CC) $(CFLAGS)  main.o parser.o lex.o error_message.o utility.o abstract_syntax.o  symbol.o table.o prabsyn.o  temp.o tree.o translateBack.o types.o semant.o  env.o printtree.o -o main -ll

main.o: parse_test.o parser.o lex.o error_message.o utility.o abstract_syntax.o prabsyn.o types.o tree.o temp.o
	$(CC) $(CFLAGS) -c main.c parser.o lex.o error_message.o utility.o abstract_syntax.o  symbol.o table.o prabsyn.o  temp.o tree.o -o main.o -ll

translateBack.o:
	$(CC) $(CFLAGS) -c translateBack.c parser.o lex.o error_message.o utility.o abstract_syntax.o  symbol.o table.o prabsyn.o  temp.o tree.o -o translateBack.o -ll

semant.o:  utility.o tokens.h symbol.o abstract_syntax.o error_message.o temp.o tree.o printtree.o table.o types.o frame.o env.o
	$(CC) $(CFLAGS) -c semant.c error_message.o utility.o abstract_syntax.o types.o symbol.o table.o printtree.o  temp.o tree.o types.o  frame.o env.o -o semant.o

frame.o: utility.o temp.o tree.o
	$(CC) $(CFLAGS) -c frame.c utility.o temp.o tree.o types.o -o frame.o

env.o: table.o
	$(CC) $(CFLAGS) -c env.c table.o types.o -o env.o


printtree.o: utility.o symbol.o temp.o tree.o
	$(CC) $(CFLAGS) -c printtree.c utility.o table.o symbol.o temp.o tree.o -o printtree.o

types.o: utility.o symbol.o
	$(CC) $(CFLAGS) -c types.c utility.o symbol.o -o types.o

temp.o: utility.o symbol.o table.o
	$(CC) $(CFLAGS) -c temp.c utility.o symbol.o table.o -o temp.o

tree.o: temp.o types.o utility.o
	$(CC) $(CFLAGS) -c tree.c  utility.o temp.o symbol.o -o tree.o


error_message.o: error_message.c error_message.h utility.h
	$(CC) $(CFLAGS) -c error_message.c -o error_message.o

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c -o utility.o

tokens.h: parser.c

parser.c: grammar.y
	@echo "start building the parser using BISON"
	bison -dv grammar.y
	cp grammar.tab.c parser.c
	@echo "...construct tokens.h (prepare for robust flex issue) "
	cmp -s grammar.tab.h tokens.h || cp grammar.tab.h tokens.h

parser.o: parser.c	lex.o error_message.o utility.o
	$(CC) $(CFLAGS) -c parser.c lex.o error_message.o utility.o -o parser.o
	@echo "...parser.o executable okay"

parse_test.o: parse_test.c error_message.h utility.h
	$(CC) $(CFLAGS) -c parse_test.c -o parse_test.o

parse_test: parse_test.o parser.o lex.o error_message.o utility.o abstract_syntax.o prabsyn.o
	$(CC) $(CFLAGS) parse_test.o parser.o lex.o error_message.o utility.o abstract_syntax.o  symbol.o table.o prabsyn.o -o parse_test -ll

prabsyn.o: abstract_syntax.o
	$(CC) $(CFLAGS) -c prabsyn.c -o prabsyn.o


abstract_syntax.o: abstract_syntax.h symbol.h utility.h symbol.o
	$(CC) $(CFLAGS) -c abstract_syntax.c  symbol.o -o abstract_syntax.o

symbol.o: table.o
	$(CC) $(CFLAGS) -c symbol.c utility.o -o symbol.o

table.o:
	$(CC) $(CFLAGS) -c table.c -o table.o

lex.c: syntax.lex parser.c tokens.h
	@echo "start building lexical analysis tool using FLEX"
	flex syntax.lex
	@echo "lexical program okay"
	cp lex.yy.c lex.c
	rm lex.yy.c

lex.o: lex.c tokens.h error_message.h utility.h parser.c
	$(CC) $(CFLAGS) -c lex.c -o lex.o

lexical_test.o: lexical_test.c tokens.h error_message.h utility.h
	$(CC) $(CFLAGS) -c lexical_test.c

lexical_test: lexical_test.o lex.o error_message.o utility.o
	$(CC) $(CFLAGS) -o lextest lexical_test.o lex.o error_message.o utility.o -o lexical_test

.PHONY: clean
clean:
	rm -fr ./*.o lex.c lex.yy.c grammar.output grammar.tab.c grammar.tab.h grammar.c tokens.h parse_test lexical_test parser.c ./main ./lucc *.dSYM
