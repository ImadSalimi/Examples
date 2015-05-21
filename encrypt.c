/**
 * encrypt.c
 *
 * Encrypts a file using RSA
 */

// standard libraries
#include <cs50.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// header files
#include "rsa.h"

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 3)
	{
		printf("Usage: ./encrypt infile outfile\n");
		return 1;
	}
	
	// open file for reading
	FILE* infile = fopen(argv[1], "r");
	if (infile == NULL)
	{
		printf("Couldn't open %s\n", argv[1]);
		return 1;
	}
	
	// generate RSA keypair
	RSAkey* key = genRSAkey();
	
	// create file signature
	char* ext = getExtension(argv[1]);
	int k = 0;
	if (ext != NULL)
	{
		k = strlen(ext);
	}
	
	FILE* outfile = fopen(argv[2], "w");
	if (outfile == NULL)
	{
		printf("Error while trying to create outfile\n");
		return 2;
	}
	
	// write file's signature
	fwrite(&k, sizeof(int), 1, outfile);
	fwrite(ext, k * sizeof(char), 1, outfile);
	fwrite(key, sizeof(*key), 1, outfile);
	
	printf("Encrypting...\n");
	
	// read through the file character by character, encrypt it,
	// and store the output in the hash file
	uint8_t temp;
	while (fread(&temp, sizeof(uint8_t), 1, infile) == 1)
	{
		int c = mod_exp(temp, key->e, key->n);
		fwrite(&c, sizeof(int), 1, outfile);
	}
	
	printf("The encrypted data is in the file %s!\n", argv[2]);
	
	// free the memory
	free(ext);
	free(key);
	fclose(infile);
	fclose(outfile);
	
    return 0;
}
