#include <stdio.h>

// Prototypes
int encrypt();
int decrypt();

int main()
{
	int choice = 0;

	do
	{
		printf("Choisir opération\n");
        printf("1. Crypter\n");
		printf("2. Décrypter\n");
		printf("3. Quitter\n");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				encrypt();
                break;
            case 2:
                decrypt();
                break;
			default:
				break;
		}
	}
	while(choice != 3);
}
