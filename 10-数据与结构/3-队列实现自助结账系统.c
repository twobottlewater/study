#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//商品结构体
typedef struct {
    int id;//商品编号
    char name[20];//商品名称
    float price;//商品价格
    int num;//商品数量
} Product;


//队列结构体  --顺序队列
typedef struct {
    Product *queue;//商品数组
    int first;//队头
    int last;//队尾
    int max_size;//队列最大长度
}SeqQue;

SeqQue*shopQue;

//初始化队列
void queue_init(int max_size)
{
    //1 申请队列管理结构体内存空间
    shopQue = malloc(sizeof(SeqQue));
    if(shopQue==NULL){
        perror("malloc error");
        return ;
    }
    //2 初始化队列
    shopQue->queue = (Product*)malloc(sizeof(Product) * max_size);
    shopQue->first = 0;
    shopQue->last = 0;
    shopQue->max_size = max_size;

}

//判断队列是否为满
bool queue_is_full()
{
    return (shopQue->last + 1)%shopQue->max_size == shopQue->first;
}

//入队
bool queue_push( Product data)
{
    if(queue_is_full()){
        printf("队列已满\n");
        return false;
    }
    shopQue->queue[shopQue->last] = data;
    shopQue->last = (shopQue->last + 1)%shopQue->max_size;

    return true;
}

void car_insert()
{
    Product temp;
    memset(&temp, 0, sizeof(temp));
    //提示用户输入商品信息
    printf("请输入商品编号:");
    scanf("%d", &temp.id);
    printf("请输入商品名称:");
    scanf("%s", temp.name);
    printf("请输入商品价格:");
    scanf("%f", &temp.price);
    printf("请输入商品数量:");
    scanf("%d", &temp.num);
    
    //将商品信息添加到队列中
    queue_push( temp);
}

//出队
void queue_pop(Product *data)
{
    if(shopQue->first == shopQue->last){
        printf("队列为空\n");
        return ;
    } 
    *data = shopQue->queue[shopQue->first];
    shopQue->first = (shopQue->first + 1)%shopQue->max_size;
}

void car_result()   
{
    //每次结算的时候 只会结算 商品购物车队列中的一个商品
    //出队
    Product temp;
    queue_pop(&temp);
    //计算总金额
    float sum = temp.price * temp.num;
    printf("商品编号:%d\t", temp.id);
    printf("商品名称:%s\t", temp.name);
    printf("商品价格:%f\t", temp.price);
    printf("商品数量:%d\t", temp.num);
    printf("商品总金额:%f\n", sum);
}

void car_scan()
{
    //遍历队列
    for(int i = shopQue->first; i != shopQue->last; i = (i+1)%shopQue->max_size){
        printf("商品编号:%d\t", shopQue->queue[i].id);
        printf("商品名称:%s\t", shopQue->queue[i].name);    
        printf("商品价格:%f\t", shopQue->queue[i].price);
        printf("商品数量:%d\n", shopQue->queue[i].num);
    }
}


int main()
{
    queue_init(100);

    while (1)
    {
        /* code */
        printf("[1]将商品加入购物车 [2]查看购物车    [3]结算 [4]退出:");
        int n;
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            car_insert();
            break;
        case 2:
            car_scan();
            break;
        case 3:
            car_result();
            break;
        default:
            break;
        }
    
    }
    

    return 0;
}