/**
 * main.c
 *
 * For testing purposes
 */

// standard libraries
#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// header files
#include "rsa.h"

int main(int argc, char* argv[])
{
	int p, q, e;

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

	do
	{
		e = genPrime();
	}
	while (e <= 1 || e >= phi || gcd(e, phi) != 1);

	// use Euclid's Extender Algorithm to determine d
	int d;

	do
	{
		d = extended_euclid(phi, e);
	}
	while (d == e);

	if (d > phi)
		d = d % phi;

	if (d < 0)
		d = d + phi;

	printf("\nGenerated key pair:\n");
	printf("Public key: (%d, %d)\n", e, n);
	printf("Private key: (%d, %d)\n", (int) d, n);

	// prompt user for input
	printf("\nMessage to encrypt: ");
	string plain = GetString();
	int l = strlen(plain);
	int cipher[l];

	printf("Encrypting...\n");
	for (int i = 0; i < l; i++)
	{
		cipher[i] = mod_exp(plain[i], e, n);
		printf("%d", cipher[i]);
	}
	printf("\n");

    return 0;
}
