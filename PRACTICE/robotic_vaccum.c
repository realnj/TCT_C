#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * �κ� û�ұ�� ������ ���� �۵��Ѵ�.
1.���� ��ġ�� û���Ѵ�.
2.���� ��ġ���� ���� ������ �������� ���ʹ������ ���ʴ�� Ž���� �����Ѵ�.
   1.���� ���⿡ ���� û������ ���� ������ �����Ѵٸ�, �� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ �����Ѵ�.
2.���� ���⿡ û���� ������ ���ٸ�, �� �������� ȸ���ϰ� 2������ ���ư���.
3.�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���� ��쿡��, �ٶ󺸴� ������ ������ ä�� �� ĭ ������ �ϰ� 2������ ���ư���.
4.�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���̸鼭, ���� ������ ���̶� ������ �� �� ���� ��쿡�� �۵��� �����.

�κ� û�ұ�� �̹� û�ҵǾ��ִ� ĭ�� �� û������ ������, ���� ����� �� ����.

ù° �ٿ� ���� ũ�� N�� ���� ũ�� M�� �־�����. (3 �� N, M �� 50)

��° �ٿ� �κ� û�ұⰡ �ִ� ĭ�� ��ǥ (r, c)�� �ٶ󺸴� ���� d�� �־�����.
d�� 0�� ��쿡�� ������, 1�� ��쿡�� ������, 2�� ��쿡�� ������, 3�� ��쿡�� ������ �ٶ󺸰� �ִ� ���̴�.

��° �ٺ��� N���� �ٿ� ����� ���°� ���ʺ��� ���� �������, �� ���� ���ʺ��� ���� ������� �־�����.
�� ĭ�� 0, ���� 1�� �־�����. ����� ��� �ܰ��� ���̴�.

�κ� û�ұⰡ �ִ� ĭ�� ���´� �׻� �� ĭ�̴�.

 *
 */

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
 	setvbuf(stdout,NULL, _IONBF,0);
 	setvbuf(stderr,NULL, _IONBF,0);
}
int changeDir(int dir);
int moveBack(int array[][10], int*posX, int *posY, int dir);
int moveDir(int array[][10], int*posX, int *posY, int dir);

int main(void)
{
	int array[11][10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
									1, 0, 0, 0, 1, 1, 1, 1, 0, 1,
									1, 0, 0, 1, 1, 0, 0, 0, 0, 1,
									1, 0, 1, 1, 0, 0, 0, 0, 0, 1,
									1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
									1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
									1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
									1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
									1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1	};

	int row = 11;
	int col =10;
	int posX = 7;
	int posY = 4;
	int i =0;
	int count =0;
	int dir  =0; // �� 0, �� 1, �� 2, �� 3
	int moveYn =0;


	while(1)
	{

		if(array[posX][posY]==0)
		{
			array[posX][posY] =2;
			count++;
		}

		for(i=0; i<4; i++)
		{
			 dir = changeDir(dir);
			 moveYn = moveDir(array, &posX, &posY, dir);
			 if(moveYn ==0)
			 {
				 break;
			 }
		}

		if(i==4)
		{
			moveYn = moveBack(array, &posX, &posY, dir);
			if(moveYn==1)
			{
				break;
			}
		}
	}

	printf("//////////count = %d\n", count);

}

int changeDir(int dir)
{
	int changeDir =0;
	if(dir ==0) // ����
	{
		changeDir = 3; // ����
	}
	else if(dir ==1) // ����
	{
		changeDir =0;
	}
	else if(dir ==2) // ����
	{
		changeDir = 1;
	}
	else if(dir ==3) // ����
	{
		changeDir =2;
	}

	return changeDir;
}
int moveDir(int array[][10], int*posX, int *posY, int dir)
{

	int r = *posX;
	int c = *posY;
	int moveYn =0;

	if(dir==0) // ����
	{
		r--;
	}
	else if(dir ==1) // ����
	{
		c--;
	}
	else if(dir ==2) // ����
	{
		r++;
	}
	else if(dir ==3) // ����
	{
		c++;
	}

	if(r>= 11 || r < 0)
	{
		return 1;
	}

	if(c>= 10 || c < 0)
	{
		return 1;
	}

	if(array[r][c] == 1 || array[r][c] ==2)
	{
		return 1;
	}


	*posX = r;
	*posY = c;

	return moveYn;
}

int moveBack(int array[][10], int*posX, int *posY, int dir)
{

	int r = *posX;
	int c = *posY;

	if(dir==0) // ����
	{
		r++;
	}
	else if(dir ==1) // ����
	{
		c--;
	}
	else if(dir ==2) // ����
	{
		r--;
	}
	else if(dir ==3) // ����
	{
		c++;
	}

	if(r>= 11 || r < 0)
	{
		return 1;
	}

	if(c>= 10 || c < 0)
	{
		return 1;
	}

	*posX = r;
	*posY = c;

	return 0;
}
