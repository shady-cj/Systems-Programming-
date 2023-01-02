#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>


/* we define a buffer big enough to read 100 events
 * in one go */
#define BUFSIZE (100 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main()
{
	FILE *fconfig; /* descriptor for config file*/
	FILE *fout; /* Descriptor for output file */

	char watchname[PATH_MAX];
	struct stat sb;
	int notifyfd, watchfd;
	char eventbuf[BUFSIZE]; /* events are read into here */
	int n;
	char *p;
	struct inotify_event *event;

	/* Here we hold the names of the watched files, indexed by the watch descriptor */;
	char watchednames[100][NAME_MAX+1];
	notifyfd = inotify_init();

	/*open the config file of file to be watched*/
	
	if ((fconfig = fopen("monitor.conf","r")) == NULL)
	{
		printf("unable to open file; giving up!\n");
		exit(1);
	}
	/* Read all watched file names from file */
	while (fgets(watchname, PATH_MAX, fconfig) != NULL)
	{
		/* GET RID OF THE NEW LINE */
		watchname[strlen(watchname) - 1] = '\0';

		if (stat(watchname, &sb) < 0)
		{
			printf("cannot stat %s, ignored\n", watchname);
			continue;
		}
		if (S_ISREG(sb.st_mode))
		{
			/* Regular file so add to watch list */
			if ((watchfd = inotify_add_watch(notifyfd, watchname, IN_MODIFY | IN_DELETE_SELF)) < 0)
			{
				printf("error adding watch for %s\n", watchname);
			}
			else
			{
				printf("added %s to watch list on descriptor %d\n", watchname, watchfd);
				strcpy(watchednames[watchfd], watchname);
			}
		}
		else
		{
			/* Not a regular file prolly a directory*/
			printf("%s is not a regular file, ignored\n", watchname);
		}
	}

	/*
	 * All our watches are in place so just read and report events */
	fout = fopen("monitor.out", "a");

	while (1)
	{
		n = read(notifyfd, eventbuf, BUFSIZE);
		/**
		 * read over all events and report them. this is 
		 * a little tricky because the event records are not of fixed length */
		for (p = eventbuf; p < eventbuf + n;)
		{
			event = (struct inotify_event *) p;
		
			p += sizeof(struct inotify_event) + event->len;
			/* Display the event */
			if (event->mask & IN_MODIFY) 
				fprintf(fout, "%s was modified\n", watchednames[event->wd]);
			if (event->mask & IN_DELETE_SELF)
				fprintf(fout, "%s was deleted\n", watchednames[event->wd]);
			fflush(fout);
		}
	}

}
