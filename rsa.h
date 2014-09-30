/**
 * Imad Salimi
 * rsa.h
 *
 * Functions that help generate rsa keypairs
 */

// maximum value that genPrime() can generate, to not go as big as 32 bit numbers
#define MAX 46340

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
 * Generates a random prime number
 */
int genPrime(void);

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
