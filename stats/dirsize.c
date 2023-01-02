
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>


int main()
{
	DIR *d;
	struct dirent *info; /* A directory entry */
	struct stat sb;  /* stat buffer */
	size_t total = 0;

	d = opendir(".");

	while ((info = readdir(d)) != NULL)
	{
		stat(info->d_name, &sb);
		total += sb.st_size;
	}
	closedir(d);
	printf("total size = %u\n", total);
}
