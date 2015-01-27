#
# Makefile
#
# Exercises
#

all: encrypt decrypt

decrypt: decrypt.c rsa.c rsa.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o decrypt decrypt.c rsa.c -lcs50 -lm

encrypt: encrypt.c rsa.c rsa.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o encrypt encrypt.c rsa.c -lcs50 -lm

test: test.c rsa.c rsa.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o test test.c rsa.c -lcs50 -lm

clean:
	rm -f *.o a.out core encrypt decrypt
