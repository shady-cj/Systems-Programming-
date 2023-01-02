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
	FILE *infile;

	infile = fopen("newperson.dat", "r");
	if (infile == NULL)
	{
		perror("person.dat");
		exit(1);
	}
	struct person input;
	while (fread(&input, sizeof(struct person), 1, infile))
		printf("%d - %s %s \n", input.id, input.fname, input.lname);

	fclose(infile);
	return (0);
}
