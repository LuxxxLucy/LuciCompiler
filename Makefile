lextest: lexical_test.o lex.yy.o error_message.o utility.o
	cc -g -o lextest lexical_test.o lex.yy.o error_message.o utility.o

lexical_test.o: lexical_test.c tokens.h error_message.h utility.h
	cc -g -c lexical_test.c

error_message.o: error_message.c error_message.h utility.h
	cc -g -c error_message.c

lex.yy.o: lex.yy.c tokens.h error_message.h utility.h
	cc -g -c lex.yy.c

lex.yy.c: syntax.lex
	lex syntax.lex

utility.o: utility.c utility.h
	cc -g -c utility.c

clean:
	rm -f a.out utility.o lexical_test.o lex.yy.o lex.yy.c error_message.o
