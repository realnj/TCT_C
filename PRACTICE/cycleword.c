#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}

int isDiffWord(char *word, char *new);

int main(void)
{
	int num =0;
	char wordBuf[20][20] ={0,};
	char newBuf[20][20] ={0,};
	int i=0;
	int j=0;
	int index =0;
	int nResult = 0;

	scanf("%d", &num);
	for(i=0; i<num; i++)
	{
		scanf("%s", wordBuf[i]);
	}

	for(i=0; i<num; i++)
	{
		if(i==0)
		{
			memcpy(newBuf[index], wordBuf[i], strlen(wordBuf[i]));
			index++;
		}
		else
		{
			for(j=0; j<index; j++)
			{
				nResult= isDiffWord(wordBuf[i], newBuf[j]);
				if(nResult==1 && j==index-1)
				{
					memcpy(newBuf[index], wordBuf[i], strlen(wordBuf[i]));
					index++;
					break;
				}
				else if(nResult==0)
				{
					printf("//same\n");
					break;
				}
			}


		}

	}

//	for(i=0; i<index; i++)
//	{
//		printf("newBuf[%d] = %s\n", i, newBuf[i]);
//	}
}

int isDiffWord(char *word, char *new)
{
	int i, j=0;
	int len =0;
	int sameFlag = 0;
	if(strlen(word) != strlen(new))
	{
		printf("DIFF LENGTH\n");
		return 1;
	}
	//wodr read
	len = strlen(word);
	for(i=0; i<len; i++)
	{
		if(word[0]==new[i])
		{
			for(j=0; j<len; j++)
			{
				//printf("word[%d] = %c, new[%d] = %c\n", j, word[j], (i+j)%len, new[(i+j)%len]);
				if(word[j] != new[(i+j)%len]) // 1+0, 1+1
				{
					printf("diff \n");
					break;
				}
			}

			if(j==len)
			{
				printf("Same\n");
				return 0;
			}
		}
	}

	if(i==len)
	{
		//printf("diff i==len\n");
		return 1;
	}

}
