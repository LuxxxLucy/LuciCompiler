
OBJS = parser.o lex.o parse_test lexical_test

CC	= g++
# CFLAGS	= -g -Wall -ansi -pedantic
CFLAGS	= -g -w -ansi -pedantic

all:  parser.c parser.o lex.o parse_test lexical_test

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
	$(CC) $(CFLAGS) -c symbol.c -o symbol.o

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
	rm -f ./*.o lex.c lex.yy.c grammar.output grammar.tab.c grammar.tab.h grammar.c tokens.h parse_test lexical_test parser.c
