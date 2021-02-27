//#include <format>
#include <iostream>
#include <sstream> 
#include <string>

#include "include/controller.h"
#include "include/mockmon_data.h"

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
    //controller::TestControllerToString();
    Mockmon m{};
    m.GrantExperiencePoints(105);
    m.GrantExperiencePoints(105);

    std::cout << "mockmon is " << m.CheckExperiencePoints() << '\n';
    m.ChangeName("levelupper");
    m.GrantExperiencePoints(305);

    //m.GrantExperiencePoints(3005);
    std::cout << "mockmon is " << m.CheckExperiencePoints() << '\n';
    m.GrantExperiencePoints(384);
    std::cout << "mockmon is " << m.CheckExperiencePoints() << '\n';
    m.GrantExperiencePoints(2);
    std::cout << "mockmon is " << m.CheckExperiencePoints() << '\n';

    // std::cout << "enter value of x" <<'\n';
    // std::cin >> x;
    // std::cout << x <<'\n';

    //auto cmd =GetInput("test case user input",{"option A",controller::ACTION_A});
    //std::cout<<controller::controllerToStr(cmd)<<'\n';

}