/**
 * Imad Salimi
 * rsa.c
 *
 * Functions that help generate rsa keypairs
 */

// standard libraries
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// header files
#include "rsa.h"

/**
 * Converts a number from decimal base to binary base
 */
void dec_to_bin(int n, int d[], int k)
{
	int t;
	int pos = 0, end = k - 1, i;
	
	for (i = 0; i < k; i++)
		d[i] = 0;
	
	while(n > 0)
	{
		d[pos] = n % 2;
		pos++;
		n = n / 2;
	}
	
	// reverse array's elements
	int c;
	for (c = 0; c < k/2; c++)
	{
		t = d[c];
		d[c]   = d[end];
		d[end] = t;

		end--;
	}
}

/**
 * Calculates a * x + b * y = gcd(a, b) = d
 * Author: Pate Williams (c) 1997
 */
int extended_euclid(int a, int b)
{
    int prevx = 1, x = 0;
    int prevy = 0, y = 1;
    int q, r;

    while (b)
    {
        q = a / b;
        r = a % b;

        int tmp = x;
        x = prevx - q * x;
        prevx = tmp;

        tmp = y;
        y = prevy - q * y;
        prevy = tmp;

        a = b;
        b = r;
    }
    
    return prevy;
}

/**
 * Determines, recursively, the greatest common divisor between a and b
 */
int gcd(int a, int b)
{
	if (a == 0)
		return b;
		
	return gcd(b % a, a);
}

/**
 * Generates an RSA keypair
 */
RSAkey* genRSAkey(void)
{
	int p, q, e, d;

	srand(time(NULL));

	// generate pseudo-random different prime numbers
	do
	{
		p = genPrime();
		q = genPrime();
	}
	while (p == q);

	// modulus
	int n = p * q;
	// Euler's totient
	int phi = (p - 1) * (q - 1);

	// generate public key exponent
	do
	{
		e = genPrime();
	}
	while (e <= 1 || e >= phi || gcd(e, phi) != 1);

	// use Euclid's Extender Algorithm to determine d
	do
	{
		d = extended_euclid(phi, e);
	}
	while (d == e);

	// validate d
	if (d > phi)
		d = d % phi;
	if (d < 0)
		d = d + phi;
		
	RSAkey* pair = malloc(sizeof(*pair));
	pair->e = e;
	pair->d = d;
	pair->n = n;
	
	return pair;
}

/**
 * Generates a random prime number
 */
int genPrime(void)
{
	int r;
	
	// generate random numbers until a prime number is found
	do
	{
		r = rand() % MAX + 2;
	}
	while (!isPrime(r));
	
	return r;
}

/**
 * Takes a filename as input and returns its extension if it has any, else NULL
 */
char* getExtension(char* filename)
{
	int l = strlen(filename);
	int k = 0, i = 0, j = 0;
	
	// count length of the extension
	for (i = l - 1; filename[i] != '.' && i >= 0; i--)
	{
		k++;
	}
	
	// if no '.' was found, file has no extension
	if (i == -1)
	{
		return NULL;
	}
	
	// store extension in a char* and return it
	char* ext = malloc(sizeof(char) * k);
	for (j = 0; j < k; j++)
	{
		ext[j] = filename[l - k + j];
	}
	
	return ext;
}

/**
 * Determines naively whether a given integer n is prime or not
 */
bool isPrime(int n)
{
	// handles basic cases
	if (n == 0 || n == 1)
		return false;
	
	// check if there's a number from 2 to sqrt(n) that divides n, in which case
	// n wouldn't be prime
	int i;
	for (i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			return false;
	}
	
	return true;
}

/**
 * compute a^b % c using binary modular exponentiation method
 */
int mod_exp(int a, int e, int n)
{
	int k = 32;
	int exp[k];
	dec_to_bin(e, exp, k);

	long long base = a, result = 1;
	
	while (e > 0)
	{
		if (exp[k - 1] == 1)
			result = (result * base) % n;
		
		e >>= 1;
		dec_to_bin(e, exp, k);
		base = (base * base) % n;
	}
	
	return result;
}

/**
 * a function to compute (a^b) % c
 */
int modulo(int a, int b, int c)
{
    // res is kept as int because intermediate results might overflow in "int"
	long long res = 1;

	int i;
	for(i = 0; i < b; i++)
	{
		res *= a;
		res %= c; // this step is valid because (a*b)%c = ((a%c)*(b%c))%c
	}
	
	return res % c;
}
