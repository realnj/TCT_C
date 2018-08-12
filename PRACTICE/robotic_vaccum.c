#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 로봇 청소기는 다음과 같이 작동한다.
1.현재 위치를 청소한다.
2.현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
   1.왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
2.왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
3.네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
4.네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.

로봇 청소기는 이미 청소되어있는 칸을 또 청소하지 않으며, 벽을 통과할 수 없다.

첫째 줄에 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 50)

둘째 줄에 로봇 청소기가 있는 칸의 좌표 (r, c)와 바라보는 방향 d가 주어진다.
d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽을 바라보고 있는 것이다.

셋째 줄부터 N개의 줄에 장소의 상태가 북쪽부터 남쪽 순서대로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다.
빈 칸은 0, 벽은 1로 주어진다. 장소의 모든 외곽은 벽이다.

로봇 청소기가 있는 칸의 상태는 항상 빈 칸이다.

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
	int dir  =0; // 북 0, 동 1, 남 2, 서 3
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
	if(dir ==0) // 북쪽
	{
		changeDir = 3; // 서쪽
	}
	else if(dir ==1) // 동쪽
	{
		changeDir =0;
	}
	else if(dir ==2) // 남쪽
	{
		changeDir = 1;
	}
	else if(dir ==3) // 서쪽
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

	if(dir==0) // 북쪽
	{
		r--;
	}
	else if(dir ==1) // 동쪽
	{
		c--;
	}
	else if(dir ==2) // 남쪽
	{
		r++;
	}
	else if(dir ==3) // 서쪽
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

	if(dir==0) // 북쪽
	{
		r++;
	}
	else if(dir ==1) // 동쪽
	{
		c--;
	}
	else if(dir ==2) // 남쪽
	{
		r--;
	}
	else if(dir ==3) // 서쪽
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
