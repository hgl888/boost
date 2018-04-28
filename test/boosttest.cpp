//
// Created by hou guoli on 2018/2/24.
//

#include "iostream"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "boost/optional.hpp"
#include "boost/typeof/typeof.hpp"
#include "boost/utility/in_place_factory.hpp"
#include "vector"
#include "math.h"

using namespace boost;
using namespace std;

void myFunc()
{
    std::cout << "myFunc" << std::endl;
}

void bFunc(boost::function<void()> bfunc)
{
    bfunc();
}

void stdFunc(std::function<void()> stdfunc)
{
    stdfunc();
}

struct foo
{
    int i;
    foo(int i):i(i){}
    void bar(int x){ std::cout << "foo::bar " << i << " " << x <<std::endl;}
};


int test_optional()
{
    optional<int> op0;  //一个未初始化的optional对象
    optional<int> op1(none);//同上，使用none赋予未初始化值
    assert(!op0);
    assert(op0 == op1);
    assert(op1.get_value_or(253) == 253); //获取可选值
    optional<string> ops("test");  //初始化为字符串test
    string str = *ops;     //用解引用操作符获取值
    cout <<str.c_str()<<endl;
    vector<int> v(10);
    optional<vector<int>&> opv(v);  //容纳一个容器的引用
    assert(opv);
    opv->push_back(5);     //使用箭头操作符操纵容器
    assert(opv->size() == 11);
    opv = none;
    assert(!opv);
    system("pause");
    return 0;
}


optional<double> calc(int x)    //计算倒数
{
    return optional<double>(x != 0, 1.0 / x);//条件构造函数
}
optional<double> sqrt_op(double x)   //计算实数的平方根
{
    return optional<double>(x>0, sqrt(x));//条件构造函数
}
int test_optional_1()
{
    optional<double> d = calc(10);
    if (d)
        cout << *d <<endl;
    d = sqrt_op(-10);
    if (!d)
        cout << "no result"<<endl;
    system("pause");
    return 0;
}

int test_optional_2()
{
    BOOST_AUTO(x, make_optional(5));
    assert(*x == 5);
    BOOST_AUTO(y, make_optional<double>((*x > 10), 1.0));
    assert(!y);
    system("pause");
    return 0;
}

int test_optional_3()
{
    //就地创建string对象，不需要临时对象string("..")
    optional<string> ops(in_place("test in_place_factory"));
    cout<< (*ops).c_str()<<endl;
    //就地创建std::vector对象，不需要临时对象vector(10, 3)
    optional<vector<int>> opp(in_place(10, 3));
    assert(opp->size() == 10);
    assert((*opp)[0] == 3);
    system("pause");
    return 0;
}

int main(int, char*[])
{
    test_optional_3();
    std::function<void()> stdfunc = myFunc;//std::bind(myFunc);
    boost::function<void()> bfunc = myFunc;

    bFunc(stdfunc);
    stdFunc(bfunc);

    foo f(4);
    std::function<void()> cstdfunc = std::bind(&foo::bar,&f,23);
    boost::function<void()> bstdfunc = boost::bind(&foo::bar,&f,23);

    bFunc(cstdfunc);
    stdFunc(bstdfunc);

    return 0;
}