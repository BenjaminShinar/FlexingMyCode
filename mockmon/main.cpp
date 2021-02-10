//#include <format>
#include <iostream>
#include <sstream> 
#include <string>
#include "include/controller.h"

using namespace mockmon;




controller::controller GetInput(const std::string & prompt,std::pair<const std::string,controller::controller>  a ... )
{

    std::cout<< prompt << '\n';
        int d = 1;
        std::string s;

    do
    {
    std::getline(std::cin,s);
    std::istringstream is(s);
    is >> d;
    std::cout << "input read is " <<d <<'\n';
    } while (d <=0 || d>8);

    switch (d)
    {
    case 1: 
        std::cout <<  a.first <<" : " << controller::controllerToStr(a.second)<<'\n';
        return a.second;
        break;
    
    default:
    
        std::cout << "do nothing" << '\n';
        return controller::SELECT;
        break;
    }
    
}




int main()
{
    std::string x("hello world");
    std::cout<<controller::controllerToStr(controller::DPAD_UP)<<'\n';
    std::cout<<controller::controllerToStr(controller::DPAD_LEFT)<<'\n';
    std::cout<<controller::controllerToStr(controller::DPAD_DOWN)<<'\n';
    std::cout<<controller::controllerToStr(controller::DPAD_RIGHT)<<'\n';
    std::cout<<controller::controllerToStr(controller::ACTION_A)<<'\n';
    std::cout<<controller::controllerToStr(controller::CANCEL_B)<<'\n';
    std::cout<<controller::controllerToStr(controller::START)<<'\n';
    std::cout<<controller::controllerToStr(controller::SELECT)<<'\n';

    
    // std::cout << "enter value of x" <<'\n';
    // std::cin >> x;
    // std::cout << x <<'\n';

    auto cmd =GetInput("test case user input",{"option A",controller::ACTION_A});
    std::cout<<controller::controllerToStr(cmd)<<'\n';

}