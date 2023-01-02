#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

/**
 * main - This function takes command line flag a using
 * getopt and displays the entry of a directory showing hidden
 * files or not.
 * @argv: command line argument vectors
 * @argc: Command line argument counts
 * Return: The Program output.
 */

int main(int argc, char *argv[])
{
	char c;
	int allflag = 0, long_format = 0;
	DIR *d;
	struct stat sb;
	struct dirent *info;
	struct passwd *get_user_info;
	struct group *group_name;
	struct tm *access_time;
	char *filetype[] = {"?", "p", "c",
		"?", "d", "?", "b",
		"?", "-", "?", "l", "unknown", "s" };
	char *months[] = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec"
	};

	while ((c = getopt(argc, argv, "al")) != EOF)
	{
		switch (c)
		{
			case 'a':
				allflag = 1;
				break;
			case 'l':
				long_format = 1;
				break;
			case '?':
				fprintf(stderr, "invalid option %c\n", optopt);
				break;
		}
	}
	argv += optind;
	argc -= optind;
	if (argc == 0)
	{
		fprintf(stderr, "Error: Directory path required\n");
		exit(1);
	}
	chdir(argv[0]);
	d = opendir(".");
	while (info = readdir(d))
	{
		if (info->d_name[0] == '.' && allflag == 0)
			continue;
		if (long_format)
		{
			stat(info->d_name, &sb);
			printf("%s", filetype[(sb.st_mode >> 12) &017]);
			printf("%c%c%c%c%c%c%c%c%c ",
				(sb.st_mode & S_IRUSR) ? 'r' : '-',
				(sb.st_mode & S_IWUSR) ? 'w' : '-',
				(sb.st_mode & S_IXUSR) ? 'x' : '-',
				(sb.st_mode & S_IRGRP) ? 'r' : '-',
				(sb.st_mode & S_IWGRP) ? 'w' : '-',
				(sb.st_mode & S_IXGRP) ? 'x' : '-',
				(sb.st_mode & S_IROTH) ? 'r' : '-',
				(sb.st_mode & S_IWOTH) ? 'w' : '-',
				(sb.st_mode & S_IXOTH) ? 'x' : '-'
			);
			get_user_info = getpwuid(sb.st_uid);
			group_name = getgrgid(sb.st_gid);
			printf("%ld %s %s ", sb.st_nlink, get_user_info->pw_name, group_name->gr_name);
			printf("%ld ", sb.st_size);
			access_time = localtime(&sb.st_mtime);
			printf("%s  ", months[access_time->tm_mon]);
			printf("%d ", access_time->tm_mday);
			printf("%d:%d ", access_time->tm_hour, access_time->tm_min);
			printf("%s\n",info->d_name);
		}
		else
		{
			printf("%s  ", info->d_name);
		}
	}
	if (!long_format)
		printf("\n");
	return (0);
}
