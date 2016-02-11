/**
 * encrypt.c
 *
 * Encrypts a file using RSA
 */

// standard libraries
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// header files
#include "rsa.h"

int encrypt()
{
	// Read in filename
	char filename[100], out[100];
    printf("Fichier a crypter: ");
	scanf("%s", filename);
	printf("Nom du fichier de sortie: ");
	scanf("%s", out);
	
	// open file for reading
	FILE* infile = fopen(filename, "r");
	if (infile == NULL)
	{
		printf("Couldn't open %s\n", filename);
		return 1;
	}
	
	// generate RSA keypair
	RSAkey* key = genRSAkey();
	
	// create file signature
	char* ext = getExtension(filename);
	int k = 0;
	if (ext != NULL)
	{
		k = strlen(ext);
	}
	
	FILE* outfile = fopen(out, "w");
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
	
	printf("The encrypted data is in the file %s!\n", out);
	
	// free the memory
	free(ext);
	free(key);
	fclose(infile);
	fclose(outfile);
	
    return 0;
}
