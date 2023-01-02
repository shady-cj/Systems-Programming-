#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct person
{
	int id;
	char fname[20];
	char lname[20];
};
int main()
{
	FILE *outfile;

	outfile = fopen("person.dat", "w");
	if (outfile == NULL)
	{
		perror("person.dat");
		exit(1);
	}
	struct person input1 = {1, "rohan", "sharma"};
	struct person input2 = {2, "mahendra", "dhoni"};
	fwrite(&input1, sizeof(struct person), 1, outfile);
	fwrite(&input2, sizeof(struct person), 1, outfile);
	if (fwrite != 0)
		printf("Contents to file written succesfully!\n");
	else
		printf("error writing file !\n");
	fclose(outfile);
	return (0);
}
