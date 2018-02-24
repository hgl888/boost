//
// Created by hou guoli on 2018/2/24.
//

#include "iostream"
#include "boost/function.hpp"
#include "boost/bind.hpp"

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



int main(int, char*[])
{

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