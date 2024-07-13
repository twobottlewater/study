#include <iostream>

using namespace std;

class Doublex
{
public:
    int Double(int x)
    {
        return  2*x;
    }
    long Double(long x)
    {
        return  2*x;
    }

    float Double(float x)
    {
        return  2*x;
    }

    double Double(double x)
    {
        return  2*x;
    }



};

int main()
{
    Doublex dou;
    float n=2.56;

    n=dou.Double(n);
    cout<<"输出"<<n<<endl;

    return 0;
}
