#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fin, fout, count;
	char buff[10];
	sprintf(buff, "hello");
	printf("%s\n", buff);
	sprintf(buff, "me");
	printf("%s\n", buff);
}
