/**
 * Imad Salimi
 * rsa.h
 *
 * Functions that help generate rsa keypairs
 */

#ifndef RSA_H
#define RSA_H

// maximum value that genPrime() can generate, to not go as big as 32 bit numbers
#define MAX 46340

typedef struct RSAkey {
	int e;
	int d;
	int n;
} __attribute__ ((__packed__))
RSAkey;

/**
 * Converts a number from decimal base to binary base
 */
void dec_to_bin(int n, int d[], int k);

/**
 * Return the value of y as in: a * x + b * y = gcd(a, b) = d
 */
int extended_euclid(int a, int b);

/**
 * Determines, recursively, the greatest common divisor between a and b
 */
int gcd(int a, int b);

/**
 * Generates an RSA keypair
 */
RSAkey* genRSAkey(void);

/**
 * Generates a random prime number
 */
int genPrime(void);

/**
 * Takes a filename as input and returns its extension if it has any, else NULL
 */
char* getExtension(char* filename);

/**
 * Determines whether a given integer n is prime or not
 */
bool isPrime(int n);

/**
 * compute a^b % c using binary modular exponentiation method
 */
int mod_exp(int a, int b, int n);

/**
 * a function to compute (a^b) % c
 */
int modulo(int a, int b, int c);

#endif
