#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

void getFullPath(char *path, char *name, char *fullpath);
static size_t get_file_size (const char * file_name);
int getLineCount(int nStartLine);
int scanDirectory(char *inputPath, char *fileName, char *fullpath);

int main()
{
	char *path = "./BIGFILE";
	char *fileName = "ABCDFILE.TXT";
	char fullpath[1024] ={0,};
	int fileSize=0;

	getFullPath(path, fileName, fullpath);
	printf("fullpath = %s\n", fullpath);

	fileSize = get_file_size(fullpath);
	printf("fileSize = %d\n", fileSize);

	int total_count = getLineCount(1);
	printf("total_count = %d\n", total_count);

}

void getFullPath(char *path, char *name, char *fullpath)
{
	DIR *dir;
	struct stat st;
	char newPath[1024] ={0,};
	struct dirent *ent;
	dir = opendir(path);

	if(dir != NULL)
	{
		while((ent = readdir(dir)) != NULL)
		{
			lstat(ent->d_name, &st);
			if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0)
				continue;

			if(ent->d_type != 4)
			{
				printf("file[%s]\n", ent->d_name);
				if(strcmp(ent->d_name, name)==0)
				{
					sprintf(fullpath, "%s/%s", path, ent->d_name);
					break;
				}
			}
			else
			{
				printf("dir[%s]\n", ent->d_name);
				sprintf(newPath, "%s/%s", path, ent->d_name);
				getFullPath(newPath, name, fullpath);
			}
		}
		closedir(dir);
	}
	else
	{
		return NULL;
	}
}

static size_t get_file_size (const char * file_name)
{
	struct stat sb;
	if (stat (file_name, & sb) != 0)
	{
		fprintf (stderr, "'stat' failed for '%s': %s.\n", file_name, strerror (errno));
		exit (EXIT_FAILURE);
	}
	return sb.st_size;
}

int getLineCount(int nStartLine)
{
	char fullPath[1024] ={0,};
	char line[1024] ={0,};
	char prevLine[1024]={0,};
	int count = 0;
	int nLineCount =0;
	char *line_p;

	getFullPath("BIGFILE", "ABCDFILE.TXT", fullPath);
	FILE *fp = fopen(fullPath, "r");

	if(fp != NULL)
	{
		while(!feof(fp))
		{
			fgets(line, sizeof(line), fp);

			if(nStartLine <= nLineCount+1)
			{
				if((line_p = strchr(line, '\r')) != NULL)
					*line_p = '\0';
				if((line_p = strchr(line, '\n')) != NULL)
					*line_p = '\0';
				if(strcmp(line, prevLine)!= 0)
					count++;

				memset(prevLine, 0x00, sizeof(prevLine));
				memcpy(prevLine, line, sizeof(line));
			}
			nLineCount++;
		}
	}

	fclose(fp);
	return count;
}


int scanDirectory(char *inputPath, char *fileName, char *fullpath)
{
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	struct stat statBuf;
	char pathBuf[100]={0,};

	if( (dir = opendir(inputPath)) == NULL)
	{
		printf("cannot open directory\n");
		return -1;
	}

	while((entry=readdir(dir))!= NULL)
	{
		if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0)
		{
			continue;
		}

		sprintf(pathBuf, "%s/%s", inputPath, entry->d_name);
		stat(pathBuf, &statBuf);

		if(S_ISDIR(statBuf.st_mode))
		{
			printf("1. Directory : %s\n", entry->d_name);
			scanDirectory(pathBuf, fileName, fullpath);
		}
		else if(S_ISREG(statBuf.st_mode))
		{
			printf("2. FILE : %s\n", entry->d_name);
			if(strcmp(entry->d_name, fileName)==0)
			{
				printf("Find File\n");
				memcpy(fullpath, pathBuf, strlen(pathBuf));
			}
		}

	}

	closedir(dir);
	return 0;

}

