#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}

typedef struct tran
{
	char sender[5];
	char receiver[5];
	char fare[4];
}TRAN;

typedef struct block{
	char currHash[8];
	char prevHash[8];
	char tranHash[8];
	TRAN stTran[20];
	int tranCnt;
}BLOCK;

BLOCK stBlock[100];
BLOCK stBlockTran[100];
int nTotalCnt;

// 14:45
void printHashBlockTran();
void printHashTran();
int writeFileBlockInfo(int pos);
int readFile();
int main(void)
{
	int pos =0;
	readFile();
//	printHashTran();
//	sortBlock();
	pos = findLastTran();
	writeFileBlockInfo(pos);
}

int writeFileBlockInfo(int pos)
{
	FILE *fp;
	int i=0;
	fp = fopen("./OUTFILE/result.txt", "w");

	fprintf(fp, "%.8s#%.8s#%.8s\n", stBlock[pos].currHash, stBlock[pos].prevHash, stBlock[pos].tranHash);

	for(i=0; i<stBlock[pos].tranCnt; i++)
	{
		if(i==stBlock[pos].tranCnt-1)
		{
			fprintf(fp, "%.5s,%.5s,%.4s", stBlock[pos].stTran[i].sender, stBlock[pos].stTran[i].receiver, stBlock[pos].stTran[i].fare);
		}
		else
		{
			fprintf(fp, "%.5s,%.5s,%.4s#", stBlock[pos].stTran[i].sender, stBlock[pos].stTran[i].receiver, stBlock[pos].stTran[i].fare);
		}
	}

	if(fp)
	{
		fclose(fp);
	}
}

int sortBlock()
{
	int i=0;
	int j=0;
	char hash[9] ={0,};

	memcpy(hash, "XXXXXXXX", 8);

	while(1)
	{
		for(i=0; i<nTotalCnt; i++)
		{
			if(memcmp(stBlock[i].prevHash, hash, 8)==0)
			{
				stBlockTran[j] = stBlock[i];
				memcpy(hash, stBlock[i].currHash, 8);
				j++;
				break;
			}
		}

		if(j==nTotalCnt)
		{
			break;
		}
	}

	return 0;
}

int findLastTran()
{
	int i=0;
	int j=0;
	int lastPos = 0;

	for(i=0; i<nTotalCnt; i++)
	{
		for(j=0; j<nTotalCnt; j++)
		{
			if(memcmp(stBlock[i].currHash, stBlock[j].prevHash, sizeof(stBlock[j].prevHash))==0)
			{
				break;
			}
		}
		if(j==nTotalCnt)
		{
			lastPos = i;
		}
	}
	return lastPos;
}

int readFile()
{
	FILE *fp;
	char buf[255]={0,};
	char tranBuf[20][100] ={0,};
	int lineCount =0;
	char *token;
	int nTranCnt =0;
	int i=0;
	fp= fopen("./INFILE/chain.txt", "r");

	while(fgets(buf, sizeof(buf), fp) != NULL)
	{
		if(lineCount%2==0)
		{
			nTranCnt= 0;
			token = strtok(buf, "#");
			memcpy(stBlock[nTotalCnt].currHash, token, strlen(token));
			token = strtok(NULL, "#");
			memcpy(stBlock[nTotalCnt].prevHash, token, strlen(token));
			token = strtok(NULL, "#");
			memcpy(stBlock[nTotalCnt].tranHash, token, strlen(token));
		}
		else
		{
			token = strtok(buf, "#");

			while(token != NULL)
			{
				memcpy(tranBuf[nTranCnt], token, strlen(token));
//				printf("tranBuf[%d] = %s\n", nTranCnt, tranBuf[nTranCnt]);
				token = strtok(NULL, "#");
				nTranCnt++;
			}

			stBlock[nTotalCnt].tranCnt = nTranCnt;

			for(i=0; i<nTranCnt; i++)
			{
				memcpy(&stBlock[nTotalCnt].stTran[i], tranBuf[i], sizeof(TRAN));
			}

			nTotalCnt++;
		}

		lineCount++;
	}


	if(fp)
	{
		fclose(fp);
	}

	return 0;
}

void printHashTran()
{
	int i=0;

	for(i=0; i<nTotalCnt; i++)
	{
		printf("===============================\n");
		printf("stHash[%d].currHash = %.8s\n", i, stBlock[i].currHash);
		printf("stHash[%d].prevHash = %.8s\n", i, stBlock[i].prevHash);
		printf("stHash[%d].tranHash = %.8s\n", i, stBlock[i].tranHash);

		for(int j =0; j<stBlock[i].tranCnt; j++)
		{
			printf("stTran[%d].sender = %.5s\n", j, stBlock[i].stTran[j].sender);
			printf("stTran[%d].receiver = %.5s\n", j, stBlock[i].stTran[j].receiver);
			printf("stTran[%d].fare = %.4s\n", j, stBlock[i].stTran[j].fare);
		}
	}

}

