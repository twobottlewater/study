#include<stdio.h>

int main()
{
#if 0
//1，定义10个元素整型数组，数组元素数据通过键盘输入，请找出数组当中的最大、小值，并输出它们的和。
    //变量定义在开头
    int i, a[10];
    int min,max; 
    while(1)
    {
        printf ("输入十个数字：");
        for (i=0;i<10;i++  )
        {
            scanf ("%d",&a[i]);
        }
       
       //假设a[0]为最小值
        min = a[0];
        //假设a[0]为最大值
        max = a[0];        
        for (i=1;i<10;i++)
        {
            if (min>a[i])
            {
                min=a[i];
            }
            if (max<a[i])
            {
                max=a[i];
            }            
        }
        printf ("min:%d,max:%d\n",min, max);
        printf ("min+max=%d\n",min+max);
      }

#endif 

#if 0
// 2、编写一个程序，在用户输入某个大写字母后，产生一个金字塔图案。（与数组无关）
// 例如输入字母E，则产生如下图案：

//         A
//        ABA
//       ABCBA   
//      ABCDCBA
//     ABCDEDCBA
// 有多少行，有每一行有多少空格，打打印左边，再打印右边

    int x;
    char N;     //存放字符
    char a1='A'; //大写 ‘A’ == 65
    int a2, m, y;
    while(1)
    {
        printf("请输入一个大写英文字母:\n");
        scanf("%c",&N);
        while (getchar() != '\n');
        a2=N;     //字母赋值给a2
        if(a2 >= 'A' && a2 <= 'Z')
        {
            //显示行      'D' == 68     a1 == 68
            for(a1 = 65; a1 <= a2; a1++)
            {
                //a2-a1 = 2 
                for(m = 1; m <= a2-a1; m++)
                {
                    printf(" ");
                }
                for(x = 65 ; x <= a1 ; x++) //从A  x = 'D'
                {
                    printf("%c",x);
                }
                //递减显示字符 x == 69 y=67('C')
                for(y = x-2 ; y >= 'A' ; y--)
                {
                    printf("%c",y);
                }
                printf("\n");
            }
        }
        else
        {
            printf("输入字符有误\n");
        }
    }

#endif 

#if 1
//3、编写一个程序，接收用户的输入信息，当用户输入完成后（#代表输入完成），自动统计用户输入的空格数、大小写字母数和其他字符数数量。
    char str[256] = {0};
    int cnt=0;
    int spaces = 0;
    int chcnt=0;
    int other=0;

    while(1)
    {
        str[cnt] = getchar();

        if(str[cnt] == '#')
            break;
            
        cnt++;
    }

    //遍历数组
    for(int i=0; i<cnt; i++)
    {
        if(str[i] == ' ')
        {
            spaces++;
        }
        else if((str[i] >= 'A' && str[i] <= 'Z') ||  (str[i] >= 'a' && str[i] <= 'z') )
        {
            chcnt++;
        }
        else{
            other++;
        }
    }

    printf("spaces:%d chcnt:%d other:%d\n",spaces,chcnt,other);
    
#endif 

	return 0;
}