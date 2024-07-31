#include <iostream>  // C++特有的头文件，输入输出流头文件
using namespace std;

/*
    定义矩形类  
*/
class Rect
{
public:
    // 构造函数
    Rect(float _w=2, float _h=2);

    // 成员方法
    void getArea()
    {
        cout << "矩形面积: " << w * h << endl;
    }

    void getGirth()
    {
        cout << "矩形周长: " << 2 * (w + h) << endl;
    }

    // 设置属性
    void setAttr(float _w, float _h)
    {
        w = _w;
        h = _h;
    }

private:
    // 成员属性
    float w;
    float h;
};

Rect::Rect(float _w, float _h)
{
    w = _w;
    h = _h;
}

int main()
{
    // 创建矩形对象
    Rect r1;
    // r1.setAttr(2.5, 1.2); // 如果需要在创建对象后修改属性，可以取消注释这行
    r1.getArea();
    r1.getGirth();
    return 0;
}