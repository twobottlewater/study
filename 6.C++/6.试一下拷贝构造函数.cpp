#include <iostream>  // C++特有的头文件，输入输出流头文件
using namespace std;

/*
    使用拷贝构造函数
*/
class Cat
{
public:

    Cat(int _weight=2,int _age=2)
    {
        weight=_weight;
        age=_age;
        cout<<"我调用了默认参数构造函数"<<endl;

    }
    Cat(const Cat &other)
    {
          cout<<"我调用了拷贝构造函数"<<endl;
          weight=other.weight;
          age=other.age;
    }

    void show_cat()
    {
        cout<<"x是:"<<age<<endl;
        cout<<"y是:"<<weight<<endl;
    }
private:
        int weight;
        int age;

};


int main()
{
    //第一种情况
    // Cat c1(5,6);
    // Cat c2(c1);
   


    //第二种情况
    // Cat c1(7,8);
    // Cat c2=c1;

    //第三种情况

    Cat c1(8,9);
    Cat *c2=new Cat(c1);



    c1.show_cat();
    c2->show_cat();

    delete c2;

    return 0;
}