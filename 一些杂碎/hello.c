#include <stdio.h>

int GetPhaseNum(void);

int main(int argc, char const *argv[])
{
	GetPhaseNum();
    
    return 0;
}

int GetPhaseNum(void)
{
	int i;            //阶梯数
    int count = 0;    //记录满足条件的阶梯个数
	
    for (i = 1; i < 1000; i++)
    {

        if (i % 2 == 1 && i % 3 == 2 && i % 4 == 3&& i % 5 == 4 && i % 6 == 5 && i % 7 == 0)
        {
            count++;
			
            while (count == 1)
            {
                printf("最少阶梯数为：%d\n", i);
                break;
            }
        }
        
    }	
}


