#
# Makefile
# ========
# Simple 16-bit RSA Encryption/Decryption
#
# Imad Salimi
#

all: main

main: main.c rsa.c encrypt.c decrypt.c rsa.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o main main.c encrypt.c decrypt.c rsa.c -lm

decrypt: decrypt.c rsa.c rsa.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o decrypt decrypt.c rsa.c -lm

encrypt: encrypt.c rsa.c rsa.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o encrypt encrypt.c rsa.c -lm

clean:
	rm -f *.o a.out core encrypt decrypt
