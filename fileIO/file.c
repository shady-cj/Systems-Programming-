#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fin, fout, count;
	char buff[10];

	fin = open("fin", O_RDONLY);
	if (fin < 0)
	{
		perror("fin");
		exit(2);
	}
	fout = open("fout", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fout < 0)
	{
		perror("fout");
		exit(2);
	}
	while ((count = read(fin, buff, 10)) > 0)
	{
		printf("reading %s count - %d\n", buff, count);
		write(fout, buff, count);
	}
	close(fin);
	close(fout);
}
