#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

struct person
{
	int id;
	char fname[20];
	char lname[20];
};
int main()
{
	int fout;

	fout = open("newperson.dat", O_WRONLY | O_CREAT, 0644);
	if (fout < 0)
	{
		perror("person.dat");
		exit(1);
	}
	struct person input1 = {1, "rohan", "sharma"};
	struct person input2 = {2, "mahendra", "dhoni"};
	ssize_t out1 = write(fout, &input1, sizeof(struct person));
	ssize_t out2 = write(fout, &input2, sizeof(struct person));
	printf("out1 - %d , out2 - %d \n", out1, out2);
	close(fout);
	return (0);
}
