#include <stdio.h>

int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
// 定义一个函数，判断日期是否合法，返回0表示合法，返回1表示非法
int is_valid_date(int day, int month, int year)
{
    // 判断年份是否在合理的范围内
    if (year < 1800 || year > 9999)
    {
        return 1;
    }
    // 判断月份是否在合理的范围内
    if (month < 1 || month > 12)
    {
        return 1;
    }
    // 定义一个数组，存储每个月的天数
 
    // 判断是否是闰年，如果是，将二月的天数改为29
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        days_in_month[1] = 29;
    }
    // 判断日期是否在合理的范围内
    if (day < 1 || day > days_in_month[month - 1])
    {
        return 1;
    }
    // 如果以上都通过，返回0表示日期合法
    return 0;
}

int main()
{
    int day, month, year;
    int result; // 用来存储scanf的返回值
    int valid;  // 用来存储日期是否合法的标志
	
    do
    {
        printf("请输入年月日，格式为yyyy mm dd\n");
        // 使用%4d和%2d来限制输入的位数，使用result来接收scanf的返回值
        result = scanf("%4d%2d%2d", &year, &month, &day);
        // 清空输入缓冲区，防止输入错误的字符影响下一次输入
        while (getchar() != '\n')
            ;
        // 如果输入的不是三个数字，提示输入错误
        if (result != 3)
        {
            printf("您的输入有误，请重新输入\n");
            continue;
        }
        // 调用函数，判断日期是否合法，将返回值赋给valid
        valid = is_valid_date(day, month, year);
        // 如果valid为1，表示日期非法，提示重新输入
        if (valid == 1)
        {
            printf("您输入的日期非法，请重新输入\n");
        }
        // 如果valid为0，表示日期合法，跳出循环
    } while (valid == 1);

    // 如果程序能执行到这里，表示输入的日期合法，打印提示信息
    printf("您输入的日期合法\n");

    // 使用一个循环，计算输入的日期是这年的第几天
    int day_of_year = 0; // 用来存储结果
    for (int i = 0; i < month - 1; i++)
    {
        // 累加前几个月的天数
        day_of_year += days_in_month[i];
    }
    // 再加上当前月的天数
    day_of_year += day;
    // 打印结果
    printf("您输入的是这年的第%d天\n", day_of_year);

    return 0;
}
