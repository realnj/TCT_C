#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <error.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}
int isExistProgram(char *path, char *fileName);

int main(void)
{
	char *path = "./BATCH";
	char *fileName = "BATCH20.EXE";

	if(isExistProgram(path, fileName))
	{
		printf("NOT EXIST\n");
	}
	else
	{
		printf("EXIST\n");
	}
}

int isExistProgram(char *path, char *fileName)
{
	  DIR *dir;
	  struct dirent *ent;
	  int result =1;
	  dir = opendir(path);
	  if (dir != NULL) {

			  /* print all the files and directories within directory */
			  while ((ent = readdir (dir)) != NULL) {
				  //파일명에 .log 포함된 경우
				  	  if(strstr(ent->d_name,".EXE")!= NULL)
				  	  {
				  		  //printf ("%s\n", ent->d_name);
				  		  if(strcmp(fileName, ent->d_name)==0)
				  		  {
				  			  result =0;
				  			  return result;
				  		  }
				  	  }
			  }
			  closedir (dir);
	  } else {
			  /* could not open directory */
			  perror ("");
			  return EXIT_FAILURE;
	  }

	  return result;
}
