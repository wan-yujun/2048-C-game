#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<memory.h>
#include<windows.h>
void ini();         // 定义初始化和生成随机数种子
void first();       // 初始化生成两个数字 一个必为2，另一个2或4，比例为4:1
void page();        // 游戏页面
void color(int m);  // 修改命令行窗口顔色

//方向移动函数
void move_left();
void move_up();
void move_right();
void move_down();

void random();	    // 生成2或4的随机数且比例为4:1

void check();       // 检查是否输掉游戏，设置结束游戏标志
int game_blank();   // 获取空值个数

int map[4][4];          // 定义4行4列的二维数组
int score = 0;          // 游戏得分
int blank;              // 是否有空位标志，0代表无，1代表有
int need_add_num;       // 是否需要生成随机数标志，1表示需要，0表示不需要
int if_game_over;       // 是否游戏结束标志，1表示游戏结束，0表示正常

int main()
{
    char cmd;
    ini();                // 定义初始化和生成随机数种子
    first();              // 初始化生成两个数字 一个必为2，另一个2或4，比例为4:1
    while(1)
    {
        need_add_num = 0;      // 先设定不默认需要生成随机数，需要时再设定为1
        page();                // 游戏页面
        cmd = getch();         // 接收键盘输入命令                         
        switch (cmd)
        {
            case 'w':
            case 'W': move_up(); break;
            case 's':
            case 'S': move_down(); break;
            case 'a':
            case 'A': move_left(); break;
            case 'd':
            case 'D': move_right(); break;
        }
        if (need_add_num)                // 生成随机数
        {
            random();
        }
        if (game_blank() == 0)           // 空值个数为0就检查是否有相邻元素相等
        {
            check();
        }
        if (if_game_over)                // 游戏结束，输出游戏页面和分数
        {
            page();
            color(4);
            printf("\n\n            游戏结束,你的最终分数为:%d\n", score);
            system("pause");
            return 0;
        }
    }
}

// 检查游戏是否结束 
void check()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // 横向和纵向比较挨着的两个元素是否相等，若有相等则游戏不结束
            if (map[i][j] == map[i][j+1] || map[j][i] == map[j+1][i])
            {
                if_game_over = 0;
                return;
            }
        }
    }
    if_game_over = 1;
}

// 生成随机数 
void random()							
{
	int i, j;
	do
	{
		i = rand() % 4;
		j = rand() % 4;
	} while (map[i][j] != 0);               //随机找到值为0的i行j列

	map[i][j] = rand() % 5 ? 2 : 4;         //令其值为2或4，比例为4:1

}

// 获取空值个数 
int game_blank()
{
    int n = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            n += (map[i][j] == 0 ? 1 : 0);
        }
    }
    return n;
}

// 方向函数 
void move_left()
{
    // 变量i用来遍历行项的下标
	for (int i = 0; i < 4; i++)
	{
		// 变量j为列下标，变量k为(待比较)/(合并)项的下标 
		for (int j = 1, k = 0; j < 4; j++)
		{
			if (map[i][j] > 0) // 找出k后面第一个不为空的项，下标为j，之后分三种情况
			{
				if (map[i][k] == map[i][j]) // 情况1：k项和j项相等，此时合并方块并计分
				{
                    map[i][k] *= 2;
                    score += map[i][k]; 
                    k++;
					map[i][j] = 0;
					need_add_num = 1; // 需要生成随机数
				}
				else if (map[i][k] == 0) // 情况2：k项为空，则把j项赋值给k项，相当于j方块移动到k方块
				{
					map[i][k] = map[i][j];
					map[i][j] = 0;
					need_add_num = 1;
				}
				else // 情况3：k项不为空，且和j项不相等，此时把j项赋值给k+1项，相当于移动到k+1的位置 
				{
					map[i][++k] = map[i][j];
					if (j != k) // 判断j项和k项是否原先就挨在一起，若不是则把j项赋值为空（值为0）
					{
						map[i][j] = 0;
						need_add_num = 1;
					}
				}
			}
        }
    }
}

void move_up()
{
    // 写法与左移类似，只是方向不同，思路是一样的
    for (int j = 0; j < 4; j++)
    {
        for (int i = 1, k = 0; i < 4; i++)
        {
            if (map[i][j] > 0)
            {
                if (map[k][j] == map[i][j])
                {
                    map[k][j] *= 2;
                    score += map[k][j];
                    k++;
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else if (map[k][j] == 0)
                {
                    map[k][j] = map[i][j];
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    map[++k][j] = map[i][j];
                    if (k != i)
                    {
                        map[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

void move_right()
{
    // 写法与左移类似，只是方向不同，思路是一样的
    for (int i = 0; i < 4; i++)
    {
        for (int j = 2, k = 3; j > -1; j--)
        {
            if (map[i][j] > 0)
            {
                if (map[i][j] == map[i][k])
                {
                    map[i][k] *= 2;
                    score += map[i][k];
                    k--;
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else if (map[i][k] == 0)
                {
                    map[i][k] = map[i][j];
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    map[i][--k] = map[i][j];
                    if(k != j)
                    {
                        map[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

void move_down()
{
    // 写法与左移类似，只是方向不同，思路是一样的
    for (int j = 0; j < 4; j++)
    {
        for (int i = 2, k = 3; i > -1; i--)
        {
            if (map[i][j] > 0)
            {
                if (map[i][j] == map[k][j])
                {
                    map[k][j] *= 2;
                    score += map[k][j];
                    k--;
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else if (map[k][j] == 0)
                {
                    map[k][j] = map[i][j];
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    map[--k][j] = map[i][j];
                    if(i != k)
                    {
                        map[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

// 游戏界面
void page()
{
    int i, j;
    COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    system("cls");
    color(3);
    printf("游戏名: 2048                                 分数: %06d\n", score);
	printf("------------------------------------------------------------\n\n");
	printf("               ┏━━━━┳━━━━┳━━━━┳━━━━┓");       //顶边框 
	printf("\n");
	for (i = 0; i < 4; i++)
    {
        printf("               ┃");
		for (j = 0; j < 4; j++)
        {
			if (map[i][j] == 0)
            {
                printf("    ┃");                        //值为0时，只打印(|)
            }                                    
			else
            {  
                printf("%4d┃", map[i][j]);              //值不为0时，打印(数字|)
            }
		}
		if (i != 3)
        {
            printf("\n               ┣━━━━╋━━━━╋━━━━╋━━━━┫\n");//层边框 
        }
		else 
        {    
            printf("\n               ┗━━━━┻━━━━┻━━━━┻━━━━┛\n");//底边框
        } 
	}
	printf("------------------------------------------------------------\n");
	color(6);
	printf("           W↑  A←  →D  ↓S\n");
	printf("当前分数为:%d\n", score);
}

// 初始化生成两个数字
void first()                            
{
    int i, j;

    i = rand() % 4;
    j = rand() % 4;
    map[i][j] = 2;                      //生成数字2

    do
    {
        i = rand() % 4;
        j = rand() % 4;
    } while (map[i][j] != 0);           //随机找到值为0的i行j列

    map[i][j] = rand() % 5 ? 2 : 4;     //令其值为2或4，比例为4:1
}

// 初始化和生成随机数种子
void ini()	  
{
	srand(time(NULL));      
    memset(map, 0, sizeof(map));      //将map数组里的全部值设置为0
}

// 修改命令行窗口顔色
void color(int m)
{
	HANDLE consolehend;
	consolehend = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consolehend, m);
}