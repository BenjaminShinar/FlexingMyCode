#include <iostream>


template<int N,int M>
struct monster: public monster<N,M-1>
{
    explicit monster()
    {
       std::cout<< "*";
    }
};

template<int N>
struct monster<N,0>:public monster<N-1,N-1>
{
    explicit monster()
    {
        std::cout<< '\n';
    }
};

template<>
struct monster<0,0>
{};

int main()
{
    monster<5,5> m;
    return 0;
}